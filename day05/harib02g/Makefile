CC = gcc

TARGET = haribote.img

all : $(TARGET)

$(TARGET) : ipl.bin haribote.sys
		mformat -f 1440 -C -B ipl.bin -i $(TARGET) ::
		mcopy haribote.sys -i $(TARGET) ::

ipl.bin : ipl10.s
		$(CC) -nostdlib ipl10.s -o ipl.bin -T binary.ld

haribote.sys : asmhead.bin ./bootpack.hrb
		cat asmhead.bin ./bootpack.hrb > haribote.sys

asmhead.bin : asmhead.s
		$(CC) -nostdlib asmhead.s -o asmhead.bin -T head.ld

bootpack.hrb : bootpack.c
		$(CC) -march=i486 -m32 -nostdlib -fno-pic bootpack.c gasfunc.s hankaku.c mysprintf.c -o bootpack.hrb -T hrb.ld

run : $(TARGET)
		qemu-system-i386 -fda $(TARGET) -boot a

.PHONY : clean
clean :
		rm -f $(TARGET) *.bin *.sys *.hrb *~