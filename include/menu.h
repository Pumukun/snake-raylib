#ifndef MENU_H
#define MENU_H

#include <raylib.h>
#include <string.h>

#include "snake.h"

#define CELL_SIZE 40

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define WALL_WIDTH 1040
#define WALL_HEIGHT 1040

void DrawTextCentered(const char* text, float font_size, Color color, Vector2 offset);
void DrawInterface();
void DrawMenu();
void DrawGMMenu();
void show_debug_information(Snake* snake);

#endif /* MENU_H */
