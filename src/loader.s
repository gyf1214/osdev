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
.align 4
kernelStackBottom:
    .skip StackSize
kernelStackTop:

.align 0x1000
.global kPDT
.type kPDT, @object
.size kPDT, PageSize
kPDT:
    .skip PageSize

_kPDT = kPDT - GlobalOffset

.section .text
.align 4

.global loader
.type loader, @function
loader = _loader - GlobalOffset
_loader:
    movl $FirstPage, _kPDT
    movl $FirstPage, _kPDT + (GlobalOffset >> 20)

    movl $_kPDT, %ecx
    movl %ecx, %cr3

    movl %cr4, %ecx
    orl $0x10, %ecx
    movl %ecx, %cr4

    movl %cr0, %ecx
    orl $0x80000000, %ecx
    movl %ecx, %cr0

    movl $.Flush, %ecx
    jmp %ecx
.Flush:
    movl $kernelStackTop, %esp
    movl $kernelStackTop, %ebp
    call kmain
    cli
.L:
    hlt
    jmp .L
