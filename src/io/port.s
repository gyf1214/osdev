.section .text
.align 4

.global outb
.type outb, @function
outb:
    movw 4(%esp), %dx
    movb 8(%esp), %al
    outb %al, %dx
    ret
.size outb, . - outb

.global outw
.type outw, @function
outw:
    movw 4(%esp), %dx
    movw 8(%esp), %ax
    outw %ax, %dx
    ret
.size outw, . - outw

.global outl
.type outl, @function
outl:
    movw 4(%esp), %dx
    movl 8(%esp), %eax
    outl %eax, %dx
    ret
.size outl, . - outl

.global inb
.type inb, @function
inb:
    movw 4(%esp), %dx
    inb %dx, %al
    ret
.size inb, . - inb

.global inw
.type inw, @function
inw:
    movw 4(%esp), %dx
    inw %dx, %ax
    ret
.size inw, . - inw

.global inl
.type inl, @function
inl:
    movw 4(%esp), %dx
    inl %dx, %eax
    ret
.size inl, . - inl;

.macro ins s
.global ins\s
.type ins\s, @function
ins\s:
    pushl %edi
    movw 8(%esp), %dx
    movl 12(%esp), %edi
    movl 16(%esp), %ecx
    cld
    rep ins\s
    popl %edi
    ret
.size ins\s, . - ins\s
.endm

.macro outs s
.global outs\s
.type outs\s, @function
outs\s:
    pushl %esi
    movw 8(%esp), %dx
    movl 12(%esp), %esi
    movl 16(%esp), %ecx
    cld
    rep outs\s
    popl %esi
    ret
.size outs\s, . - outs\s
.endm

ins b
ins w
ins l

outs b
outs w
outs l

.global ioWait
.type ioWait, @function
ioWait:
    xorl %eax, %eax
    outb %al, $0x80
    ret
.size ioWait, . - ioWait
