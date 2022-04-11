.file "api012.s"
        .equ    MALLOC_ADDR, 0x0020     # .hrbヘッダのmalloc領域
        .equ    DS_SIZE, 0x0000         # .hrbヘッダのデータセグメントサイズ
.arch i486

        .global api_refreshwin
.text
api_refreshwin: # void api_refreshwin(int win, int x0, int y0, int x1, int y1)
        pushl   %edi
        pushl   %esi
        pushl   %ebx
        movl    $12, %edx
        movl    16(%esp), %ebx  # win
        movl    20(%esp), %eax  # x0
        movl    24(%esp), %ecx  # y0
        movl    28(%esp), %esi  # x1
        movl    32(%esp), %edi  # y1
        int     $0x40
        popl    %ebx
        popl    %esi
        popl    %edi
        ret