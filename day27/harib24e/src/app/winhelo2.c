#include "apilib.h"

char buf[150 * 150];

void HariMain(void)
{
    int win;
    win = api_openwin(buf, 150, 50, -1, "hello");
    api_boxfilwin(win, 8, 36, 141, 43, 3);  // 黄色
    api_putstrwin(win, 28, 28, 0, 12, "hello world!");  // 黒
    api_end();
}