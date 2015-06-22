#include "MenuItemToggle.hpp"

MenuItemToggle::MenuItemToggle(const char *label, ID id, Type type, bool init):
	MenuItem(label, id, type),
	sel(init),
	init(init)
{}

void MenuItemToggle::draw(Window *window, bool cur, int w, int y, int x)
{
	window->print(label.substr(0, w - 4), y, x, cur ? COLOR_GREEN : -1, -1);
	window->print("[", y, x - 4, cur ? COLOR_GREEN : -1, -1);
	window->print(sel ? "ON" : "OFF", y, w - 3, cur ? COLOR_GREEN : -1, -1);
	window->print("]", y, x - 1, cur ? COLOR_GREEN : -1, -1);
}

void MenuItemToggle::update(int key)
{
	if (key == KEY_LEFT || key == KEY_RIGHT || key == '\n') {
		sel = !sel;
	}
}