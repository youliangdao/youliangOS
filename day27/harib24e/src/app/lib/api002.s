.file "api002.s"
        .equ    MALLOC_ADDR, 0x0020     # .hrbヘッダのmalloc領域
        .equ    DS_SIZE, 0x0000         # .hrbヘッダのデータセグメントサイズ
.arch i486

        .global api_putstr0
.text
api_putstr0:	# void api_putstr0(char *s);
	pushl	%ebx
	movl	$2, %edx
	movl	8(%esp), %ebx	# s
	int		$0x40
	popl	%ebx
	ret