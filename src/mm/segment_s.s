.section .text
.align 4

.global segLoadDS
.type segLoadDS, @function
segLoadDS:
    movw 4(%esp), %ds
    ret
.size segLoadDS, . - segLoadDS

.global segLoadES
.type segLoadES, @function
segLoadES:
    movw 4(%esp), %es
    ret
.size segLoadES, . - segLoadES

.global segLoadFS
.type segLoadFS, @function
segLoadFS:
    movw 4(%esp), %fs
    ret
.size segLoadFS, . - segLoadFS

.global segLoadGS
.type segLoadGS, @function
segLoadGS:
    movw 4(%esp), %gs
    ret
.size segLoadGS, . - segLoadGS

.global segLoadSS
.type segLoadSS, @function
segLoadSS:
    movw 4(%esp), %ss
    ret
.size segLoadSS, . - segLoadSS


.global segLoadCS
.type segLoadCS, @function
segLoadCS:
    movzwl 4(%esp), %eax
    pushl %eax
    pushl $.L
    lret
.L:
    ret
.size segLoadCS, . - segLoadCS

.global segLoadGDT
.type segLoadGDT, @function
segLoadGDT:
    movl 4(%esp), %eax
    lgdt (%eax)
    ret
.size segLoadGDT, . - segLoadGDT
