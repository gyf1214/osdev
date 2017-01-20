# OS Dev #

Learning OS development

## How to build ##

Since I use both x86-64 Mac OS X as host os & GRUB to boot kernel, so I use cross gcc & binutils (for elf32-i386)

So change toolchain in `makefile` if needed

`mkisofs` (which is available on Mac) is used as the tool to generate iso files

Just `make all` to build the final `os.iso`

## Running ##

~~`bochs` is used as a x86 simulator and debugger, a default `.bochsrc` is provided~~

Switch to `qemu` to enable debugging with `gdb`

A `.gdbinit` is provided to configure & link `gdb` with `qemu`

The boot loader is GRUB 0.97, using `stage2_eltorito` for ISO

Both the GRUB binary and `menu.lst` are provided

~~Use `make run` to start the simulator if `bochs` is installed~~

Use `make qemu` to start the simulator __in background__

Use `make run` to start both the simulator and `gdb`, which the simulator will then stop at BIOS boot loader

In `gdb`, customer function `re` is defined to restart the simulator when __it is killed__

Annoyingly, `Ctrl-C` (Signal 2) will kill the background simulator in `gdb` and a solution has not been found on OS X

## Progress ##

- ~~Bare Bones~~ -> 968c88af0338d79dabe5114f52da91cae860e82c
- ~~Segmentation~~ -> f4882b4e8177e5b4e5ba87804d9a2dc5b8132d52
- ~~Debug Device COM1~~ -> b0f295ca76443b21af12a9af9dae1fa52ec614b9
- ~~Generic Device Manager~~ -> e0d4bbfed3f568b1478fe21b154d751a3d67c826
- ~~Framebuffer~~ -> 8db4a0b7482592ded2f6b00db1ee78467cc12347
- ~~Allow Paging & Switch to Higher Address Kernel~~ -> 92258e005f70fcdd2475228ef433d821afe2ef1b
- ~~Switch to `qemu` & `gdb`~~ -> ca11c569b75c6a81e7a61e15cd94692fa3252d6c
- ~~Add `multiboot` Info~~ -> 9594267257011f0e429a4833deec862d7b6963c4
- ~~Rearrange Memory for Memory Manager~~ -> 14b2a7322ca5972e5312fc83eac047343d9f4f91
- ~~Kernel Object Manager~~ -> eb4d5532e949044f393a4bf1ef1d987b86868847
- ~~Interrupt~~ -> b4bde8ede239956f3133bfa237495e8fd8044bd2
- ATA/ATAPI Disk
- Filesystem ISO9660
- Frame Allocator
- User Mode Paging
- ELF Loader

## Author ##

Tiny

## License ##

MIT

## Reference ##

- [《x86汇编语言：从实模式到保护模式》](https://www.amazon.cn/dp/B00AR0ZSVO/)
- [『30日でできる! OS自作入門』](https://www.amazon.co.jp/dp/4839919844)
- [The little book about OS development](https://littleosbook.github.io/)
- [OSDev.org](http://www.osdev.org/)
