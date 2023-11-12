CFLAGS=-g3  -Wall -pedantic -std=c99 -Wextra -Werror -O3 -march=native

main: skiplist.o main.c

all: main

run: all
	./main

clean:
	rm main *.o
