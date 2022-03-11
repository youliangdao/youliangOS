CC = gcc

TARGET = haribote.img

all : $(TARGET)

$(TARGET) : ipl.bin haribote.sys hlt.hrb
		mformat -f 1440 -C -B ipl.bin -i $(TARGET) ::
		mcopy haribote.sys -i $(TARGET) ::
		mcopy src/asm/boot/ipl10.s -i $(TARGET) ::
		mcopy Makefile -i $(TARGET) ::
		mcopy hlt.hrb -i $(TARGET) ::

ipl.bin : src/asm/boot/ipl10.s
		$(CC) -nostdlib src/asm/boot/ipl10.s -o ipl.bin -T scripts/binary.ld

haribote.sys : asmhead.bin ./bootpack.hrb
		cat asmhead.bin ./bootpack.hrb > haribote.sys

asmhead.bin : src/asm/boot/asmhead.s
		$(CC) -nostdlib src/asm/boot/asmhead.s -o asmhead.bin -T scripts/head.ld

bootpack.hrb : src/bootpack.c src/asm/gasfunc.s font/hankaku.c src/dsctbl.c src/graphic.c src/int.c src/fifo.c src/keyboard.c src/mouse.c src/memory.c src/sheet.c src/timer.c src/mtask.c src/window.c src/file.c src/console.c lib/mysprintf.c lib/strcmp.c lib/strncmp.c
		$(CC) -march=i486 -m32 -nostdlib -fno-pic -o $@ $^ -T scripts/hrb.ld

hlt.hrb : src/hlt_app/hlt.s
		$(CC) -nostdlib src/hlt_app/hlt.s -o hlt.hrb -T scripts/binary.ld

run : $(TARGET)
		qemu-system-i386 -fda $(TARGET) -boot a

.PHONY : clean
clean :
		rm -f $(TARGET) *.bin *.sys *.hrb *~