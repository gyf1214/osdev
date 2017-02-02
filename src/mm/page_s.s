.section .text
.align 4

.global pageLoadCR3
.type pageLoadCR3, @function
pageLoadCR3:
    movl 4(%esp), %eax
    movl %eax, %cr3
    ret
.size pageLoadCR3, . - pageLoadCR3

.global pageFlushTLB
.type pageFlushTLB, @function
pageFlushTLB:
    movl 4(%esp), %eax
    invlpg (%eax)
    ret
.size pageFlushTLB, . - pageFlushTLB
