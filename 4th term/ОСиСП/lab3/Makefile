CHILD_PATH := /home/byaketava/CLionProjects/lab3
CC=gcc
CFLAGS=-W -Wall -Wno-unused-parameter -Wno-unused-variable -std=c11 -pedantic

.PHONY: all clean

all: child parent clean

parent: parent.c
	$(CC) $(CFLAGS) -o parent parent.c
	./parent $(CHILD_PATH)

child: child.c
	$(CC) $(CFLAGS) -o child child.c

clean:
	rm -f parent child