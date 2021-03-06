#include <string>

#include "engine/Config/Globals.hpp"
#include "engine/Keys.hpp"
#include "engine/Menu/Items/MenuItemToggle.hpp"
#include "engine/window.hpp"

MenuItemToggle::MenuItemToggle(const char *label, unsigned id, MenuItem::Type type, bool init):
	MenuItem(label, id, type),
	current(init),
	init(init)
{}

using namespace Globals;

void MenuItemToggle::draw(Window *window, bool cur, int w, int y, int x)
{
	window->print(label.substr(0, w - 4), y, x, cur ? Globals::text["highlight"] : Globals::text["normal"]);
	window->print("[", y, x - 4, cur ? Globals::text["highlight"] : Globals::text["normal"]);
	window->print(current ? "ON" : "OFF", y, w - 3, cur ? Globals::text["highlight"] : Globals::text["normal"]);
	window->print("]", y, x - 1, cur ? Globals::text["highlight"] : Globals::text["normal"]);
}

void MenuItemToggle::update(Key key)
{
	if (key.val == Key::LEFT || key.val == Key::RIGHT || key.val == Key::ENTER) {
		current = !current;
	}
}

bool MenuItemToggle::getValue()
{
	return current;
}

void MenuItemToggle::reset()
{
	current = init;
}
