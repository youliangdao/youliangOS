.file "api018.s"
        .equ    MALLOC_ADDR, 0x0020     # .hrbヘッダのmalloc領域
        .equ    DS_SIZE, 0x0000         # .hrbヘッダのデータセグメントサイズ
.arch i486

        .global api_freetimer
.text
api_freetimer:  # void api_freetimer(int timer)
        pushl   %ebx
        movl    $19, %edx
        movl    8(%esp), %ebx
        int     $0x40
        popl    %ebx
        ret