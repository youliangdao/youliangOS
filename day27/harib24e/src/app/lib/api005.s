.file "api005.s"
        .equ    MALLOC_ADDR, 0x0020     # .hrbヘッダのmalloc領域
        .equ    DS_SIZE, 0x0000         # .hrbヘッダのデータセグメントサイズ
.arch i486

        .global api_closewin
.text
api_closewin:   # void api_closewin(int win);
        pushl   %ebx
        movl    $14, %edx
        movl    8(%esp), %ebx   # win
        int     $0x40
        popl    %ebx
        ret