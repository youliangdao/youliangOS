CC = gcc

TARGET = haribote.img

all : $(TARGET)

$(TARGET) : ipl.bin haribote.sys hello.hrb hello2.hrb hello3.hrb hello4.hrb hello5.hrb \
			winhelo.hrb winhelo2.hrb winhelo3.hrb star1.hrb stars2.hrb lines.hrb walk.hrb \
			noodle.hrb beepdown.hrb color.hrb color2.hrb \
			crack7.hrb sosu.hrb sosu2.hrb sosu3.hrb
		mformat -f 1440 -C -B ipl.bin -i $(TARGET) ::
		mcopy haribote.sys -i $(TARGET) ::
		mcopy src/asm/boot/ipl10.s -i $(TARGET) ::
		mcopy Makefile -i $(TARGET) ::
		mcopy hello.hrb -i $(TARGET) ::
		mcopy hello2.hrb -i $(TARGET) ::
		mcopy hello3.hrb -i $(TARGET) ::
		mcopy hello4.hrb -i $(TARGET) ::
		mcopy hello5.hrb -i $(TARGET) ::
		mcopy winhelo.hrb -i $(TARGET) ::
		mcopy winhelo2.hrb -i $(TARGET) ::
		mcopy winhelo3.hrb -i $(TARGET) ::
		mcopy star1.hrb -i $(TARGET) ::
		mcopy stars2.hrb -i $(TARGET) ::
		mcopy lines.hrb -i $(TARGET) ::
		mcopy walk.hrb -i $(TARGET) ::
		mcopy noodle.hrb -i $(TARGET) ::
		mcopy beepdown.hrb -i $(TARGET) ::
		mcopy color.hrb -i $(TARGET) ::
		mcopy color2.hrb -i $(TARGET) ::
		mcopy crack7.hrb -i $(TARGET) ::
		mcopy sosu.hrb -i $(TARGET) ::
		mcopy sosu2.hrb -i $(TARGET) ::
		mcopy sosu3.hrb -i $(TARGET) ::
ipl.bin : src/asm/boot/ipl10.s
		$(CC) -nostdlib src/asm/boot/ipl10.s -o ipl.bin -T scripts/binary.ld

haribote.sys : asmhead.bin ./bootpack.hrb
		cat asmhead.bin ./bootpack.hrb > haribote.sys

asmhead.bin : src/asm/boot/asmhead.s
		$(CC) -nostdlib src/asm/boot/asmhead.s -o asmhead.bin -T scripts/head.ld

bootpack.hrb : src/bootpack.c src/asm/gasfunc.s font/hankaku.c src/dsctbl.c src/graphic.c src/int.c src/fifo.c src/keyboard.c src/mouse.c src/memory.c src/sheet.c src/timer.c src/mtask.c src/window.c src/file.c src/console.c lib/mysprintf.c lib/strcmp.c lib/strncmp.c
		$(CC) -march=i486 -m32 -nostdlib -fno-pic -o $@ $^ -T scripts/hrb_os.ld

hello.hrb : src/app/hello.s
		$(CC) -nostdlib src/app/hello.s -o hello.hrb -T scripts/binary.ld

hello2.hrb : src/app/hello2.s
		$(CC) -nostdlib src/app/hello2.s -o hello2.hrb -T scripts/app.ld

hello3.hrb : src/app/hello3.c src/app/a_nask.s
		$(CC) -march=i486 -m32 -fno-pic -nostdlib src/app/hello3.c src/app/a_nask.s -o hello3.hrb -T scripts/hrb_app.ld

hello4.hrb : src/app/hello4.c src/app/a_nask.s
		$(CC) -march=i486 -m32 -fno-pic -nostdlib src/app/hello4.c src/app/a_nask.s -o hello4.hrb -T scripts/hrb_app.ld

hello5.hrb : src/app/hello5.s
		$(CC) -march=i486 -m32 -fno-pic -nostdlib src/app/hello5.s -o hello5.hrb -T scripts/hrb_app.ld

