void io_hlt(void);
void write_mem8(int addr, int data);

void HariMain(void)
{
    int i;  // 変数宣言。iというのは、4byteの整数型
    char *p;    // *pという変数は、BYTE[...]用の番地

    for ( i = 0xa0000; i <= 0xaffff; i++)
    {
        p = (char *)i;  // 番地を代入
        *p = i & 0x0f;
    }

    for (;;)
    {
        io_hlt();
    }
    
}