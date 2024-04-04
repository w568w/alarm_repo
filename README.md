# Personal ArchLinux ARM Repo
Some personally maintained packages that are unsuitable for AUR will be hosted here.

## Packages
### 1. libmali-bifrost-g52-g13p0-x11-gbm
A closed-source Bifrost Mali driver (userspace part) for Mali G52.

It provides OpenCL and OpenGL ES support on Orangepi 3B.

Repacked from <https://github.com/orangepi-xunlong/rk-rootfs-build/>.

> **Note: How to use Mali G52?**
>
> To utilize the GPU, you have to choose one of the following options:
> 
> 1. Open-sourced upstream solution:
>    - Kernel modules: Panfrost ([need to be enabled](https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/drivers/gpu/drm/panfrost/Kconfig) in mainline kernel, **NOT** in OrangePi OS)
>    - Userspace: [Mesa with Panfrost support](https://docs.mesa3d.org/drivers/panfrost.html) (just `pacman -S mesa` may work)
> 2. Closed-sourced downstream solution:
>    - Kernel modules: Mali GPU kernel modules (already built in OrangePi OS, **NOT** in mainline kernel)
>    - Userspace: **This package** (just `makepkg -si` it)
>
> `linux-aarch64-rockchip-opi3b-npu-w568w` in this repository has Panfrost enabled.
>
> See [OpenSUSE Wiki](https://en.opensuse.org/ARM_Mali_GPU) for more information.

### 2. linux-aarch64-rockchip-opi3b-npu-w568w
The Linux kernel and modules with my own patches for Orangepi 3B. Adapted from (and would be synced with) [@SUISHUI's repository](https://github.com/SUISHUI/linux-orangepi-3b).

> **Note: Why the kernel name is so long?**
> 
> The name follows [@7Ji's Kernel Package Guidelines](https://github.com/7Ji-PKGBUILDs/.meta/blob/main/PackageGuidelines.md#kernel-package-guidelines).

It should be kept up-to-date with upstream kernel, rather than full of patches and dirty hacks, or even diverged from upstream (**saying you, [Rockchip](https://github.com/rockchip-linux/kernel/tree/develop-5.10) and [Xunlong](https://github.com/orangepi-xunlong/linux-orangepi/blob/orange-pi-5.10-rk35xx/)!**)

#### Features
It can be a drop-in replacement of the default kernel (usually called `linux-rk3566-legacy`) in OrangePi OS (based on Archlinux ARM).

It is patched with following features:

1. Add **device tree** for Orangepi 3B
2. Add **WiFi** driver for UWE5622
3. Add **NPU** driver v0.9.3 for RK3566 (**see notes below!**)

[Panfrost](https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/drivers/gpu/drm/panfrost/) kernel module is included and enabled by default. So you can use it with [Mesa 3D](https://docs.mesa3d.org/drivers/panfrost.html) to enjoy **OpenGL ES and OpenCL with your GPU** too.

RKNPU driver is migrated by myself from downstream kernels [rockchip-linux/kernel](https://github.com/rockchip-linux/kernel/tree/develop-5.10) and [orangepi-xunlong/linux-orangepi](https://github.com/orangepi-xunlong/linux-orangepi/blob/orange-pi-5.10-rk35xx/). 

> **Warning** 
> 
> A lot of changes and polyfills are made to make the NPU driver work properly. **It is quite experimental and may not work on your device; you have been warned.** 

> **See Also** 
> 
> Keep an eye on [Tomeu Vizoso's blog](https://blog.tomeuvizoso.net/) as he is working towards a fully open-source NPU driver for rockchip devices by reverse engineering.

#### Known Problems of the Kernel
(1) In my case, power model is not working but it does NOT affect the functionality of NPU:

```
[    2.501015] RKNPU fde40000.npu: RKNPU: rknpu iommu is disabled, using non-iommu mode
[    2.503000] [drm] Initialized rknpu 0.9.3 20231121 for fde40000.npu on minor 1
[    2.503800] RKNPU fde40000.npu: bin=0
[    2.504027] RKNPU fde40000.npu: Failed to get leakage
[    2.507392] RKNPU fde40000.npu: avs=0
```

(2) ~~Only tasks submitted after the first initialization of RKNN Runtime can be executed. Once the runtime is created again, the NPU is likely not to work anymore until machine reboot.~~ **Solved by disabling RKNPU MMU (Memory Management Unit) in device tree.** Do not know the root cause yet.

<del>
<pre>
[  605.159276] RKNPU: failed to wait job, task counter: 0, flags: 0x5, ret = 0, elapsed time: 6160643us
[  605.267268] RKNPU: job timeout, flags: 0x0, irq status: 0x0, raw status: 0x0, require mask: 0x300, task counter: 0x0, elapsed time: 6268640us
[  605.375257] RKNPU: soft reset
[  607.915608] RKNPU: failed to wait job, task counter: 0, flags: 0x5, ret = -512, elapsed time: 2524485us
[  608.023253] RKNPU: job abort, flags: 0x0, ret: -512, elapsed time: 2632132us
</pre>
</del>

(3) WLAN driver for UWE5622 prints a lot of errors and stack traces in dmesg, but it does NOT affect the functionality of network adapter:

```
[   18.181010] sprdwl:sprdwl_rx_skb_process, drop loopback pkt, macaddr:24:b7:2a:a7:af:e9
[   19.206465] sprdwl:sprdwl_rx_skb_process, drop loopback pkt, macaddr:24:b7:2a:a7:af:e9
[   19.220338] sprdwl:sprdwl_rx_skb_process, drop loopback pkt, macaddr:24:b7:2a:a7:af:e9
```

### 3. linux-orangepi-3b-dev
My edge branch of linux-aarch64-rockchip-opi3b-npu-w568w. It is used for testing new features and patches, and may be unstable or even unbootable. **Use it at your own risk.**

> **Notes**
>
> You may want to cross-build it on a x86_64 machine with following options:
> 
> ```sh
> $ makepkg --syncdeps --config makepkg.conf
> ```
>