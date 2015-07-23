#include <algorithm>
#include "engine/window.hpp"

Window::Window(int h, int w, int y, int x):title(""),borders(true),_h(h),_w(w),_y(y),_x(x)
{
	win = newwin(h, w, y, x);
}

Window::Window(Window *parent, int h, int w, int y, int x):title(""),borders(true),_h(h),_w(w),_y(y),_x(x)
{
	if (w == -1) {
		_w = parent->_w - 2; 
	}

	if (h == -1) {
		_h = parent->_h - 2;
	}

	win = derwin(parent->win, _h, _w, y, x);
}

Window::~Window()
{
	if (win) {
		delwin(win);
	}
}

void Window::resize(int h, int w)
{
	wresize(win, h, w);
	_h = h;
	_w = w;
}

void Window::refresh()
{
	if (borders) {
		box(win, 0, 0);
	}

	if (!title.empty()) {
		print(title, 0, 1, COLOR_RED, -1);
	}

	wrefresh(win);
}

void Window::clear()
{
	werase(win);
}

void Window::print(std::vector<std::string> lines, int y, int x, short fore, short back)
{
	setColor(fore, back);

	std::for_each(lines.begin(), lines.end(), 
		[&](std::string &line){
			if (!line.empty()) {
				mvwaddstr(win, y++, x, line.c_str());
			}
		}
	);

	wattrset(win, A_NORMAL);
}

void Window::print(std::string line, int y, int x, short fore, short back)
{
	setColor(fore, back);

	if (!line.empty()) {
		mvwaddstr(win, y, x, line.c_str());
	}

	wattrset(win, A_NORMAL);
}

void Window::setColor(short fore, short back)
{
	if (fore < 0 || fore > 7 || back < -1 || back > 7) {
		wattrset(win, COLOR_PAIR(0));
	} else if (back == -1) {
		wattrset(win, COLOR_PAIR(65 + fore));
	} else { 
		wattrset(win, COLOR_PAIR(fore*8 + 1 + back));
	}
}

void Window::toggleBorders()
{
	borders = !borders;
}

void Window::setTitle(std::string title)
{
	this->title = title;
}