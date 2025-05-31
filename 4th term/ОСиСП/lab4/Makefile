CC = gcc
CFLAGS = -O2 -std=c11 -pedantic -Wall -Wextra -Werror -D_DEFAULT_SOURCE

_SRC = main.c consumer.c initexit.c ipc.c producer.c
SRC = $(patsubst %,%,$(_SRC))

ipc: $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: run
run:
	make ipc
	./ipc
	make clean

.PHONY: clean
clean:
	rm ipc