#ifndef SNAKE_H
#define SNAKE_H

#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <time.h>

#define CELL_SIZE 40

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define WALL_WIDTH 1040
#define WALL_HEIGHT 1040

typedef enum __direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
} Direction;

typedef struct SnakeCell {
	Vector2 position;
	Vector2 size;
	Direction direction;

	struct SnakeCell* next;
} SnakeCell;

typedef struct Snake {
	SnakeCell* head;
	int length;
} Snake;

typedef struct Fruit {
	Vector2 position;
} Fruit;

Snake* Snake_init(Vector2 position);

void Snake_draw(Snake* snake);
void Snake_process(Snake* snake, float delta);

void Snake_clear(Snake* snake);

#endif /* SNAKE_H */

