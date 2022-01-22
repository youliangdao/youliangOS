	.file "helloos.s"
	.equ	CYLS, 10
	
.code16
.text
	jmp entry		# entryから処理を開始する
	
	# FAT12 フロッピーディスクであることの宣言
	.byte	0x90
	.ascii 	"HariIPL"	# ブートセクタの名前(8バイト)
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
	.ascii	"Haribote   "	# ディスクの名前(11バイト)
	.ascii	"FAT12   "	# フォーマットの名前(8バイト)
	.skip	18, 0x00	# 18バイト空けておく
	
entry:	# プログラム本体	
	# 各種レジスタの初期化
	movw	$0, %ax
	movw	%ax, %ss
	movw	$0x7c00, %sp
	movw	%ax, %ds

	# ディスクを読む
	movw	$0x0820, %ax
	movw	%ax, %es
	movb	$0, %ch			# シリンダ0
	movb	$0x00, %dh		# ヘッド0
	movb	$2,	%cl			# セクタ2
	
readloop:
	movw	$0, %si			# 失敗回数を数えるレジスタ
retry:
	movb	$0x02, %ah		# AH=0x02 ; ディスク読み込み
	movb	$1, %al			# 1セクタ分
	movw	$0, %bx
	movb	$0x00, %dl		# Aドライブ
	int		$0x13
	jnc		next
	addw	$1, %si			# siに1を足す
	cmpw	$5, %si			# siと5を比較
	jae		error			# si >= 5 ならerrorへ
	movb	$0x00, %ah
	movb	$0x00, %dl		# Aドライブ
	int		$0x13			# ドライブのリセット
	jmp		retry
next:
	movw	%es, %ax
	addw	$0x0020, %ax
	movw	%ax, %es		# アドレスを1セクタ分(512)進める
	addb	$1,	%cl			# セクタを1つ進める
	cmpb	$18, %cl		# clと18を比較
	jbe		readloop		# cl <= 18ならreadloopへ
	movb	$1, %cl
	addb	$1, %dh
	cmpb	$2, %dh
	jb		readloop		# dh < 2ならreadloopへ
	movb	$0, %dh
	addb	$1, %ch
	cmpb	CYLS, %ch
	jb		readloop		# ch < CYLSならreadloopへ

	# ディスク読み込み完了後OS本体を実行
	jmp		0xc200

fin:	# エラーがなければ何もせず終了
	hlt
	jmp		fin

error:	# エラーがあればメッセージを表示	
	movw	$msg, %si
	
putloop: # 文字表示ループ。NUL文字が来るまで、ソフトウェア割り込み命令を使って、文字を表示していく。
	movb	(%si), %al
	addw	$1, %si
	cmpb	$0, %al		# NUL文字かどうか？
	je	fin		# NUL文字だったら、終了へ
	movb	$0x0e, %ah	# 1文字表示ファンクション
	movw	$15, %bx	# カラーコード
	int	$0x10		# ビデオBIOS呼び出し
	jmp	putloop

msg:	# メッセージ部分
	.byte	0x0a, 0x0a	# 改行を2つ
	.ascii	"load error"
	.byte 	0x0a		# 改行
	.byte 	0		# NUL文字

	.org	0x1fe, 0x00	# 0x1f0まで、0で埋める
	
	.byte	0x55, 0xaa	# ブート・シグニチャ(このマジックナンバーがないとマスターブートレコードとして有効にならない)