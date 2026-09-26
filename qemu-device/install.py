#!/usr/bin/env python3
"""Install the local Kili device into a QEMU source checkout (idempotent)."""
import argparse
from pathlib import Path
import shutil

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("qemu", type=Path)
args = parser.parse_args()
source = Path(__file__).resolve().parent
target = args.qemu.resolve()
misc = target / "hw/misc"
if not (target / "include/hw/pci/msix.h").is_file() or not (misc / "Kconfig").is_file():
    parser.error("expected a QEMU source checkout")

for name in ("kili-core.c", "kili-core.h", "kili-pci.c", "kili-regs.h"):
    shutil.copyfile(source / name, misc / name)

meson = misc / "meson.build"
line = "system_ss.add(when: 'CONFIG_KILI', if_true: files('kili-pci.c', 'kili-core.c'))\n"
text = meson.read_text()
if line not in text:
    meson.write_text(text.rstrip() + "\n\n" + line)

kconfig = misc / "Kconfig"
text = kconfig.read_text()
if "config KILI\n" not in text:
    kconfig.write_text(text.rstrip() + "\n\nconfig KILI\n"
                      "    bool\n    default y if TEST_DEVICES\n"
                      "    depends on PCI && MSI_NONBROKEN\n")
print(f"Installed Kili sources and build entries in {misc}")
