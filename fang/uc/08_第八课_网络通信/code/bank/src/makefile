CC = gcc
RM = rm
CFLAGS = -c -Wall

all: client server open close save withdraw query transfer

client: client.o network.o
	$(CC) $^ -o ../bin/$@

client.o: client.c
	$(CC) $(CFLAGS) $^

server: server.o
	$(CC) $^ -o ../bin/$@

server.o: server.c
	$(CC) $(CFLAGS) $^

open: open.o dao.o network.o
	$(CC) $^ -o ../bin/$@

open.o: open.c
	$(CC) $(CFLAGS) $^

close: close.o dao.o network.o
	$(CC) $^ -o ../bin/$@

close.o: close.c
	$(CC) $(CFLAGS) $^

save: save.o dao.o network.o
	$(CC) $^ -o ../bin/$@

save.o: save.c
	$(CC) $(CFLAGS) $^

withdraw: withdraw.o dao.o network.o
	$(CC) $^ -o ../bin/$@

withdraw.o: withdraw.c
	$(CC) $(CFLAGS) $^

query: query.o dao.o network.o
	$(CC) $^ -o ../bin/$@

query.o: query.c
	$(CC) $(CFLAGS) $^

transfer: transfer.o dao.o network.o
	$(CC) $^ -o ../bin/$@

transfer.o: transfer.c
	$(CC) $(CFLAGS) $^

dao.o: dao.c
	$(CC) $(CFLAGS) $^

network.o: network.c
	$(CC) $(CFLAGS) $^

clean:
	$(RM) *.o \
	../bin/client \
	../bin/server \
	../bin/open \
	../bin/close \
	../bin/save \
	../bin/withdraw \
	../bin/query \
	../bin/transfer
