#include "../../main.h"

namespace d
{
	RECT get_view_port()
	{
		RECT Viewport = { 0, 0, 0, 0 };
		int w, h;
		i::engineclient->get_screen_size(w, h);
		Viewport.right = w; Viewport.bottom = h;
		return Viewport;
	}

	void draw_gradient_v(int x, int y, int w, int h, color c1, color c2)
	{
		draw_filled_rect(x, y, w, h, c1);
		BYTE first = c2.r();
		BYTE second = c2.g();
		BYTE third = c2.b();
		for (int i = 0; i < h; i++)
		{
			float fi = i, fh = h;
			float a = fi / fh;
			DWORD ia = a * 255;
			draw_filled_rect(x, y + i, w, 1, color(first, second, third, ia));
		}
	}

	void draw_outlined_rect(int x, int y, int w, int h, color col)
	{
		i::surface->draw_set_color(col);
		i::surface->draw_outlined_rect(x, y, x + w, y + h);
	}

	void draw_line(int x, int y, int x1, int y1, color col)
	{
		i::surface->draw_set_color(col);
		i::surface->draw_line(x, y, x1, y1);
	}

	void draw_filled_rect(int x, int y, int w, int h, color col)
	{
		i::surface->draw_set_color(col);
		i::surface->draw_filled_rect(x, y, x + w, y + h);
	}

	void draw_filled_rect_secondary(int x, int y, int w, int h, color Col)
	{
		i::surface->draw_set_color(Col);
		i::surface->draw_filled_rect(x, y, x + w, y + h);
	}

	void draw_filled_rect_secondary(int x, int y, int w, int h, DWORD dwColor)
	{
		i::surface->draw_set_color_secondary(RED(dwColor), GREEN(dwColor), BLUE(dwColor), ALPHA(dwColor));
		i::surface->draw_filled_rect(x, y, x + w, y + h);
	}

	void draw_string(int x, int y, color color, unsigned long font, const char* text, ...)
	{
		size_t origsize = strlen(text) + 1;
		const size_t newsize = 100;
		size_t convertedChars = 0;
		wchar_t wcstring[newsize];
		mbstowcs_s(&convertedChars, wcstring, origsize, text, _TRUNCATE);

		i::surface->draw_set_text_font(font);
		i::surface->draw_set_text_color(color);
		i::surface->draw_set_text_pos(x, y);
		i::surface->draw_print_text(wcstring, wcslen(wcstring));
	}

	void draw_text(int x, int y, color color, DWORD font, const wchar_t* text)
	{
		i::surface->draw_set_text_font(font);
		i::surface->draw_set_color(color);
		i::surface->draw_set_text_pos(x, y);
		i::surface->draw_print_text(text, wcslen(text));
	}

	void draw_text(int x, int y, DWORD font, const wchar_t* text)
	{
		i::surface->draw_set_text_font(font);
		i::surface->draw_set_text_pos(x, y);
		i::surface->draw_print_text(text, wcslen(text));
	}

	void draw_text(int x, int y, color color, DWORD font, const char* text, ...)
	{
		size_t origsize = strlen(text) + 1;
		const size_t newsize = 100;
		size_t convertedChars = 0;
		wchar_t wcstring[newsize];
		mbstowcs_s(&convertedChars, wcstring, origsize, text, _TRUNCATE);

		i::surface->draw_set_text_font(font);

		i::surface->draw_set_color(color);
		i::surface->draw_set_text_pos(x, y);
		i::surface->draw_print_text(wcstring, wcslen(wcstring));
	}

	void draw_menu_string(int x, int y, const char* _Input, int font, color color)
	{
		int apple = 0;
		char Buffer[2048] = { '\0' };
		va_list Args;
		va_start(Args, _Input);
		vsprintf_s(Buffer, _Input, Args);
		va_end(Args);
		size_t Size = strlen(Buffer) + 1;
		wchar_t* WideBuffer = new wchar_t[Size];
		mbstowcs_s(0, WideBuffer, Size, Buffer, Size - 1);

		i::surface->draw_set_color(color);
		i::surface->draw_set_text_font(font);
		i::surface->draw_set_text_pos(x, y);
		i::surface->draw_print_text(WideBuffer, wcslen(WideBuffer));
	}

	RECT get_text_size(DWORD font, const char* text)
	{
		size_t origsize = strlen(text) + 1;
		const size_t newsize = 100;
		size_t convertedChars = 0;
		wchar_t wcstring[newsize];
		mbstowcs_s(&convertedChars, wcstring, origsize, text, _TRUNCATE);

		RECT rect; int x, y;
		i::surface->get_text_size(font, wcstring, x, y);
		rect.left = x; rect.bottom = y;
		rect.right = x;
		return rect;
	}

	RECT get_text_size_secondary(const char* _Input, int font)
	{
		int apple = 0;
		char Buffer[2048] = { '\0' };
		va_list Args;
		va_start(Args, _Input);
		vsprintf_s(Buffer, _Input, Args);
		va_end(Args);
		size_t Size = strlen(Buffer) + 1;
		wchar_t* WideBuffer = new wchar_t[Size];
		mbstowcs_s(0, WideBuffer, Size, Buffer, Size - 1);
		int Width = 0, Height = 0;

		i::surface->get_text_size(font, WideBuffer, Width, Height);

		RECT outcome = { 0, 0, Width, Height };
		return outcome;
	}

	byte get_esp_height()
	{
		return 12;
	}

}