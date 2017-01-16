.section .text
.align 4

.global segLoadDS
.type segLoadDS, @function
segLoadDS:
    movw 4(%esp), %ds
    ret

.global segLoadES
.type segLoadES, @function
segLoadES:
    movw 4(%esp), %es
    ret

.global segLoadFS
.type segLoadFS, @function
segLoadFS:
    movw 4(%esp), %fs
    ret

.global segLoadGS
.type segLoadGS, @function
segLoadGS:
    movw 4(%esp), %gs
    ret

.global segLoadSS
.type segLoadSS, @function
segLoadSS:
    movw 4(%esp), %ss
    ret


.global segLoadCS
.type segLoadCS, @function
segLoadCS:
    movzwl 4(%esp), %eax
    pushl %eax
    pushl $.L
    lret
.L:
    ret

.global segLoadGDT
.type segLoadGDT, @function
segLoadGDT:
    movl 4(%esp), %eax
    lgdt (%eax)
    ret
