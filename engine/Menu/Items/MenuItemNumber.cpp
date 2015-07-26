#include <string>

#include "engine/Config/Globals.hpp"
#include "engine/Menu/Items/MenuItemNumber.hpp"
#include "engine/window.hpp"

MenuItemNumber::MenuItemNumber(
	const char *label, unsigned id, MenuItem::Type type,
	int min, int max, int start):
	MenuItem(label, id, type),
	current(start),
	min(min),
	max(max),
	start(start)
{}

using namespace Globals;

void MenuItemNumber::draw(Window *window, bool cur, int w, int y, int x)
{
	std::string num = std::to_string(current);

	window->print(label.substr(0, w - num.size()), y, x, cur ? Globals::text["highlight"] : Globals::text["normal"]);
	window->print(num, y, w - num.size(), cur ? Globals::text["highlight"] : Globals::text["normal"]);
}

void MenuItemNumber::update(int key)
{
	// these bools tell us if we set the 1st, 2nd, 3rd and 4th digits
	static bool a = false;
	static bool b = false;
	static bool c = false;
	static bool d = false;

	if (key == KEY_LEFT) {
		if ((current - 1) >= min) --current; 
	} else if (key == KEY_RIGHT) {
		if ((current + 1) <= max) ++current;
	} else if (key >= '0' && key <= '9') {
		if (!a) {
			a = true;
			current = key - '0';
		} else if (!b) {
			b = true;
			current = current * 10 + key -'0';
		} else if (!c) {
			c = true;
			current = current * 10 + key - '0';
		} else if (!d) {
			d = true;
			current = current * 10 + key - '0';
			a = b = c = d = false;
		}

		// sanity checks
		if (current > max) {
			current = max;
			a = b = c = d = false;
		} else if (current < min) {
			current = min;
			a = b = c = d = false;
		}
	} else if (key == '\n') {
		a = b = c = d = false;
	}
}

int MenuItemNumber::getValue()
{
	return current;
}

void MenuItemNumber::reset()
{
	current = start;
}
