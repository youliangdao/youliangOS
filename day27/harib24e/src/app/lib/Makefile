CC = gcc

TARGET = apilib.a

all : $(TARGET)

$(TARGET) : api001.o api002.o api003.o api004.o api005.o api006.o api007.o \
			api008.o api009.o api010.o api011.o api012.o api013.o api014.o \
			api015.o api016.o api017.o api018.o api019.o
		ar r $@ $^

api001.o : api001.s 
		$(CC) -march=i486 -m32 -fno-pic -nostdlib api001.s -o api001.o

api002.o : api002.s 
		$(CC) -march=i486 -m32 -fno-pic -nostdlib api002.s -o api002.o

api003.o : api003.s 
		$(CC) -march=i486 -m32 -fno-pic -nostdlib api003.s -o api003.o

api004.o : api004.s 
		$(CC) -march=i486 -m32 -fno-pic -nostdlib api004.s -o api004.o

api005.o : api005.s 
		$(CC) -march=i486 -m32 -fno-pic -nostdlib api005.s -o api005.o

api006.o : api006.s 
		$(CC) -march=i486 -m32 -fno-pic -nostdlib api006.s -o api006.o

api007.o : api007.s 
		$(CC) -march=i486 -m32 -fno-pic -nostdlib api007.s -o api007.o

api008.o : api008.s 
		$(CC) -march=i486 -m32 -fno-pic -nostdlib api008.s -o api008.o

api009.o : api009.s 
		$(CC) -march=i486 -m32 -fno-pic -nostdlib api009.s -o api009.o

api010.o : api010.s 
		$(CC) -march=i486 -m32 -fno-pic -nostdlib api010.s -o api010.o

api011.o : api011.s 
		$(CC) -march=i486 -m32 -fno-pic -nostdlib api011.s -o api011.o

api012.o : api012.s 
		$(CC) -march=i486 -m32 -fno-pic -nostdlib api012.s -o api012.o

api013.o : api013.s 
		$(CC) -march=i486 -m32 -fno-pic -nostdlib api013.s -o api013.o

api014.o : api014.s 
		$(CC) -march=i486 -m32 -fno-pic -nostdlib api014.s -o api014.o

api015.o : api015.s 
		$(CC) -march=i486 -m32 -fno-pic -nostdlib api015.s -o api015.o

api016.o : api016.s 
		$(CC) -march=i486 -m32 -fno-pic -nostdlib api016.s -o api016.o

api017.o : api017.s 
		$(CC) -march=i486 -m32 -fno-pic -nostdlib api017.s -o api017.o

api018.o : api018.s 
		$(CC) -march=i486 -m32 -fno-pic -nostdlib api018.s -o api018.o

api019.o : api019.s 
		$(CC) -march=i486 -m32 -fno-pic -nostdlib api019.s -o api019.o

.PHONY : clean
clean :
		rm -f $(TARGET) *.o