.file "api009.s"
        .equ    MALLOC_ADDR, 0x0020     # .hrbヘッダのmalloc領域
        .equ    DS_SIZE, 0x0000         # .hrbヘッダのデータセグメントサイズ
.arch i486

        .global api_malloc
.text
api_malloc:     # char *api_malloc(int size);
        pushl   %ebx
        movl    $9, %edx
        movl    %cs:(MALLOC_ADDR), %ebx
        movl    8(%esp), %ecx   # size
        int     $0x40
        popl    %ebx
        ret