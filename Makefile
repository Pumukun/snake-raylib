CC = gcc
CCFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all: snake

snake: main.c snake.c input.c server.c
	$(CC) $(CCFLAGS) -o $@ $^

.PHONY: clean install

install:
	sudo install snake /usr/bin/

clean:
	rm -rf snake

