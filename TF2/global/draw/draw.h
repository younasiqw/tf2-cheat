#ifndef DRAW_H
#define DRAW_H
#ifdef _WIN32
#pragma once
#endif

#define RED(COLORCODE) ((int)(COLORCODE >> 24))
#define BLUE(COLORCODE) ((int)(COLORCODE >> 8) & 0xFF)
#define GREEN(COLORCODE) ((int)(COLORCODE >> 16) & 0xFF)
#define ALPHA(COLORCODE) ((int)COLORCODE & 0xFF)
#define COLORCODE(r, g, b, a) ((DWORD)((((r)&0xff) << 24) | (((g)&0xff) << 16) | (((b)&0xff) << 8) | ((a)&0xff)))


namespace d
{
	extern void draw_outlined_rect(int x, int y, int w, int h, color col);
	extern void draw_line(int x, int y, int x1, int y1, color col);
	extern void draw_filled_rect(int x, int y, int w, int h, color col);
	extern void draw_filled_rect_secondary(int x, int y, int w, int h, color col);
	extern void draw_filled_rect_secondary(int x, int y, int w, int h, DWORD dwColor);
	extern void draw_menu_string(int x, int y, const char* _Input, int font, color color);
	extern void draw_gradient_v(int x, int y, int w, int h, color c1, color c2);

	extern void draw_string(int x, int y, color color, unsigned long font, const char* text, ...);

	extern void draw_text(int x, int y, color color, DWORD font, const char* text, ...);
	extern void draw_text(int x, int y, color color, DWORD font, const wchar_t* text);
	extern void draw_text(int x, int y, DWORD font, const wchar_t* text);

	RECT get_view_port();

	RECT get_text_size(DWORD font, const char* text);
	RECT get_text_size_secondary(const char* _Input, int font);

	byte get_esp_height();
}

#endif // !DRAW_H