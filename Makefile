OBJS=./src/main.o ./src/libc99/stdlib.o ./src/libc99/stdio.o ./src/handlers.o
CC=cc
PREFIX=/usr/local
LDLIBS_STATIC=-L/usr/local/lib -L/opt/freeware/lib -lcurl -ldiscord -lcrypto -lpthread -lnghttp2 -lssl -lz -lpsl -lidn2 -lunistring -liconv -static
LDLIBS_DYN=-L/usr/local/lib -L/opt/freeware/lib -lcurl -ldiscord -lpthread
CFLAGS=-I/usr/local/include -I/opt/freeware/include -g 

all: $(OBJS) $(TESTS) pancake-bot

clean:
	rm -rf $(OBJS)
	rm -rf $(TESTS)
	rm -rf vgcore.*
	rm -rf core*
	rm -rf *.core
	rm -rf pancake-bot pancake-bot-static

install:
	mkdir -p $(PREFIX)
	mkdir -p $(PREFIX)/bin
	install -m 755 pancake-bot $(PREFIX)/bin

uninstall:
	rm -f $(PREFIX)/bin/pancake-bot

./src/main.o: ./src/main.c ./src/bot.h
	$(CC) -c $(CFLAGS) ./src/main.c -o ./src/main.o

./src/handlers.o: ./src/handlers.c ./src/bot.h
	$(CC) -c $(CFLAGS) ./src/handlers.c -o ./src/handlers.o

./src/libc99/stdlib.o: ./src/libc99/stdlib.c ./src/libc99/libc99.h
	$(CC) -c $(CFLAGS) ./src/libc99/stdlib.c -o ./src/libc99/stdlib.o 

./src/libc99/stdio.o: ./src/libc99/stdio.c ./src/libc99/libc99.h
	$(CC) -c $(CFLAGS) ./src/libc99/stdio.c -o ./src/libc99/stdio.o 

pancake-bot: $(OBJS)
	$(CC) $(OBJS) -o pancake-bot $(LDFLAGS) $(LDLIBS_DYN)

pancake-bot-static: $(OBJS)
	$(CC) $(OBJS) -o pancake-bot-static $(LDFLAGS) $(LDLIBS_STATIC)
