#include "MenuItem.hpp"

MenuItem::MenuItem(const char *label, ID id, Type type):
	id(id),
	type(type),
	label(label)
{}

void MenuItem::draw(Window *window, bool cur, int w, int y, int x)
{
	window->print(label.substr(0, w), y, x, cur ? COLOR_GREEN : -1, -1);
}