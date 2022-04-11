.file "api001.s"
        .equ    MALLOC_ADDR, 0x0020     # .hrbヘッダのmalloc領域
        .equ    DS_SIZE, 0x0000         # .hrbヘッダのデータセグメントサイズ
.arch i486

        .global api_putchar
.text
api_putchar:    # void api_putchar(int c)
        movl $1, %edx
        movb 4(%esp), %al
        int $0x40
        ret