makegen project unix --binary pancake-bot --main src/main.c \
                     --ldlibs '\-lcurl -ldiscord -lcrypto -lpthread' > Makefile
