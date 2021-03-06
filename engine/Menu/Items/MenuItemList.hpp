#pragma once

#include <stddef.h> // for size_t
#include <string>
#include <vector>

#include "engine/Menu/Items/MenuItem.hpp"

class Window;

class MenuItemList: public MenuItem
{
public:
	MenuItemList(
		const char *label, unsigned id, MenuItem::Type type,
		std::vector<std::string> list,
		std::string def);

	void draw(Window *window, bool cur, int w, int y, int x) override;
	void update(Key key) override;
	std::string getValue();
	void reset() override;
private:
	std::vector<std::string> list;
	std::string def;
	size_t index;
};
