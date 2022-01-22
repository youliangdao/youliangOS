CC = gcc

TARGET = haribote.img

all : $(TARGET)

$(TARGET) : ipl.bin haribote.sys
		mformat -f 1440 -C -B ipl.bin -i $(TARGET) ::
		mcopy haribote.sys -i $(TARGET) ::

ipl.bin : ipl10.s
		$(CC) -nostdlib ipl10.s -o ipl.bin -T binary.ld

haribote.sys : haribote.s
		$(CC) -nostdlib haribote.s -o haribote.sys -T binary.ld

run : $(TARGET)
		qemu-system-i386 -fda $(TARGET) -boot a

.PHONY : clean
clean :
		rm -f $(TARGET) ipl.bin haribote.sys *~