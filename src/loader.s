.set Align, 1 << 0
.set MemInfo, 1 << 1
.set MagicNumber, 0x1BADB002
.set Flags, Align | MemInfo
.set Checksum, -(MagicNumber + Flags)
.set StackSize, 0x1000

.section .multiboot
.align 4
    .long MagicNumber
    .long Flags
    .long Checksum


.section .bss
.align 4
kernel_stack_bottom:
    .skip StackSize
kernel_stack_top:

.section .text
.global loader
.type loader, @function
loader:
    movl $kernel_stack_top, %esp
    movl $kernel_stack_top, %ebp
    call kmain
    cli
.L:
    hlt
    jmp .L
