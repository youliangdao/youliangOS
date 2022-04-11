.file "api008.s"
        .equ    MALLOC_ADDR, 0x0020     # .hrbヘッダのmalloc領域
        .equ    DS_SIZE, 0x0000         # .hrbヘッダのデータセグメントサイズ
.arch i486

        .global api_initmalloc
.text
api_initmalloc: # void api_initmalloc(void);
        pushl   %ebx
        movl    $8, %edx
        movl    %cs:(MALLOC_ADDR), %ebx
        movl    %ebx, %eax
        addl    $32*1024, %eax
        movl    %cs:(DS_SIZE), %ecx
        subl    %eax, %ecx
        int     $0x40
        popl    %ebx
        ret