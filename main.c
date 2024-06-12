#include <raylib.h>
#include <stdio.h>
#include <time.h>

#include "snake.h"
#include "input.h"

#define CELL_SIZE 40

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define WALL_WIDTH 1040
#define WALL_HEIGHT 1040

int game_over = false;
int score = 0;

Vector2 mouse_position;

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

int main() {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib");

	SetTargetFPS(60);

	int frames_counter = 0;

	char score_str[256];

	Snake* snake = Snake_init((Vector2){(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2});

	srand(time(NULL));

	int pause = true;

	Button* b = new_Button((Vector2){(float)(SCREEN_WIDTH - 300) / 2, 750}, (Vector2){300, 100}, "Multiplayer", 40);

	while (!WindowShouldClose()) {
		mouse_position = GetMousePosition();

		float delta = GetFrameTime();

		if (button_clicked(b)) {
			b->text = "Multiprayer";
		} else {
			b->text = "Multiplayer";
		}

		if (IsKeyDown(KEY_P) && frames_counter%4 == 0) { pause = !pause; }
		if (IsKeyDown(KEY_ENTER)) { pause = false; game_over = false; }

		BeginDrawing();

		if (pause && !game_over) {
			DrawMenu();
			button_draw(b);
		}

		if (game_over) { 
			Snake_clear(snake);
			pause = true; 
			score = 0;
			DrawGMMenu();
		}

		sprintf(score_str, "%d", score);

		if (!pause) {
			Snake_process(snake, delta);
		}

		ClearBackground(BLACK);

		if (!pause && !game_over) {
			DrawInterface();
			DrawTextCentered(
				score_str,
				40,
				WHITE,
				(Vector2){0, -((float)SCREEN_HEIGHT / 2 - 50)}
			);
		}

		if (!pause) {
			Snake_draw(snake);
		}

		EndDrawing();

		frames_counter++;
	}

	Snake_clear(snake);
	free(snake->head);
	free(snake);

	CloseWindow();

	return 0;
}

