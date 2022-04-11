#include "apilib.h"

int rand(void);     // 0~32767の範囲で乱数を発生

void HariMain(void)
{
    char *buf;
    int win, i, x, y;
    api_initmalloc();

    buf = api_malloc(150 * 100);
    win = api_openwin(buf, 150, 100, -1, "stars2");
    api_boxfilwin(win + 1, 6, 26, 143, 93, 0);  // 黒
    for ( i = 0; i < 50; i++)
    {
        x = (rand() % 137) + 6;
        y = (rand() % 67) + 26;
        api_point(win + 1, x, y, 3);    // 黄色
    }
    api_refreshwin(win, 6, 26, 144, 94);
    api_end();
}

unsigned long int rand_num = 1;

int rand(void)
{
    rand_num = rand_num * 1103515245 + 12345;
    return (unsigned int)(rand_num / 0x65536) % 0x32768;
}