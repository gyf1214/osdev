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

.global insb
.type insb, @function
insb:
    movw 4(%esp), %dx
    movl 8(%esp), %edi
    movl 12(%esp), %ecx
    cld
    rep insb
    ret
.size insb, . - insb

.global insw
.type insw, @function
insw:
    movw 4(%esp), %dx
    movl 8(%esp), %edi
    movl 12(%esp), %ecx
    cld
    rep insw
    ret
.size insw, . - insw

.global insl
.type insl, @function
insl:
    movw 4(%esp), %dx
    movl 8(%esp), %edi
    movl 12(%esp), %ecx
    cld
    rep insl
    ret
.size insl, . - insl

.global ioWait
.type ioWait, @function
ioWait:
    xorl %eax, %eax
    outb %al, $0x80
    ret
.size ioWait, . - ioWait
