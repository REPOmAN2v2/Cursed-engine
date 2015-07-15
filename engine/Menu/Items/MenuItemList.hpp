#pragma once

#include "MenuItem.hpp"

class MenuItemList: public MenuItem
{
public:
	MenuItemList(
		const char *label, ID id, Type type,
		std::vector<std::string> list,
		std::string def);

	void draw(Window *window, bool cur, int w, int y, int x) override;
	void update(int key) override;
	std::string getValue();
	void reset() override;
private:
	std::vector<std::string> list;
	std::string def;
	size_t index;
};