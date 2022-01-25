#include "lib/mysprintf.h"
#include "bootpack.h"

#define PORT_KEYDAT	0x0060
#define PORT_KEYSTA	0x0064
#define PORT_KEYCMD	0x0064
#define KEYSTA_SEND_NOTREADY	0x02
#define KEYCMD_WRITE_MODE	0x60
#define KBC_MODE	0x47

void wait_KBC_sendready(void);
void init_keyboard(void);

#define KEYCMD_SENDTO_MOUSE	0xd4
#define MOUSE_ENABLE	0xf4

void enable_mouse(void);

extern struct FIFO8 keyfifo;
extern struct FIFO8 mousefifo;

void HariMain(void)
{
  struct BOOTINFO *binfo = (struct BOOTINFO *) ADR_BOOTINFO;
  char mcursor[16 * 16];
  char msg[256], s[4], keybuf[32], mousebuf[128];
  int mx;
  int my;
  int i;

  unsigned char mouse_dbuf[3], mouse_phase;

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

  enable_mouse();
  mouse_phase = 0;
  
  for (;;) {
    io_cli();
    if (fifo8_status(&keyfifo) + fifo8_status(&mousefifo) == 0) {
      io_stihlt();
    } else {
      if (fifo8_status(&keyfifo) != 0) {
	      i = fifo8_get(&keyfifo);
	      io_sti();
      
	      sprintk(s, "%02x", i);
	      boxfill8(binfo->vram, binfo->scrnx, COL8_008484, 0, 16, 15, 31);
	      putfont8_asc(binfo->vram, binfo->scrnx, 0, 16, COL8_FFFFFF, s);
      } else if (fifo8_status(&mousefifo) != 0) {
	      i = fifo8_get(&mousefifo);
      	io_sti();

	      if (mouse_phase == 0) {
	        /* マウスの初期化直後の0xfaを待っている段階 */
	        if (i == 0xfa) {
	         mouse_phase = 1;
	        }
	      } else if (mouse_phase == 1) {
	        /* マウスの1バイト目を待っている段階 */
	        mouse_dbuf[0] = i;
	        mouse_phase = 2;
	      } else if (mouse_phase == 2) {
	        /* マウスの2バイト目を待っている段階 */
	        mouse_dbuf[1] = i;
	        mouse_phase = 3;
	      } else if (mouse_phase == 3) {
	        /* マウスの2バイト目を待っている段階 */
	        mouse_dbuf[2] = i;
	        mouse_phase = 1;
	        /* データが3バイト揃ったので表示 */
	        sprintk(s, "%02x %02x %02x", mouse_dbuf[0], mouse_dbuf[1], mouse_dbuf[2]);
	        boxfill8(binfo->vram, binfo->scrnx, COL8_008484, 32, 16, 32 + 8 * 8 - 1, 31);
	        putfont8_asc(binfo->vram, binfo->scrnx, 32, 16, COL8_FFFFFF, s);
	      }
      }
    }
  }
}

void wait_KBC_sendready(void)
{
  /* キーボードコントローラがデータ送信可能になるまで待つ */
  for (;;) {
    if ((io_in8(PORT_KEYSTA) & KEYSTA_SEND_NOTREADY) == 0) {
      break;
    }
  }
  return;
}

void init_keyboard(void)
{
  /* キーボードコントローラの初期化 */
  wait_KBC_sendready();
  io_out8(PORT_KEYCMD, KEYCMD_WRITE_MODE);
  wait_KBC_sendready();
  io_out8(PORT_KEYDAT, KBC_MODE);
  return;
}

void enable_mouse(void)
{
  /* マウス有効 */
  wait_KBC_sendready();
  io_out8(PORT_KEYCMD, KEYCMD_SENDTO_MOUSE);
  wait_KBC_sendready();
  io_out8(PORT_KEYDAT, MOUSE_ENABLE);
  return;
}