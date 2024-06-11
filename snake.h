#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <time.h>

#define CELL_SIZE 40

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

SnakeCell* new_SnakeCell(Vector2 position, SnakeCell* next, Direction direction);

Snake* Snake_init(Vector2 position);

void Snake_draw(Snake* snake);
void Snake_process(Snake* snake, float delta);

void Snake_add_cell(Snake* snake);

void Snake_clear(Snake* snake);

