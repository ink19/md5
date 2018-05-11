all: main

main: main.o md5.o

main.o: main.c md5.h

md5.o: md5.c md5.h

clean:
	rm -rf *.o main