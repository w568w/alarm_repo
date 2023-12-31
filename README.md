# Personal ArchLinux ARM Repo
Some personally maintained packages that are unsuitable for AUR will be hosted here.

## Packages
### libmali-bifrost-g52-g13p0-x11-gbm
A closed-source Bifrost Mali driver (userspace part) for Mali G52.

It provides OpenCL and OpenGL ES support on Orangepi 3B.

Repacked from <https://github.com/orangepi-xunlong/rk-rootfs-build/>.

#### Notes
To utilize this GPU, you have to choose only one of the following options:

1. Open-sourced upstream software:
    - Kernel modules: Panfrost ([need to be enabled](https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/drivers/gpu/drm/panfrost/Kconfig) in mainline kernel, **NOT** in OrangePi OS)
    - Userspace: [Mesa with Panfrost support](https://docs.mesa3d.org/drivers/panfrost.html) (just `pacman -S mesa` may work)
2. Closed-sourced software:
    - Kernel modules: Mali GPU kernel modules (already built in OrangePi OS, **NOT** in mainline kernel)
    - Userspace: **This package** (just `makepkg -si` it)

`linux-orangepi-3b` in this repository has Panfrost enabled.

See [OpenSUSE Wiki](https://en.opensuse.org/ARM_Mali_GPU) for more information.

### linux-orangepi-3b
The Linux kernel and modules with my own patches for Orangepi 3B. Adapted from (and would be synced with) [@SUISHUI's repository](https://github.com/SUISHUI/linux-orangepi-3b).

It should be kept up-to-date with upstream kernel, rather than full of patches and dirty hacks, or even diverged from upstream (**saying you, [Rockchip](https://github.com/rockchip-linux/kernel/tree/develop-5.10) and [Xunlong](https://github.com/orangepi-xunlong/linux-orangepi/blob/orange-pi-5.10-rk35xx/)!**)

#### Features
It can be a drop-in replacement of the default kernel (usually called `linux-rk3566-legacy`) in OrangePi OS (based on Archlinux ARM).

Compared with upstream kernel, it is patched with following features:

1. Add **device tree** for Orangepi 3B
2. Add **WiFi** driver for UWE5622
3. Add **NPU** driver for RK3566 (**see notes below!**)

[Panfrost](https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/drivers/gpu/drm/panfrost/) kernel module is included and enabled by default. So you can use it with [Mesa 3D](https://docs.mesa3d.org/drivers/panfrost.html) to enjoy **OpenGL ES and OpenCL on your GPU** too.

#### Notes 
You may want to cross-build it on a x86_64 machine with following options:

```sh
$ makepkg --syncdeps --config makepkg.conf
```

RKNPU driver is migrated by myself from downstream kernels [rockchip-linux/kernel](https://github.com/rockchip-linux/kernel/tree/develop-5.10) and [orangepi-xunlong/linux-orangepi](https://github.com/orangepi-xunlong/linux-orangepi/blob/orange-pi-5.10-rk35xx/). A lot of changes and polyfills are made to make it work properly. **It is quite experimental and may not work on your device; you have been warned.** 

##### Known Problems of RKNPU
(1) In my case, power model is not working but it does not affect the functionality of NPU:

```
[   23.948577] RKNPU fde40000.npu: deferred probe timeout, ignoring dependency
[   23.950313] RKNPU fde40000.npu: RKNPU: rknpu iommu is enabled, using iommu mode
[   23.954131] [drm] Initialized rknpu 0.8.2 20220829 for fde40000.npu on minor 2
[   23.955842] RKNPU fde40000.npu: Failed to get npu_leakage
[   23.960750] RKNPU fde40000.npu: avs=0
[   23.961574] RKNPU fde40000.npu: RKNPU: failed to initialize power model
[   23.961587] RKNPU fde40000.npu: RKNPU: failed to get dynamic-coefficient
```

(2) Only tasks submitted after the first initialization of RKNN Runtime can be executed. **Once the runtime is destroyed and created again, the NPU will not work anymore**:

```
[  605.159276] RKNPU: failed to wait job, task counter: 0, flags: 0x5, ret = 0, elapsed time: 6160643us
[  605.267268] RKNPU: job timeout, flags: 0x0, irq status: 0x0, raw status: 0x0, require mask: 0x300, task counter: 0x0, elapsed time: 6268640us
[  605.375257] RKNPU: soft reset
[  607.915608] RKNPU: failed to wait job, task counter: 0, flags: 0x5, ret = -512, elapsed time: 2524485us
[  608.023253] RKNPU: job abort, flags: 0x0, ret: -512, elapsed time: 2632132us
```