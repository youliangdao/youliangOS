    .equ    OS_ADR, 0x102600

.arch i486

.text
    movl    $1*8, %eax
    movw    %ax, %ds
    movw    $0, (OS_ADR)
    lret