#include "Utilities.h"
void Utilities::draw_centerd_text(const char* text, int screen_width, int y, int font_size, Color color) {
	int text_width = MeasureText(text, font_size);
	int x = (screen_width - text_width) / 2;

	DrawText(text, x, y, font_size, color);
}