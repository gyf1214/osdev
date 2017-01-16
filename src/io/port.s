.section .text
.align 4

.global outb
.type outb, @function
outb:
    movw 4(%esp), %dx
    movb 8(%esp), %al
    outb %al, %dx
    ret

.global outw
.type outw, @function
outw:
    movw 4(%esp), %dx
    movw 8(%esp), %ax
    outw %ax, %dx
    ret

.global outl
.type outl, @function
outl:
    movw 4(%esp), %dx
    movl 8(%esp), %eax
    outl %eax, %dx
    ret

.global inb
.type inb, @function
inb:
    movw 4(%esp), %dx
    inb %dx, %al
    ret

.global inw
.type inw, @function
inw:
    movw 4(%esp), %dx
    inw %dx, %ax
    ret

.global inl
.type inl, @function
inl:
    movw 4(%esp), %dx
    inl %dx, %eax
    ret