winhelo.hrb : src/app/winhelo.c src/app/a_nask.s
		$(CC) -march=i486 -m32 -fno-pic -nostdlib src/app/winhelo.c src/app/a_nask.s -o winhelo.hrb -T scripts/hrb_app.ld

winhelo2.hrb : src/app/winhelo2.c src/app/a_nask.s
		$(CC) -march=i486 -m32 -fno-pic -nostdlib src/app/winhelo2.c src/app/a_nask.s -o winhelo2.hrb -T scripts/hrb_app.ld

winhelo3.hrb : src/app/winhelo3.c src/app/a_nask.s
		$(CC) -march=i486 -m32 -fno-pic -nostdlib src/app/winhelo3.c src/app/a_nask.s -o winhelo3.hrb -T scripts/hrb_app.ld

star1.hrb : src/app/star1.c src/app/a_nask.s
		$(CC) -march=i486 -m32 -fno-pic -nostdlib src/app/star1.c src/app/a_nask.s -o star1.hrb -T scripts/hrb_app.ld

stars2.hrb : src/app/stars2.c src/app/a_nask.s
		$(CC) -march=i486 -m32 -fno-pic -nostdlib src/app/stars2.c src/app/a_nask.s -o stars2.hrb -T scripts/hrb_app.ld

lines.hrb : src/app/lines.c src/app/a_nask.s
		$(CC) -march=i486 -m32 -fno-pic -nostdlib src/app/lines.c src/app/a_nask.s -o lines.hrb -T scripts/hrb_app.ld

walk.hrb : src/app/walk.c src/app/a_nask.s
		$(CC) -march=i486 -m32 -fno-pic -nostdlib src/app/walk.c src/app/a_nask.s -o walk.hrb -T scripts/hrb_app.ld

noodle.hrb : src/app/noodle.c src/app/a_nask.s lib/mysprintf.c
		$(CC) -march=i486 -m32 -fno-pic -nostdlib src/app/noodle.c src/app/a_nask.s lib/mysprintf.c -o noodle.hrb -T scripts/hrb_app.ld

beepdown.hrb : src/app/beepdown.c src/app/a_nask.s
		$(CC) -march=i486 -m32 -fno-pic -nostdlib src/app/beepdown.c src/app/a_nask.s -o beepdown.hrb -T scripts/hrb_app.ld

color.hrb : src/app/color.c src/app/a_nask.s
		$(CC) -march=i486 -m32 -fno-pic -nostdlib src/app/color.c src/app/a_nask.s -o color.hrb -T scripts/hrb_app.ld

color2.hrb : src/app/color2.c src/app/a_nask.s
		$(CC) -march=i486 -m32 -fno-pic -nostdlib src/app/color2.c src/app/a_nask.s -o color2.hrb -T scripts/hrb_app.ld

crack7.hrb : src/app/crack7.s
		$(CC) -march=i486 -m32 -fno-pic -nostdlib src/app/crack7.s -o crack7.hrb -T scripts/hrb_app.ld

sosu.hrb : src/app/sosu.c src/app/a_nask.s lib/mysprintf.c
		$(CC) -march=i486 -m32 -fno-pic -nostdlib $^ -o sosu.hrb -T scripts/hrb_app.ld

sosu2.hrb : src/app/sosu2.c src/app/a_nask.s lib/mysprintf.c
		$(CC) -march=i486 -m32 -fno-pic -nostdlib $^ -o $@ -T scripts/hrb_app.ld

sosu3.hrb : src/app/sosu3.c src/app/a_nask.s lib/mysprintf.c
		$(CC) -march=i486 -m32 -fno-pic -nostdlib $^ -o $@ -T scripts/hrb_app.ld

run : $(TARGET)
		qemu-system-i386 -fda $(TARGET) -boot a

.PHONY : clean
clean :
		rm -f $(TARGET) *.bin *.sys *.hrb *~