#include <raylib.h>
#include <stdio.h>
#include <time.h>

#include "snake.h"

#define CELL_SIZE 40

#define SCREEN_WIDTH 840
#define SCREEN_HEIGHT 840

int game_over = false;
int score = 0;

void DrawInterface() {
	DrawRectangleLines(20, 20, 800, 800, WHITE);
	DrawRectangleLines(19, 19, 800, 800, WHITE);
}

void DrawMenu() {
	DrawText("Press \"Enter\" to start!", 120, 440, 50, WHITE);
}

void DrawGMMenu() {
	DrawText("Game Over :(", 260, 390, 50, RED);
	DrawText("Press \"Enter\" to start!", 120, 440, 50, WHITE);
}

int main() {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib");

	SetTargetFPS(60);

	int frames_counter = 0;

	char score_str[256];

	Snake* snake = Snake_init((Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});

	srand(time(NULL));

	int pause = true;

	while (!WindowShouldClose()) {
		if (IsKeyDown(KEY_P) && frames_counter%4 == 0) { pause = !pause; }
		if (IsKeyDown(KEY_ENTER)) { pause = false; game_over = false; }

		if (pause && !game_over) {
			DrawMenu();
		}
		if (game_over) { 
			Snake_clear(snake);
			pause = true; 
			score = 0;
			DrawGMMenu();
		}

		float delta = GetFrameTime();

		sprintf(score_str, "%d", score);

		if (!pause) {
			Snake_process(snake, delta);
		}

		BeginDrawing();

		ClearBackground(BLACK);

		DrawInterface();
		DrawText(score_str, 440, 20, 40, WHITE);
		
		if (!pause) {
			Snake_draw(snake);
		}

		EndDrawing();

		frames_counter++;
	}

	CloseWindow();

	return 0;
}

