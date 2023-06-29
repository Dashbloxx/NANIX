# NANIX
## About
NANIX is a UNIX-like kernel written for the i386 architecture. NANIX is inspired by MINIX, to be used for computing research.
## Building
Building is easy, you'll need either a x86 cross-compiler, or the default compiler on a x86 machine. After that, execute the Makefile, and you'll have the kernel built. Then, you'll need to build the initial ramdisk, which is a simple filesystem that is to be used to test the different components of the kernel. Run `make initrd` to generate the initrd. You'll need root permissions to make the initial ramdisk image.
## Testing
To test NANIX, you can use a bootloader tool to create a bootable disk image that can be used to boot NANIX on real hardware. If you want to use an emulator like QEMU however, you can simply run `qemu-system-i386 -kernel kernel.bin -initrd initrd.fat`. Make sure you have QEMU installed before running this command, or else the command execution won't work.
