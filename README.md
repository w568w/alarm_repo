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

See [OpenSUSE Wiki](https://en.opensuse.org/ARM_Mali_GPU) for more information.