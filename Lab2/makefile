all: search client

search: p2-server.c
	gcc -o server p2-server.c

client: p2-client.c
	gcc -o client p2-client.c

run: run-server 

run-server: server
	./server

	