CC = gcc
CCFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Iinclude

SRCS = src/main.c src/snake.c src/menu.c src/input.c

all: snake

snake: $(SRCS)
	$(CC) $(CCFLAGS) -o $@ $^

.PHONY: clean install

install:
	sudo install snake /usr/bin/

clean:
	rm -rf snake

