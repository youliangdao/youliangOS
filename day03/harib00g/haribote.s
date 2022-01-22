    .file   "haribote.s"

.code16
.text

        movb    $0x13, %al      # VGAグラフィックス、320*200*8bitカラー
        movb    $0x00, %ah
        int     $0x10
fin:
        hlt
        jmp fin