#pragma once

#include <ncurses.h>
#include <string>
#include <vector>

#include "engine/Attributes.hpp"

class Window
{
public:
	Window(int h, int w, int y, int x);
	// Subwindows need a ref to the parent
	Window(Window *parent, int h, int w, int y, int x);
	~Window();
	void resize(int h, int w);
	void refresh();
	void clear();
	void setTitle(std::string title);
	void toggleBorders();
	//void setColor(short fore, short back);
	void setAttr(const Attributes &att);
	void print(std::string line, int y, int x, const Attributes &att);
	void print(std::vector<std::string> lines, int y, int x, const Attributes &att);
	int getH() const {return _h;};
	int getW() const {return _w;};
	int getY() const {return _y;};
	int getX() const {return _x;};
private:
	// TODO: add background colour
	WINDOW *win;
	std::string title;
	bool borders;
	int _h, _w, _y, _x;
};
