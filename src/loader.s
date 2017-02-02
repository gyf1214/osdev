.set Align, 1 << 0
.set MemInfo, 1 << 1
.set MagicNumber, 0x1BADB002
.set Flags, Align | MemInfo
.set Checksum, -(MagicNumber + Flags)
.set StackSize, 0x1000
.set PageSize, 0x1000
.set FirstPage, 0x83
.set GlobalOffset, 0xc0000000

.section .multiboot
.align 4
    .long MagicNumber
    .long Flags
    .long Checksum

.section .bss

.align 0x1000
.global kPDT
.type kPDT, @object
kPDT:
    .skip PageSize
.size kPDT, . - kPDT

_kPDT = kPDT - GlobalOffset

.align 4
.global kStack
.type kStack, @object
kStack:
    .skip StackSize
.size kStack, . - kStack

.section .text
.align 4

.global loader
.type loader, @function
loader:
    movl $FirstPage, _kPDT
    movl $FirstPage, _kPDT + (GlobalOffset >> 20)

    movl $_kPDT, %ecx
    movl %ecx, %cr3
    invlpg 0

    movl %cr4, %ecx
    orl $0x10, %ecx
    movl %ecx, %cr4

    movl %cr0, %ecx
    orl $0x80000000, %ecx
    movl %ecx, %cr0

    pushl $.Flush
    ret
.Flush:
    movl $kStack, %esp
    movl $kStack, %ebp
    pushl %ebx
    call kmain
    cli
.L:
    hlt
    jmp .L
.size loader, . - loader
