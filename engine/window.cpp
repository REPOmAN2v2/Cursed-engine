#include <algorithm>
#include <map>
#include <stddef.h>
#include "engine/window.hpp"
#include "engine/Config/Globals.hpp"

static int to_nc_colour(const Colours::Colour &colour)
{
	// Our base colours
	static std::map<Colours::Colour, int> colours = {
		{Colours::Colour::DEFAULT, -1},
		{Colours::Colour::RED, COLOR_RED},
		{Colours::Colour::BLUE, COLOR_BLUE},
		{Colours::Colour::GREEN, COLOR_GREEN},
		{Colours::Colour::YELLOW, COLOR_YELLOW},
		{Colours::Colour::MAGENTA, COLOR_MAGENTA},
		{Colours::Colour::CYAN, COLOR_CYAN},
		{Colours::Colour::BLACK, COLOR_BLACK},
		{Colours::Colour::WHITE, COLOR_WHITE}
	};

	// default colours go from COLOR_BLACK (0) to COLOR_WHITE (7)
	static size_t id = 8;

	// try to find the colour in our hashmap
	// if not found, initialise it if possible and add it to the map
	auto it = colours.find(colour);
	if (it != colours.end()) {
		return it->second;
	} else if (can_change_color()) {
		init_color(id, colour.r * 1000 / 255, 
				         colour.g * 1000 / 255,
				         colour.b * 1000 / 255);
		colours[colour] = id;
		return id++;
	}

	return -1;
}

static int to_nc_colour_pair(const Colours::ColourPair &pair)
{
	static std::map<Colours::ColourPair, int> pairs;
	static int id = 1;

	auto it = pairs.find(pair);
	if (it != pairs.end()) {
		return it->second;
	}

	init_pair(id, to_nc_colour(pair.first), to_nc_colour(pair.second));
	pairs[pair] = id;
	return id++;
}

Window::Window(int h, int w, int y, int x):title(""),borders(true),_h(h),_w(w),_y(y),_x(x)
{
	win = newwin(h, w, y, x);
}

Window::Window(Window *parent, int h, int w, int y, int x):
title(""),borders(true),_h(h),_w(w),_y(y),_x(x)
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
		print(title, 0, 1, Globals::text["title"]);
	}

	wrefresh(win);
}

void Window::clear()
{
	werase(win);
}

void Window::print(std::vector<std::string> lines, int y, int x, const Attributes &att)
{
	setAttr(att);

	std::for_each(lines.begin(), lines.end(), 
		[&](std::string &line){
			if (!line.empty()) {
				mvwaddstr(win, y++, x, line.c_str());
			}
		}
	);

	wattrset(win, A_NORMAL);
}

void Window::print(std::string line, int y, int x, const Attributes &att)
{
	setAttr(att);

	if (!line.empty()) {
		mvwaddstr(win, y, x, line.c_str());
	}

	wattrset(win, A_NORMAL);
}

static void wattrtoggle(WINDOW *win, int att, bool on)
{
	if (on)
		wattron(win, att);
	else
		wattroff(win, att);
}

void Window::setAttr(const Attributes &att)
{
	int pair = to_nc_colour_pair({att.fg, att.bg});
	wattrset(win, COLOR_PAIR(pair));
	wattrtoggle(win, A_BOLD, att.flags & Attributes::BOLD);
	wattrtoggle(win, A_UNDERLINE, att.flags & Attributes::UNDERLINE);
	wattrtoggle(win, A_DIM, att.flags & Attributes::DIM);
	wattrtoggle(win, A_REVERSE, att.flags & Attributes::REVERSE);
	wattrtoggle(win, A_BLINK, att.flags & Attributes::BLINK);
}

/*void Window::setColor(short fore, short back)
{
	if (fore < 0 || fore > 7 || back < -1 || back > 7) {
		wattrset(win, COLOR_PAIR(0));
	} else if (back == -1) {
		wattrset(win, COLOR_PAIR(65 + fore));
	} else { 
		wattrset(win, COLOR_PAIR(fore*8 + 1 + back));
	}
}*/

void Window::toggleBorders()
{
	borders = !borders;
}

void Window::setTitle(std::string title)
{
	this->title = title;
}