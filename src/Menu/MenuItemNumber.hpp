#pragma once

#include "MenuItem.hpp"

class MenuItemNumber: public MenuItem
{
public:
	MenuItemNumber(
		const char *label, ID id, Type type,
		int min, int max, int start);

	void draw(Window *window, bool cur, int w, int y, int x);
	void update(int key);
	int getValue();
private:
	int current, min, max, start;
};