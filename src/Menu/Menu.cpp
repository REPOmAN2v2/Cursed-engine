#include "Menu.hpp"

MenuStyle *Menu::style = nullptr;

Menu::Menu(Manager &manager):State(manager),data(nullptr),quit(true)
{
	if (!style) {
		style = new MenuStyle(Globals::Settings::height, Globals::Settings::width);
	}
}

void Menu::exit()
{
	if (data) {
		data->clear();
		delete data;
		data = nullptr;
	}

	if (style && quit) {
		delete style;
		style = nullptr;
		quit = true;
	}
}

void Menu::draw()
{
	style->draw(data);
}

void Menu::resize()
{
	//style->menu->resize(y,x);
}

void Menu::changeMenu(State *state)
{
	// this lets us change menu states without rewriting the entire window
	quit = false;
	manager.change(state);
}