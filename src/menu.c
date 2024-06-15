#include "menu.h"

void DrawTextCentered(const char* text, float font_size, Color color, Vector2 offset) {
	Vector2 text_size = MeasureTextEx(GetFontDefault(), text, font_size, 4);
	DrawTextEx(
		GetFontDefault(),
		text,
		(Vector2){
			(SCREEN_WIDTH - text_size.x) / 2 + offset.x, 
			(SCREEN_HEIGHT - text_size.y) / 2 + offset.y
		},
		font_size,
		4,
		color
	);

}

void DrawInterface() {
	DrawRectangleLines(
		(SCREEN_WIDTH - WALL_WIDTH) / 2, 
		(SCREEN_HEIGHT - WALL_HEIGHT) / 2, 
		WALL_WIDTH, 
		WALL_HEIGHT, 
		WHITE
	);

	DrawRectangleLines( 
		(SCREEN_WIDTH - WALL_WIDTH) / 2 - 1, 
		(SCREEN_HEIGHT - WALL_HEIGHT) / 2 - 1, 
		WALL_WIDTH + 2, 
		WALL_HEIGHT + 2, 
		WHITE
	);
}

void DrawMenu() {
	DrawTextCentered("Press \"Enter\" to start!", 50, WHITE, (Vector2){0, 0});
}

void DrawGMMenu() {
	DrawTextCentered("Game Over :(", 50, RED, (Vector2){0, 0});
	DrawTextCentered("Press \"Enter\" to start!", 50, WHITE, (Vector2){0, 60});
}

void show_debug_information(Snake* snake) {
	char fps[10];
	char snake_len[128];

	char direction_string[6];
	switch (snake->head->direction) {
		case UP:
			strcpy(direction_string, "UP");
			break;
		case DOWN:
			strcpy(direction_string, "DOWN");
			break;
		case LEFT:
			strcpy(direction_string, "LEFT");
			break;
		case RIGHT:
			strcpy(direction_string, "RIGHT");
			break;
	}

	sprintf(fps, "fps: %d\n", GetFPS());
	sprintf(snake_len, "Snake {\n\n\tlength: %d\n\n\tdirection: %s\n\n\thead->pos: {\n\n\t\tx: %.2f,\n\n\t\ty: %.2f\n\n\t}\n\n}", snake->length - 1, direction_string, snake->head->position.x, snake->head->position.y);

	DrawText(fps, 1500, 20, 30, WHITE);
	DrawText(snake_len, 1500, 50, 30, WHITE);
}
