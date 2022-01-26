#include "lib/mysprintf.h"
#include "bootpack.h"

#define EFLAGS_AC_BIT       0x00040000
#define CR0_CACHE_DISABLE   0x60000000

int load_cr0(void);
void store_cr0(int cr0);
unsigned int memtest(unsigned int start, unsigned int end);
unsigned int memtest_sub(unsigned int start, unsigned int end);

extern struct FIFO8 keyfifo, mousefifo;

void HariMain(void)
{
  struct BOOTINFO *binfo = (struct BOOTINFO *) ADR_BOOTINFO;
  char mcursor[16 * 16];
  char msg[256], s[16], keybuf[32], mousebuf[128];
  int mx;
  int my;
  int i;

  struct MOUSE_DEC mdec;

  init_gdtidt();
  init_pic();
  io_sti();	/* IDT/PICの初期化が完了したので、CPUの割り込み禁止を解除 */
  
  fifo8_init(&keyfifo, 32, keybuf);
  fifo8_init(&mousefifo, 128, mousebuf);
  io_out8(PIC0_IMR, 0xf9); /* PIC1とキーボードを許可(11111001) */
  io_out8(PIC1_IMR, 0xef); /* マウスを許可(11101111) */
  init_keyboard();
  
  init_palette();
  init_screen(binfo->vram, binfo->scrnx, binfo->scrny);
  init_mouse_cursor8(mcursor, COL8_008484);

  /* マウス・カーソルを画面中心になるように計算し描画 */
  mx = (binfo->scrnx - 16) / 2;
  my = (binfo->scrny - 28 - 16) / 2;
  putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);
  
  sprintk(msg, "(%d, %d)", mx, my);
  putfont8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, msg);

  enable_mouse(&mdec);

  i = memtest(0x00400000, 0xbfffffff) / (1024 * 1024);
  sprintk(s, "memory %dMB", i);
  putfont8_asc(binfo->vram, binfo->scrnx, 0, 32, COL8_FFFFFF, s);

  for (;;) {
    io_cli();
    if (fifo8_status(&keyfifo) + fifo8_status(&mousefifo) == 0) {
      io_stihlt();
    } else {
      if (fifo8_status(&keyfifo) != 0) {
	      i = fifo8_get(&keyfifo);
	      io_sti();
      
	      sprintk(s, "%02X", i);
	      boxfill8(binfo->vram, binfo->scrnx, COL8_008484, 0, 16, 15, 31);
	      putfont8_asc(binfo->vram, binfo->scrnx, 0, 16, COL8_FFFFFF, s);
      } else if (fifo8_status(&mousefifo) != 0) {
	      i = fifo8_get(&mousefifo);
      	io_sti();

        if (mouse_decode(&mdec, i) != 0)
        {
    	     /* データが3バイト揃ったので表示 */
	        sprintk(s, "[lcr %d %d]", mdec.x, mdec.y);
          if ((mdec.btn & 0x01) != 0 )
          {
            s[1] = 'L';
          }
          if ((mdec.btn & 0x02) != 0 )
          {
            s[3] = 'R';
          }
          if ((mdec.btn & 0x04) != 0 )
          {
            s[2] = 'C';
          }
	        boxfill8(binfo->vram, binfo->scrnx, COL8_008484, 32, 16, 32 + 15 * 8 - 1, 31);
	        putfont8_asc(binfo->vram, binfo->scrnx, 32, 16, COL8_FFFFFF, s);
          // マウスカーソルの移動
          boxfill8(binfo->vram, binfo->scrnx, COL8_008484, mx, my, mx + 15, my + 15);   // マウス消す
          mx += mdec.x;
          my += mdec.y;
          if (mx < 0)
          {
            mx = 0;
          }
          if (my < 0)
          {
            my = 0;
          }
          if (mx > binfo->scrnx - 16)
          {
            mx = binfo->scrnx - 16;
          }
          if (my > binfo->scrny - 16)
          {
            my = binfo->scrny - 16;
          }
          sprintk(s, "(%3d, %3d)", mx, my);
          boxfill8(binfo->vram, binfo->scrnx, COL8_008484, 0, 0, 79, 15);   // 座標消す
          putfont8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, s);    // 座標書く
          putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);  // マウス書く
          
        }
      }
    }
  }
}

unsigned int memtest(unsigned int start, unsigned int end)
{
  char flag486 = 0;
  unsigned int eflag, cr0, i;

  // 386か、486以降なのか確認
  eflag = io_load_eflags();
  eflag |= EFLAGS_AC_BIT;   // AC-bit = 1
  io_store_eflags(eflag);
  eflag = io_load_eflags();
  if ((eflag & EFLAGS_AC_BIT) != 0)   // 386ではAC=1にしても自動で0に戻ってしまう
  {
    flag486 = 1;
  }
  eflag &= ~EFLAGS_AC_BIT;  // AC-bit = 0
  io_store_eflags(eflag);
  
  if (flag486 != 0)
  {
    cr0 = load_cr0();
    cr0 |= CR0_CACHE_DISABLE;  // キャッシュ禁止
    store_cr0(cr0);
  }

  i = memtest_sub(start, end);

  if (flag486 != 0)
  {
    cr0 = load_cr0();
    cr0 &= ~CR0_CACHE_DISABLE;
    store_cr0(cr0);
  }
  
  return i;
}

unsigned int memtest_sub(unsigned int start, unsigned int end)
{
  unsigned int i, *p, old, pat0 = 0xaa55aa55, pat1 = 0x55aa55aa;
  for (int i = 0; i <= end; i+=0x1000)
  {
    p = (unsigned int *) (i + 0xffc);
    old = *p;             // いじる前の値を覚えておく
    *p = pat0;            // ためしに書いてみる
    *p ^= 0xffffffff;     // そしてそれを反転してみる
    if (*p != pat1)       // 反転結果になったか？
    {
not_memory:
            *p = old;
            break;
    }
    *p ^= 0xffffffff;     // もう一度反転してみる
    if (*p != pat0)
    {
      goto not_memory;
    }
    *p = old;             // いじった値をもとに戻す
    
  }
  return i;
}

