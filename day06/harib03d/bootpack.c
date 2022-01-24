#include "lib/mysprintf.h"
#include "bootpack.h"

void HariMain(void)
{
    struct BOOTINFO *binfo = (struct BOOTINFO *) ADR_BOOTINFO;
    char mcursor[16 * 16];
    char msg[128];
    int mx;
    int my;

    init_gdtidt();
    init_pic();

    init_palette(); // パレットを設定
    init_screen(binfo->vram, binfo->scrnx, binfo->scrny); 
    init_mouse_cursor8(mcursor, COL8_008484);

    // マウスカーソルを画面中心になるよう計算し描画
    mx = (binfo->scrnx - 16) / 2;
    my = (binfo->scrny - 28 - 16) / 2;
    putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);

    sprintf(msg, "(%d, %d)", mx, my);
    putfont8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, msg);

    for (;;)
    {
        io_hlt();
    }
}