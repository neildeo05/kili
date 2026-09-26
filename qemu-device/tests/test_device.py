#!/usr/bin/env python3
"""Exercise the real QEMU device through qtest; no guest OS or Python packages."""
import argparse
from pathlib import Path
import random
import socket
import struct
import subprocess
import tempfile
import time

from test_core import load_model

BAR = 0x10000000
ROOT_CFG = 0x3F000000 + (1 << 15)  # virt,highmem=off, root port 00:01.0
CFG = 0x3F000000 + (1 << 20)  # Endpoint on secondary bus 01:00.0
SQ, CQ = 0x40100000, 0x40200000
WEIGHTS, ACTS, OUTPUT, MSI = 0x40300000, 0x40400000, 0x40500000, 0x40600000
MSI_DATA = 0x1234ABCD


class Device:
    def __init__(self, binary, tmp):
        path = str(Path(tmp) / "qtest.sock")
        self.log = open(Path(tmp) / "qemu.log", "w+")
        self.proc = subprocess.Popen([
            str(binary), "-machine", "virt,highmem=off", "-cpu", "max",
            "-accel", "qtest", "-m", "128M", "-display", "none",
            "-nodefaults", "-device", "pcie-root-port,id=rp,addr=01.0,chassis=1",
            "-device", "kili,bus=rp,addr=00.0", "-qtest",
            f"unix:{path},server=on,wait=off", "-qtest-log", "/dev/null"],
            stdout=self.log, stderr=self.log)
        self.sock = socket.socket(socket.AF_UNIX)
        self.sock.settimeout(5)
        deadline = time.monotonic() + 10
        try:
            while True:
                try:
                    self.sock.connect(path)
                    break
                except (FileNotFoundError, ConnectionRefusedError):
                    if self.proc.poll() is not None or time.monotonic() > deadline:
                        self.log.seek(0)
                        raise RuntimeError(self.log.read())
                    time.sleep(0.02)
            self.stream = self.sock.makefile("rwb", buffering=0)
            # No firmware under qtest: configure the bridge's bus and MMIO window.
            self.writel(ROOT_CFG + 0x18, 0x00010100)
            self.writel(ROOT_CFG + 0x20, 0x10001000)  # 0x10000000..0x100fffff
            self.command(f"writew {ROOT_CFG + 4:#x} 0x6")
            assert self.readl(CFG) == 0x11111234
            pcie = self.readl(CFG + 0x80)
            assert pcie & 0xFF == 0x10  # PCI Express capability.
            assert (pcie >> 16) & 0xF == 2  # Capability version 2.
            assert (pcie >> 20) & 0xF == 0  # Ordinary PCIe endpoint.
            self.writel(CFG + 0x10, BAR)
            self.command(f"writew {CFG + 4:#x} 0x6")  # Memory + bus master.
            assert self.reg(0) == 0x69696969
            assert self.reg(4) == 2
            self.msix_cap = self.readl(CFG + 0x34) & 0xFF
            while self.msix_cap:
                cap = self.readl(CFG + self.msix_cap)
                if cap & 0xFF == 0x11:
                    break
                self.msix_cap = (cap >> 8) & 0xFF
            assert self.msix_cap
            self.writel(BAR + 0x2000, MSI)
            self.writel(BAR + 0x2004, 0)
            self.writel(BAR + 0x2008, MSI_DATA)
            self.writel(BAR + 0x200C, 0)
            self.msix(True)
        except BaseException:
            self.close()
            raise

    def close(self):
        if hasattr(self, "stream"):
            self.stream.close()
        self.sock.close()
        self.proc.terminate()
        self.proc.wait(timeout=10)
        self.log.close()

    def command(self, text):
        self.stream.write((text + "\n").encode())
        result = self.stream.readline().decode().strip()
        assert result.startswith("OK"), (text, result)
        return result[2:].strip()

    def readl(self, addr):
        return int(self.command(f"readl {addr:#x}"), 16)

    def writel(self, addr, value):
        self.command(f"writel {addr:#x} {value:#x}")

    def reg(self, offset, value=None):
        if value is None:
            return self.readl(BAR + offset)
        self.writel(BAR + offset, value)

    def write(self, addr, data):
        self.command(f"write {addr:#x} {len(data):#x} 0x{data.hex()}")

    def read(self, addr, count):
        return bytes.fromhex(self.command(f"read {addr:#x} {count:#x}")[2:])

    def msix(self, enable):
        self.command(f"writew {CFG + self.msix_cap + 2:#x} {0x8000 if enable else 0:#x}")

    def setup(self, sq_size=16, cq_size=4, sq=SQ, cq=CQ):
        self.reg(8, 2)
        self.sq_size, self.cq_size = sq_size, cq_size
        for offset, value in ((0x10, sq & 0xFFFFFFFF), (0x14, sq >> 32),
                              (0x18, cq & 0xFFFFFFFF), (0x1C, cq >> 32),
                              (0x20, sq_size), (0x24, cq_size)):
            self.reg(offset, value)
        self.reg(8, 1)

    def submit(self, sequence, tag=0,
               weights=WEIGHTS, acts=ACTS, output=OUTPUT, reserved=0):
        sqe = struct.pack("<IIQQQ", tag, reserved,
                          weights, acts, output)
        self.write(SQ + (sequence % self.sq_size) * 32, sqe)

    def wait(self, offset, value):
        deadline = time.monotonic() + 5
        while self.reg(offset) != value:
            if time.monotonic() > deadline:
                raise AssertionError(f"register {offset:#x}: expected {value}, "
                                     f"got {self.reg(offset)}; error {self.reg(0x38)}")
            time.sleep(0.001)

    def completion(self, sequence):
        return struct.unpack("<II", self.read(CQ + sequence % self.cq_size * 8, 8))


