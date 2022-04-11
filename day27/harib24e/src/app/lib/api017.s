.file "api017.s"
        .equ    MALLOC_ADDR, 0x0020     # .hrbヘッダのmalloc領域
        .equ    DS_SIZE, 0x0000         # .hrbヘッダのデータセグメントサイズ
.arch i486

        .global api_settimer
.text
api_settimer:   # void api_settimer(int timer, int time)
        pushl   %ebx
        movl    $18, %edx
        movl    8(%esp), %ebx   # timer
        movl    12(%esp), %eax  # time
        int     $0x40
        popl    %ebx
        ret