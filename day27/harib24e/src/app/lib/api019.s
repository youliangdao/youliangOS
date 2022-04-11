.file "api019.s"
        .equ    MALLOC_ADDR, 0x0020     # .hrbヘッダのmalloc領域
        .equ    DS_SIZE, 0x0000         # .hrbヘッダのデータセグメントサイズ
.arch i486

        .global api_beep
.text
api_beep:       # void api_beep(int tone)
        movl    $20, %edx
        movl    4(%esp), %eax   # tone
        int     $0x40
        ret