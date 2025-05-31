CC=gcc
CFLAGS=-Wall -Wextra -lm

all: generate sort

generate: main.c
	$(CC) $(CFLAGS) main.c -o generate

sort: sort_index.c
	$(CC) $(CFLAGS) sort_index.c -o sort

clean:
	rm -f generate sort