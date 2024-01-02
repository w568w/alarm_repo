CFLAGS=-static

qemu-aarch64-static-fast: qemu-aarch64-static-fast.c

install:
	install -t /usr/bin qemu-aarch64-static-fast
	install -t /etc/binfmt.d qemu-aarch64-static-fast.conf
	systemctl restart systemd-binfmt.service
