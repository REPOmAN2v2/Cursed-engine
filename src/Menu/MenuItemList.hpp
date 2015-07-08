#pragma once

#include "MenuItem.hpp"

class MenuItemList: public MenuItem
{
public:
	MenuItemList(
		const char *label, ID id, Type type,
		std::vector<std::string> list,
		std::string def);

	void draw(Window *window, bool cur, int w, int y, int x);
	void update(int key);
	std::string getValue();
private:
	std::vector<std::string> list;
	std::string def;
	size_t index;
};
