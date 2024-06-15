#include <raylib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "snake.h"
#include "input.h"
#include "menu.h"

#define CELL_SIZE 40

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define WALL_WIDTH 1040
#define WALL_HEIGHT 1040

int game_over = false;
int score = 0;

Vector2 mouse_position;

int main() {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib");

	SetTargetFPS(60);

	int frames_counter = 0;

	char score_str[256];

	InitAudioDevice();

	Snake* snake = Snake_init((Vector2){(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2});

	srand(time(NULL));
	int pause = true;

	Button* b = new_Button((Vector2){(float)(SCREEN_WIDTH - 300) / 2, 750}, (Vector2){300, 100}, "Multiplayer", 40);
	
	while (!WindowShouldClose()) {
		show_debug_information(snake);

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

	CloseAudioDevice();

	CloseWindow();

	return 0;
}

