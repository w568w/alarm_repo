# qemu-aarch64-static-fast - speed up qemu-aarch64-static

`qemu-aarch64-static` is used to transparently emulate aarch64
on non-native hosts. It is useful to build container images.

However, the default configuration is slow, due to pointer
authentication emulation. There is a QEMU flag to speed it up,
but it takes a bit of work to integrate it into the kernel
binfmt_misc system. This program does the work for you. It
requires that `qemu-aarch64-static` already be installed.

Usage
    make
    sudo make install