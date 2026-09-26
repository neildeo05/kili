# Kili C / QEMU device

Implementation of QEMU backend for `kili` ternary AI accelerator, and linux kernel module for it

## Build and run

From this directory, install into the adjacent QEMU source checkout:

```sh
python3 install.py ../../../qemu
mkdir -p /tmp/kili-qemu-build
cd /tmp/kili-qemu-build
/absolute/path/to/qemu/configure --target-list=aarch64-softmmu --disable-docs --disable-rust
make -j8
```

Use the newly built binary and attach Kili through a PCIe root port:

```sh
-device pcie-root-port,id=kili_port,chassis=1 -device kili,bus=kili_port
```

Run the tests from this directory:

```sh
python3 -B tests/test_core.py --model ../../kili.py
python3 -B tests/test_device.py --qemu /tmp/kili-qemu-build/qemu-system-aarch64 --model ../../kili.py
```
