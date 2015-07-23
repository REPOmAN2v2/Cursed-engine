#include "Menu.hpp"
#include "engine/Menu/../Config/Globals.hpp"
#include "engine/Menu/../State/Manager.hpp"
#include "engine/Menu/../State/State.hpp"
#include "engine/Menu/MenuData.hpp"
#include "engine/Menu/MenuStyle.hpp"

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
	style->resize(data, Globals::Settings::height, Globals::Settings::width);
}

void Menu::changeMenu(State *state)
{
	// this lets us change menu states without rewriting the entire window
	quit = false;
	manager.change(state);
}
