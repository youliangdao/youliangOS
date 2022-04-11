.file "api015.s"
        .equ    MALLOC_ADDR, 0x0020     # .hrbヘッダのmalloc領域
        .equ    DS_SIZE, 0x0000         # .hrbヘッダのデータセグメントサイズ
.arch i486

        .global api_alloctimer
.text
api_alloctimer: # int api_alloctimer(void)
        movl    $16, %edx
        int     $0x40
        ret