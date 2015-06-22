#pragma once

#include "MenuItem.hpp"

class MenuItemList: public MenuItem
{
public:
	MenuItemList(MenuItemTemplate &tem);

	void draw(Window *window, bool cur, int w, int y, int x);
	void update(int key);
private:
	std::vector<std::string> list;
	std::string def;
	size_t current;
};
