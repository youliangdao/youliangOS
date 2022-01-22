        .file   "haribote.s"
                # BOOT_INFO関係
                .equ    CYLS,   0x0ff0  # IPLが設定する
                .equ    LEDS,   0x0ff1  # Keyboardの状態
                .equ    VMODE,  0x0ff2  # 色数に関する情報。何ビットカラーか？
                .equ    SCRNX,  0x0ff4  # 解像度のX（screen x）
                .equ    SCRNY,  0x0ff6  # 解像度のY（screen y）
                .equ    VRAM,   0x0ff8  # グラフィックバッファの開始番地
.code16
.text

        # 画面モードの切り替え
        movb    $0x13, %al      # VGAグラフィックス、320*200*8bitカラー
        movb    $0x00, %ah
        int     $0x10

        # 画面モードをメモする
        movb    $8, (VMODE)
        movw    $320, (SCRNX)
        movw    $200, (SCRNY)
        movl    $0x00a0000, (VRAM)

        # キーボードのLED状態をBIOSに教えてもらう
        movb    $0x02, %ah
        int     $0x16
        movb    %al, (LEDS)
fin:
        hlt
        jmp fin