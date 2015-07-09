#include "SettingsMenu.hpp"
#include "MainMenu.hpp"
#include <climits>

SettingsMenu::SettingsMenu(Manager &manager):Menu(manager) {};

void SettingsMenu::load()
{
	if (data) {
		delete data;
		data = nullptr;
	}

	data = new MenuData(style->menu->getH() - 2,
						style->menu->getW() - 2,
						1,1);

	MenuItem *item;
	item = new MenuItemNumber("Width", ID::WIDTH, Type::NUMBER, -1, INT_MAX, Globals::Settings::width);
	data->addItem(item);
	item = new MenuItemNumber("Height", ID::HEIGHT, Type::NUMBER, -1, INT_MAX, Globals::Settings::height);
	data->addItem(item);
	data->addItem(nullptr);
	item = new MenuItem("Reset", ID::RESET, Type::SIMPLE);
	data->addItem(item);
	item = new MenuItem("Back", ID::BACK, Type::SIMPLE);
	data->addItem(item);
}

void SettingsMenu::update()
{
	data->update();
	static State *menu = nullptr;

	switch (data->whichSelected()) {
		case ID::BACK:
			saveSettings(); 
			/*resize();*/
			menu = new MainMenu(manager);
			manager.change(menu);
			menu = nullptr;
		break;

		case ID::RESET:
			load();
		break;

		default:
		break;
	}
}

void SettingsMenu::saveSettings()
{
	Globals::Settings::width = data->get<int>(ID::WIDTH);
	Globals::Settings::height = data->get<int>(ID::HEIGHT);
}