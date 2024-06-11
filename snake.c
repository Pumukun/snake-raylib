#include "snake.h"

Vector2 snake_position[100];
int fruit_alive = false;
Fruit* f;

int mod = 8;

extern int game_over;
extern int score;

Fruit* fruit_spawn() {
	int r1 = (rand() % 80) * 10;
	int r2 = (rand() % 80) * 10;
	while (r1 % 40 != 0) { r1 = (rand() % 80) * 10; }
	while (r2 % 40 != 0) { r2 = (rand() % 80) * 10; }

	Fruit* f = (Fruit*)malloc(sizeof(Fruit));
	f->position = (Vector2){r1+20, r2+20};

	return f;
}

void fruit_draw(Fruit* f) {
	DrawRectangleV((Vector2)f->position, (Vector2){CELL_SIZE, CELL_SIZE}, RED);
}

void fruit_delete(Fruit* f) {
	free(f);
	fruit_alive = false;
}

SnakeCell* get_cell(Snake* snake, size_t index) {
	if (index > snake->length) {
		return NULL;
	}

	SnakeCell* tmp_cell = snake->head;
	for (size_t i = 0; i < index; ++i) {
		tmp_cell = tmp_cell->next;
	}

	return tmp_cell;
}

SnakeCell* new_SnakeCell(Vector2 position, SnakeCell* next, Direction direction) {
	SnakeCell* cell = (SnakeCell*)malloc(sizeof(SnakeCell));
	cell->position = position;
	cell->next = next;
	cell->size = (Vector2){CELL_SIZE, CELL_SIZE}; 
	cell->direction = direction;

	return cell;
}

Snake* Snake_init(Vector2 position) {
	Snake* snake = (Snake*)malloc(sizeof(Snake));
	SnakeCell* head = new_SnakeCell(position, NULL, UP);

	snake->head = head;
	snake->length = 1;

	return snake;
}

void Snake_add_cell(Snake* snake) {
	if (!snake->head) {
		printf("ERR: Snake is null!");
		exit(EXIT_FAILURE);
	}

	SnakeCell* tmp_cell = snake->head;
	while (tmp_cell->next != NULL) {
		tmp_cell = tmp_cell->next;
	}

	SnakeCell* new_cell = new_SnakeCell(tmp_cell->position, NULL, tmp_cell->direction);
	tmp_cell->next = new_cell;

	++(snake->length);
}

void Snake_draw(Snake* snake) {
	SnakeCell* tmp_cell = snake->head;

	fruit_draw(f);

	while (tmp_cell != NULL) {
		DrawRectangleV((Vector2)tmp_cell->position, (Vector2){CELL_SIZE, CELL_SIZE}, GREEN);
		tmp_cell = tmp_cell->next;
	}
}

int Snake_check_collision(Snake* snake) {
	if (snake->length < 4) {
		return false;
	}

	SnakeCell* tmp_cell = get_cell(snake, 2);

	while (tmp_cell->next != NULL) {
		if (snake->head->position.x == tmp_cell->position.x && snake->head->position.y == tmp_cell->position.y) {
			return true;
		}
		tmp_cell = tmp_cell->next;
	}

	return false;
}

void Snake_process(Snake* snake, float delta) {
	SnakeCell* head = snake->head;

	if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && head->direction != DOWN) {
		head->direction = UP;
	}
	if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && head->direction != UP) {
		head->direction = DOWN;
	}
	if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && head->direction != RIGHT) {
		head->direction = LEFT;
	}
	if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && head->direction != LEFT) {
		head->direction = RIGHT;
	}

	static int frames_counter = 0;

	switch (score) {
		case 18:
			mod = 7;
			break;
		case 28:
			mod = 6;
			break;
		case 47:
			mod = 5;
			break;
		case 59:
			mod = 4;
			break;
		case 79:
			mod = 3;
			break;
	}
	
	if ((frames_counter%mod) == 0) {
		switch (snake->head->direction) {
			case UP:
				head->position.y -= CELL_SIZE; 
				break;

			case DOWN:
				head->position.y += CELL_SIZE;
				break;

			case LEFT:
				head->position.x -= CELL_SIZE;
				break;

			case RIGHT:
				head->position.x += CELL_SIZE;
				break;
		}

		for (int i = 0; i < snake->length; ++i) {
			snake_position[i] = (Vector2)get_cell(snake, i)->position;
		}

		for (size_t i = 1; i < snake->length; ++i) {
			get_cell(snake, i)->position = snake_position[i-1];
		}
	}

	if (head->position.x <= 0 || head->position.x >= 820 || head->position.y <= 0 || head->position.y >= 820) {
		game_over = true;
	}

	if (!fruit_alive) {
		f = fruit_spawn();
		fruit_alive = true;
	}

	if (head->position.x == f->position.x && head->position.y == f->position.y) {
		Snake_add_cell(snake);
		++score;
		fruit_delete(f);
	}

	if (Snake_check_collision(snake)) {
		game_over = true;
	}

	frames_counter++;
}

void Snake_clear(Snake* snake) {
	SnakeCell* tmp_cell = snake->head->next;
	while (tmp_cell != NULL) {
		SnakeCell* next_cell = tmp_cell->next;
		free(tmp_cell);
		tmp_cell = next_cell;
	}
	snake->head->next = NULL;
	snake->length = 1;
	snake->head->position = (Vector2){420, 420};
	snake->head->direction = UP;
}

