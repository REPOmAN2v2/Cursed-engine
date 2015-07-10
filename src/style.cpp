#include "style.hpp"
#include "ncurses.hpp"

Style::Style(int h, int w):_h(h),_w(w)
{}

void Style::create()
{
	int y, x;

	if (_h == -1 || _h > LINES) {
		_h = LINES;
	}

	if (_w == -1 || _w > COLS) {
		_w = COLS;
	}

	y = (LINES - _h) / 2;
	x = (COLS - _w) / 2;

	destroy();
	main = new Window(_h, _w, y, x);
}

void Style::destroy()
{
	if (main) {
		delete main;
		main = nullptr;
	}
}

Style::~Style()
{
	destroy();
}