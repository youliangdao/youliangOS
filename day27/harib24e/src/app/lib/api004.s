.file "api004.s"
        .equ    MALLOC_ADDR, 0x0020     # .hrbヘッダのmalloc領域
        .equ    DS_SIZE, 0x0000         # .hrbヘッダのデータセグメントサイズ
.arch i486

        .global api_openwin
.text
api_openwin:    # int api_openwin(char *buf, int xsiz, int ysiz, int col_inv, char *title);
        pushl   %edi
        pushl   %esi
        pushl   %ebx
        movl    $5, %edx
        movl    16(%esp), %ebx  # buf
        movl    20(%esp), %esi  # xsiz
        movl    24(%esp), %edi  # ysiz
        movl    28(%esp), %eax  # col_inv
        movl    32(%esp), %ecx  # title
        int     $0x40

        popl    %ebx
        popl    %esi
        popl    %edi
        ret