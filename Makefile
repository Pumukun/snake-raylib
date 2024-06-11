CC = gcc
CCFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all: snake

snake: main.c snake.c
	$(CC) $(CCFLAGS) -o $@ main.c snake.c

.PHONY: clean install

install:
	sudo install snake /usr/bin/

clean:
	rm -rf snake

