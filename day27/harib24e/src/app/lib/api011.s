.file "api011.s"
        .equ    MALLOC_ADDR, 0x0020     # .hrbヘッダのmalloc領域
        .equ    DS_SIZE, 0x0000         # .hrbヘッダのデータセグメントサイズ
.arch i486

        .global api_point
.text
api_point:      # void api_point(int win, int x, int y, int col);
        pushl   %edi
        pushl   %esi
        pushl   %ebx
        movl    $11, %edx
        movl    16(%esp), %ebx  # win
        movl    20(%esp), %esi  # x
        movl    24(%esp), %edi  # y
        movl    28(%esp), %eax  # col
        int     $0x40
        popl    %ebx
        popl    %esi
        popl    %edi
        ret