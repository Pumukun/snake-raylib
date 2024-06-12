#ifndef INPUT_H
#define INPUT_H

#include <raylib.h>

extern Vector2 mouse_position;

typedef struct Button {
	Vector2 position;
	Vector2 size;

	char* text;
	float font_size;

	int clicked;
} Button;

Button new_Button(Vector2 position, Vector2 size, char* text, float font_size);

void button_draw(Button button);

int button_clicked(Button button);

#endif /* INPUT_H */
