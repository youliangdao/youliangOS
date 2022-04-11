.file "api016.s"
        .equ    MALLOC_ADDR, 0x0020     # .hrbヘッダのmalloc領域
        .equ    DS_SIZE, 0x0000         # .hrbヘッダのデータセグメントサイズ
.arch i486

        .global api_inittimer
.text
api_inittimer:  # void api_inittimer(int timer, int data)
        pushl   %ebx
        movl    $17, %edx
        movl    8(%esp), %ebx   # timer
        movl    12(%esp), %eax  # data
        int     $0x40
        popl    %ebx
        ret