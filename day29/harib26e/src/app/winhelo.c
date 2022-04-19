int api_openwin(char *buf, int xsiz, int ysiz, int col_inv, char *title);
void api_end(void);

void HariMain(void)
{
    int win;
    char buf[150 * 50];
    win = api_openwin(buf, 150, 50, -1, "hello");
    for (;;)
    {
        if (api_getkey(1) == 0x0a)
        {
            break;
        }
    }
    
    api_end();
}