IMG_PATH := /home/byaketava/disk.img
CC=gcc
CFLAGS= -std=c11 -pedantic

.PHONY: run clean

all: start fscheck
##	./start $(IMG_PATH)
##	./fscheck $(IMG_PATH)

fscheck: fscheck.c
	$(CC) $(CFLAGS) -o fscheck fscheck.c

start: start.c
	$(CC) $(CFLAGS) -o start start.c

clean:
	rm start fscheck
