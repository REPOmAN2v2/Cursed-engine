#include "MenuItemToggle.hpp"
#include "../../Config/Globals.hpp"

MenuItemToggle::MenuItemToggle(const char *label, ID id, Type type, bool init):
	MenuItem(label, id, type),
	current(init),
	init(init)
{}

using namespace Globals;

void MenuItemToggle::draw(Window *window, bool cur, int w, int y, int x)
{
	window->print(label.substr(0, w - 4), y, x, cur ? Colours::highlight : Colours::normal, Colours::normal);
	window->print("[", y, x - 4, cur ? Colours::highlight : Colours::normal, Colours::normal);
	window->print(current ? "ON" : "OFF", y, w - 3, cur ? Colours::highlight : Colours::normal, Colours::normal);
	window->print("]", y, x - 1, cur ? Colours::highlight : Colours::normal, Colours::normal);
}

void MenuItemToggle::update(int key)
{
	if (key == KEY_LEFT || key == KEY_RIGHT || key == '\n') {
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