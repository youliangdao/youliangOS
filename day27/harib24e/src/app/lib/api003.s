.file "api003.s"
        .equ    MALLOC_ADDR, 0x0020     # .hrbヘッダのmalloc領域
        .equ    DS_SIZE, 0x0000         # .hrbヘッダのデータセグメントサイズ
.arch i486

        .global api_end
.text
api_end:        # void api_end(void)
        movl $4, %edx
        int $0x40