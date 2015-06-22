#pragma once

#include "MenuItem.hpp"

class MenuItemToggle: public MenuItem
{
public:
	MenuItemToggle(const char *label, ID id, Type type, bool init);

	void draw(Window *window, bool cur, int w, int y, int x);
	void update(int key);
private:
	bool sel, init;
};