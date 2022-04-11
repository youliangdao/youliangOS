.file "api014.s"
        .equ    MALLOC_ADDR, 0x0020     # .hrbヘッダのmalloc領域
        .equ    DS_SIZE, 0x0000         # .hrbヘッダのデータセグメントサイズ
.arch i486

        .global api_getkey
.text
api_getkey:     # int api_getkey(int mode)
        movl    $15, %edx
        movl    4(%esp), %eax
        int     $0x40
        ret