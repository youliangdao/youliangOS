.file "api013.s"
        .equ    MALLOC_ADDR, 0x0020     # .hrbヘッダのmalloc領域
        .equ    DS_SIZE, 0x0000         # .hrbヘッダのデータセグメントサイズ
.arch i486

        .global api_linewin
.text
api_linewin:    # void api_linewin(int win, int x0, int y0, int x1, int y1, int col)
        pushl   %edi
        pushl   %esi
        pushl   %ebp
        pushl   %ebx
        movl    $13, %edx
        movl    20(%esp), %ebx  # win
        movl    24(%esp), %eax  # x0
        movl    28(%esp), %ecx  # y0
        movl    32(%esp), %esi  # x1
        movl    36(%esp), %edi  # y1
        movl    40(%esp), %ebp  # col
        int     $0x40
        popl    %ebx
        popl    %ebp
        popl    %esi
        popl    %edi
        ret