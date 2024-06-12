#include "input.h"

Button new_Button(Vector2 position, Vector2 size, char* text, float font_size) {
	return (Button){
		.position = position,
		.size = size,
		.text = text,
		.font_size = font_size,
		.clicked = false
	};
}

void button_draw(Button button) {
	Color color = BLACK;
	Color text_color = WHITE;
	int hover = false;
	Font font = GetFontDefault();

	Rectangle button_rect = {
		button.position.x,
		button.position.y,
		button.size.x,
		button.size.y
	};

	if (CheckCollisionPointRec(mouse_position, button_rect)) {
		hover = true;
	}

	if (hover) {
		color = WHITE;
		text_color = BLACK;
	}

	if (hover && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		color = BLACK;
		text_color = WHITE;
		button.clicked = true;
	}

	DrawRectangleV(button.position, button.size, color);
	DrawRectangleLines(
		button.position.x, 
		button.position.y, 
		button.size.x, 
		button.size.y, 
		WHITE
	);

	DrawRectangleLines(
		button.position.x + 1, 
		button.position.y + 1, 
		button.size.x - 2, 
		button.size.y - 2, 
		WHITE
	);

	if (button.text) {
		Vector2 text_size = MeasureTextEx(font, button.text, button.font_size, 1);

		float text_x = button_rect.x + (button_rect.width - text_size.x) / 2;
		float text_y = button_rect.y + (button_rect.height - text_size.y) / 2;
		DrawTextEx(font, button.text, (Vector2){ text_x, text_y }, button.font_size, 1, text_color);
	}
}

int button_clicked(Button button) {
	Rectangle button_rect = {
		button.position.x,
		button.position.y,
		button.size.x,
		button.size.y
	};

	if(CheckCollisionPointRec(mouse_position, button_rect) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		return true;
	}
	return false;
}
