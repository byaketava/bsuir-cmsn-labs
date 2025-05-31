CC = gcc
CFLAGS = -W -Wall -std=c11 -pedantic -Wno-unused-parameter -Wno-unused-variable
.PHONY : clean

all : generator main

main: main.c
	$(CC) $(CFLAGS) main.c -o main

generator: gener.c
	$(CC) $(CFLAGS) gener.c -o generator

clean:
	rm -f main generator file

generate:
	./generator

run:
	./main