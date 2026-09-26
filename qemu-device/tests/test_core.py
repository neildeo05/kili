#!/usr/bin/env python3
"""Compile the standalone C datapath and compare it to kili.py."""
import argparse
import ctypes
import importlib.util
import itertools
from pathlib import Path
import random
import shlex
import subprocess
import tempfile


def load_model(path):
    spec = importlib.util.spec_from_file_location("kili", path)
    model = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(model)
    return model


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--model", type=Path,
                        default=Path(__file__).resolve().parents[3] / "kili.py")
    parser.add_argument("--cc", default="cc")
    args = parser.parse_args()
    model = load_model(args.model)
    source = Path(__file__).resolve().parents[1]
    with tempfile.TemporaryDirectory(prefix="kili-core-") as tmp:
        library = Path(tmp) / "kili.so"
        subprocess.run(shlex.split(args.cc) + [
            "-std=c11", "-DKILI_STANDALONE", "-O2", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC",
            str(source / "kili-core.c"), "-o", str(library)], check=True)
        core = ctypes.CDLL(str(library))
        byte = ctypes.c_uint8
        pointer = ctypes.POINTER(byte)
        core.kili_decode_byte.argtypes = [byte]
        core.kili_decode_byte.restype = ctypes.c_uint16
        core.kili_tmatmul.argtypes = [pointer, pointer, pointer]
        core.kili_tmatmul.restype = None

        def array(data):
            return (byte * len(data))(*data)

        for encoded in range(256):
            assert core.kili_decode_byte(encoded) == model._decode_bits(encoded)
        # Exhaust every pair of encoded row bytes, including ignored padding.
        acts = array([128, 255, 1, 2, 127, 19, 63, 251])
        out = (byte * 8)()
        for first, second in itertools.product(range(256), repeat=2):
            weights = bytes([first, second] * 8)
            core.kili_tmatmul(array(weights), acts, out)
            assert list(out) == model.tmatmul(weights, acts)
        rng = random.Random(42)
        for _ in range(1000):
            weights = rng.randbytes(16)
            acts = rng.randbytes(8)
            core.kili_tmatmul(array(weights), array(acts), out)
            assert list(out) == model.tmatmul(weights, acts)
    print("PASS: C/Python parity: 256 decoder inputs, 65,536 row-byte pairs, "
          "1,000 random tiles")


if __name__ == "__main__":
    main()
