#include "MenuItem.hpp"
#include "../../Config/Globals.hpp"

MenuItem::MenuItem(const char *label, unsigned id, MenuItem::Type type):
	type(type),
	id(id),
	label(label)
{}

using namespace Globals;

void MenuItem::draw(Window *window, bool cur, int w, int y, int x)
{
	window->print(label.substr(0, w), y, x, cur ? Colours::highlight : Colours::normal, Colours::normal);
}