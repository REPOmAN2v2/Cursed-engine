#pragma once

#include "window.hpp"
#include "MenuItemTemplates.hpp"

class MenuItem
{
public:
	MenuItem(const char *label, ID id, Type type);
	virtual ~MenuItem() {};
	virtual void draw(Window *window, bool cur, int w, int y, int x);
	virtual void update(int key) {};
	ID id;
	Type type;
	std::string label;
};