def exercise(d, model):
    rng = random.Random(42)
    weights = [[rng.choice((-1, 0, 1)) for _ in range(8)] for _ in range(8)]
    activations = [[rng.randrange(256) for _ in range(8)] for _ in range(8)]
    d.write(WEIGHTS, model.encode_tile(weights))
    d.setup()
    assert d.reg(0x0C) == 1
    # Matrix multiply: eight queued columns, and deliberately fill the CQ.
    for col in range(8):
        d.write(ACTS + col * 8, bytes(row[col] for row in activations))
        d.write(OUTPUT + col * 8, b"\xcc" * 8)
        d.submit(col, tag=col, acts=ACTS + col * 8, output=OUTPUT + col * 8)
    d.reg(0x30, 8)
    d.wait(0x2C, 4)
    assert d.reg(0x28) == 4
    assert d.reg(0x0C) & 4
    assert d.read(OUTPUT + 32, 32) == b"\xcc" * 32
    for col in range(4):
        assert d.completion(col) == (col, 0)
    d.reg(0x34, 4)
    d.wait(0x2C, 8)
    for col in range(4, 8):
        assert d.completion(col) == (col, 0)
    expected = bytes(sum(weights[r][k] * activations[k][c] for k in range(8)) & 255
                     for c in range(8) for r in range(8))
    assert d.read(OUTPUT, 64) == expected
    assert d.readl(MSI) == MSI_DATA
    d.reg(0x34, 8)

    # Pause at CQ backpressure; acknowledging while paused cannot start DMA.
    d.setup(sq_size=8, cq_size=2)
    for sequence in range(4):
        d.submit(sequence, output=OUTPUT + sequence * 8)
    d.write(OUTPUT, b"\xcc" * 32)
    d.reg(0x30, 4)
    d.wait(0x2C, 2)
    d.reg(8, 0)
    d.reg(0x34, 2)  # Doorbells while paused are ignored.
    assert d.reg(0x34) == 0
    assert d.reg(0x2C) == 2
    d.reg(0x10, SQ + 64)  # Configuration remains locked while paused.
    assert d.reg(0x10) == SQ
    d.reg(8, 1)
    d.reg(0x34, 2)
    d.wait(0x2C, 4)

    # Reset a full CQ while work is still queued; cancelled work stays unwritten.
    d.setup(sq_size=8, cq_size=2)
    for sequence in range(4):
        d.submit(sequence, output=OUTPUT + sequence * 8)
    d.write(OUTPUT, b"\xcc" * 32)
    d.reg(0x30, 4)
    d.wait(0x2C, 2)
    d.reg(8, 2)
    assert d.reg(0x2C) == d.reg(0x30) == d.reg(0x38) == 0
    assert d.read(OUTPUT + 16, 16) == b"\xcc" * 16

    # A single doorbell must process every usable slot of a full-size ring.
    d.setup(sq_size=256, cq_size=256)
    for sequence in range(256):
        d.submit(sequence, tag=sequence)
    d.reg(0x30, 256)
    d.wait(0x2C, 256)
    assert d.reg(0x28) == 256
    for sequence in range(256):
        assert d.completion(sequence) == (sequence, 0)
    d.reg(0x34, 256)
    d.setup()

    # Multiple wraps of both rings and fresh MSI-X writes for each completion.
    for sequence in range(80):
        w, a = rng.randbytes(16), rng.randbytes(8)
        d.write(WEIGHTS, w)
        d.write(ACTS, a)
        d.write(OUTPUT, b"\xcc" * 16)
        d.writel(MSI, 0)
        d.submit(sequence, tag=sequence)
        d.reg(0x30, sequence + 1)
        d.wait(0x2C, sequence + 1)
        assert d.completion(sequence) == (sequence, 0)
        assert d.read(OUTPUT, 8) == bytes(model.tmatmul(w, a))
        assert d.read(OUTPUT + 8, 8) == b"\xcc" * 8
        assert d.readl(MSI) == MSI_DATA
        d.reg(0x34, sequence + 1)

    # Masked MSI-X sets the PBA and unmasking delivers the pending message.
    d.setup()
    d.writel(MSI, 0)
    d.writel(BAR + 0x200C, 1)
    d.submit(0)
    d.reg(0x30, 1)
    d.wait(0x2C, 1)
    assert d.readl(MSI) == 0
    assert d.readl(BAR + 0x3000) & 1
    d.writel(BAR + 0x200C, 0)
    assert d.readl(MSI) == MSI_DATA
    assert not d.readl(BAR + 0x3000) & 1

    # Late interrupt enable must report completions accumulated while polling.
    d.setup()
    d.msix(False)
    d.writel(MSI, 0)
    d.submit(0)
    d.reg(0x30, 1)
    d.wait(0x2C, 1)
    assert d.readl(MSI) == 0
    d.msix(True)
    assert d.readl(MSI) == MSI_DATA

    # Per-command failures still produce a CQE and allow following commands.
    errors = [({"reserved": 1}, 1),
              ({"weights": 0xFFFFFFFFFFFFFFF8}, 2),
              ({"acts": 0xFFFFFFFFFFFFFF00}, 2),
              ({"output": 0xFFFFFFFFFFFFFFFC}, 2),
              ({"weights": BAR}, 2), ({"output": BAR + 0x30}, 2)]
    for kwargs, status in errors:
        d.setup()
        d.submit(0, tag=17, **kwargs)
        d.submit(1, tag=18)
        d.reg(0x30, 2)
        d.wait(0x2C, 2)
        assert d.completion(0) == (17, status)
        assert d.completion(1) == (18, 0)
        assert d.reg(0x38) == 0

    # Invalid ring configuration, forward/backward doorbells, and DMA failures.
    for params in ({"sq_size": 3}, {"cq_size": 512}, {"sq": SQ + 1},
                   {"sq": 0xFFFFFFFFFFFFFFC0}):
        d.setup(**params)
        assert d.reg(0x38) == 1
        assert d.reg(0x0C) & 2
    for offset, value in ((0x30, 17), (0x30, 0xFFFFFFFF), (0x34, 1)):
        d.setup()
        d.reg(offset, value)
        assert d.reg(0x38) == 2
    d.setup(sq=0xFFFFFFFF00000000)
    d.reg(0x30, 1)
    d.wait(0x38, 3)
    d.setup(cq=0xFFFFFFFF00000000)
    d.submit(0)
    d.reg(0x30, 1)
    d.wait(0x38, 4)
    d.setup()
    d.command(f"writew {CFG + 4:#x} 0x2")
    d.submit(0)
    d.reg(0x30, 1)
    d.wait(0x38, 5)
    d.command(f"writew {CFG + 4:#x} 0x6")
    d.setup()
    assert d.reg(0x38) == 0
    assert d.reg(0x28) == d.reg(0x2C) == d.reg(0x30) == d.reg(0x34) == 0
    d.submit(0)
    d.reg(0x30, 1)
    d.wait(0x2C, 1)
    assert d.completion(0)[1] == 0
    print("PASS: PCIe endpoint/root port/BAR0, queued 8x8 matmul, ring wrap/full, "
          "MSI-X delivery/masking/late enable, descriptor/DMA errors and reset")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--qemu", required=True, type=Path)
    parser.add_argument("--model", type=Path,
                        default=Path(__file__).resolve().parents[3] / "kili.py")
    args = parser.parse_args()
    model = load_model(args.model)
    with tempfile.TemporaryDirectory(prefix="kili-qtest-") as tmp:
        device = Device(args.qemu.resolve(), tmp)
        try:
            exercise(device, model)
        finally:
            device.close()


if __name__ == "__main__":
    main()
