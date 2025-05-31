CC=g++
CFLAGS=-std=c++11

all: client server

client: Client/client.cpp
	$(CC) $(CFLAGS) -o Client/client Client/client.cpp

server: Server/server.cpp
	$(CC) $(CFLAGS) -o Server/server Server/server.cpp

clean:
	rm -f client server
