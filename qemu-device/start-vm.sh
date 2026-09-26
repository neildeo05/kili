#!/bin/sh
# Restart the existing Ubuntu ARM64 VM with the custom Kili QEMU binary.
# Power off the old VM first. This script does not stop a running VM.
set -eu

project_dir=$(CDPATH= cd -- "$(dirname -- "$0")/../../.." && pwd)
qemu_binary=${KILI_QEMU:-/tmp/kili-qemu-build/qemu-system-aarch64}

if [ ! -x "$qemu_binary" ]; then
    echo "Missing custom QEMU: $qemu_binary (see driver/README.md)" >&2
    exit 1
fi
"$qemu_binary" -device kili,help >/dev/null
if ! "$qemu_binary" -display help | grep -q cocoa; then
    echo "This QEMU must be built with --enable-cocoa." >&2
    exit 1
fi

cd "$project_dir"
exec "$qemu_binary" \
    -machine virt,gic-version=3 \
    -accel hvf -cpu host -smp 4 -m 4G \
    -drive if=pflash,format=raw,unit=0,file=edk2-aarch64-code.fd,readonly=on \
    -drive if=pflash,format=raw,unit=1,file=edk2-arm-vars.fd \
    -drive if=none,file=ubuntu-arm64.qcow2,format=qcow2,id=os \
    -device virtio-blk-pci,drive=os \
    -device virtio-net-pci,netdev=net0 \
    -netdev user,id=net0,hostfwd=tcp:127.0.0.1:2222-:22 \
    -device virtio-gpu-pci \
    -device qemu-xhci -device usb-kbd -device usb-tablet \
    -device edu,id=edu0,dma_mask=0xffffffffffffffff \
    -device pcie-root-port,id=kili_port,chassis=1 \
    -device kili,id=kili0,bus=kili_port \
    -display cocoa
