# FAT12 フロッピーディスクのための記述
	.byte	0xeb, 0x4e, 0x90
	.ascii 	"HELLOIPL"	# ブートセクタの名前(8バイト)
	.word 	512		# 1セクタのサイズ
	.byte 	1		# クラスタのサイズ
	.word 	1		# FATの開始位置
	.byte 	2		# FATの個数
	.word 	224		# ルートディレクトリ領域の大きさ
	.word	2880		# このドライブのセクタ数
	.byte	0xf0		# メディアのタイプ(固定)
	.word	9		# FAT領域のセクタ数
	.word	18		# 1トラックのセクタ数
	.word	2		# ヘッドの数
	.int	0		# パーティションの数(使ってないので0)
	.int	2880		# ドライブの大きさをもう一度
	.byte	0, 0, 0x29	# 不明
	.int	0xffffffff	# ボリュームシリアル番号？
	.ascii	"HELLO-OS   "	# ディスクの名前(11バイト)
	.ascii	"FAT12   "	# フォーマットの名前(8バイト)
	.skip	18, 0x00	# 18バイト空けておく

# プログラム本体	
	.byte 	0xb8, 0x00, 0x00, 0x8e, 0xd0, 0xbc, 0x00, 0x7c, 0x8e, 0xd8, 0x8e, 0xc0, 0xbe, 0x74, 0x7c, 0x8a
	.byte 	0x04, 0x83, 0xc6, 0x01, 0x3c, 0x00, 0x74, 0x09, 0xb4, 0x0e, 0xbb, 0x0f, 0x00, 0xcd, 0x10, 0xeb
	.byte 	0xee, 0xf4, 0xeb, 0xfd

# メッセージ部分	
	.byte	0x0a, 0x0a	# 改行を2つ
	.ascii	"hello, world"
	.byte 	0x0a		# 改行
	.byte 	0

	.org	0x1fe, 0x00	# 0x1f0まで、0で埋める
	
	.byte	0x55, 0xaa

# 以下はブートセクタ以外の部分の記述
	.byte 	0xf0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00
	.skip 	4600, 0x00
	.byte 	0xf0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00
	.skip 	1469432, 0x00