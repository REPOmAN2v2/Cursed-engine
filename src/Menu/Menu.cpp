#include "Menu.hpp"

Menu::Menu(Manager &manager):State(manager),style(nullptr),data(nullptr)
{
	style = new MenuStyle(Globals::Settings::height, Globals::Settings::width);
}

void Menu::exit()
{
	if (data) {
		data->clear();
		delete data;
		data = nullptr;
	}

	if (style) {
		delete style;
		style = nullptr;
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