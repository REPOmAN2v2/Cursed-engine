#include "engine/Config/Globals.hpp"
#include "engine/Keys.hpp"
#include "engine/Menu/Items/MenuItem.hpp"
#include "engine/window.hpp"

MenuItem::MenuItem(const char *label, unsigned id, MenuItem::Type type):
	type(type),
	id(id),
	label(label)
{}

void MenuItem::update(Key)
{}

using namespace Globals;

void MenuItem::draw(Window *window, bool cur, int w, int y, int x)
{
	window->print(label.substr(0, w), y, x, cur ? Globals::text["highlight"] : Globals::text["normal"]);
}
