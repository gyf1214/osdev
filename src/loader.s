.text
.globl loader
.align 4

MagicNumber = 0x1BADB002
Flags       = 0x0
Checksum    = - MagicNumber - Flags
StackSize   = 0x1000

header:
    .long MagicNumber
    .long Flags
    .long Checksum

loader:
    movl $kernel_stack_top, %esp
    movl $kernel_stack_top, %ebp
    call kmain
    hlt

.bss
.align 4

kernel_stack_bottom:
    .skip StackSize
kernel_stack_top:
