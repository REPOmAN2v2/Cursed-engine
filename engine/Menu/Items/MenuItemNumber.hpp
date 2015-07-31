#pragma once

#include "engine/Menu/Items/MenuItem.hpp"

class Window;

class MenuItemNumber: public MenuItem
{
public:
	MenuItemNumber(
		const char *label, unsigned id, MenuItem::Type type,
		int min, int max, int start);

	void draw(Window *window, bool cur, int w, int y, int x) override;
	void update(Key key) override;
	void reset() override;
	int getValue();
private:
	int current, min, max, start;
};
