# Kili

Ternary TMatmul accelerator with a QEMU PCIe device and Linux driver.
The example runs **TMatmul → ReLU → TMatmul**. The driver supports 16 outstanding requests.

These steps use an **Apple Silicon Mac** and an existing **Ubuntu ARM64 VM**.
The VM disk and firmware are not included in this repository.

1. **On the Mac: clone and build QEMU with Kili.**

   ```sh
   git clone https://github.com/neildeo05/kili.git
   cd kili
   brew install ninja meson pkg-config glib pixman dtc
   git clone https://gitlab.com/qemu-project/qemu.git qemu
   git -C qemu checkout efa3b9d5ac8024078225e1ab434411fdfe53b457
   python3 qemu-device/install.py qemu
   mkdir -p qemu/build
   cd qemu/build
   ../configure --target-list=aarch64-softmmu --disable-docs --disable-rust --enable-cocoa \
       --extra-cflags="-I$(brew --prefix dtc)/include" \
       --extra-ldflags="-L$(brew --prefix dtc)/lib"
   ninja -j8
   cd ../..
   ```

2. **Shut down the old VM.** Put your existing `ubuntu-arm64.qcow2`,
   `edk2-aarch64-code.fd`, and writable `edk2-arm-vars.fd` in a `vm/` directory
   inside this checkout. From the checkout root, start the VM:

   ```sh
   ./qemu/build/qemu-system-aarch64 \
       -machine virt,gic-version=3 -accel hvf -cpu host -smp 4 -m 4G \
       -drive if=pflash,format=raw,unit=0,file=vm/edk2-aarch64-code.fd,readonly=on \
       -drive if=pflash,format=raw,unit=1,file=vm/edk2-arm-vars.fd \
       -drive if=none,file=vm/ubuntu-arm64.qcow2,format=qcow2,id=os \
       -device virtio-blk-pci,drive=os \
       -device virtio-net-pci,netdev=net0 \
       -netdev user,id=net0,hostfwd=tcp:127.0.0.1:2222-:22 \
       -device virtio-gpu-pci -device qemu-xhci -device usb-kbd -device usb-tablet \
       -device pcie-root-port,id=kili_port,chassis=1 \
       -device kili,bus=kili_port -display cocoa
   ```

3. **In another Mac terminal:** from the checkout root, copy the driver sources
   and connect. Replace `user` with your VM username if different; SSH must be
   enabled in the guest.

   ```sh
   ssh -p 2222 user@localhost 'mkdir -p ~/kili-device'
   scp -P 2222 -r qemu-device/driver qemu-device/tests qemu-device/kili-*.h \
       qemu-device/kili-core.c user@localhost:~/kili-device/
   ssh -p 2222 user@localhost
   ```

4. **Inside Ubuntu: build, load, and run.**

   ```sh
   sudo apt-get update
   sudo apt-get install -y build-essential linux-headers-$(uname -r) pciutils
   cd ~/kili-device/driver
   make -j4
   lspci -nn -d 1234:1111
   sudo insmod ./kili_drv.ko
   sudo ./kili_test
   sudo ./kili_queue_test
   ```

   Expect `PASS` messages for the network and the 32-caller queue test.
   Repeat `insmod` after each guest boot. Before loading a rebuilt module, run
   `sudo rmmod kili_drv`. Run the queue test when the device is otherwise idle.

[Device ABI](qemu-device/README.md) · [Driver details](qemu-device/driver/README.md) · [HDL notes](hdl/README.md)
