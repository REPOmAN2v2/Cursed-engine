#pragma once

#include "MenuItem.hpp"

class MenuItemNumber: public MenuItem
{
public:
	MenuItemNumber(
		const char *label, ID id, Type type,
		int min, int max, int start);

	void draw(Window *window, bool cur, int w, int y, int x) override;
	void update(int key) override;
	void reset() override;
	int getValue();
private:
	int current, min, max, start;
};