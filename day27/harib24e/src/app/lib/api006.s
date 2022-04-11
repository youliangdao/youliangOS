.file "api006.s"
        .equ    MALLOC_ADDR, 0x0020     # .hrbヘッダのmalloc領域
        .equ    DS_SIZE, 0x0000         # .hrbヘッダのデータセグメントサイズ
.arch i486

        .global api_putstrwin
.text
api_putstrwin:  # void api_putstrwin(int win, int x, int y, int col, int len, char *str);
        pushl   %edi
        pushl   %esi
        pushl   %ebp
        pushl   %ebx
        movl    $6, %edx
        movl    20(%esp), %ebx  # win
        movl    24(%esp), %esi  # x
        movl    28(%esp), %edi  # y
        movl    32(%esp), %eax  # col
        movl    36(%esp), %ecx  # len
        movl    40(%esp), %ebp  # str
        int     $0x40
        popl    %ebx
        popl    %ebp
        popl    %esi
        popl    %edi
        ret