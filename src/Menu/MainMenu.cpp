#include "MainMenu.hpp"
#include "PlayMenu.hpp"
#include "SettingsMenu.hpp"

MainMenu::MainMenu(Manager &manager):Menu(manager) {};

void MainMenu::load()
{
	if (data) {
		delete data;
		data = nullptr;
	}

	data = new MenuData(style->menu->getH() - 2,
						style->menu->getW() - 2,
						1,1);

	MenuItem *item;
	item = new MenuItem("Play", ID::PLAYMENU, Type::SIMPLE);
	data->addItem(item);
	item = new MenuItem("Settings", ID::SETTINGS, Type::SIMPLE);
	data->addItem(item);
	item = new MenuItem("Help", ID::HELP, Type::SIMPLE);
	data->addItem(item);
	item = new MenuItem("Quit", ID::QUIT, Type::SIMPLE);
	data->addItem(item);
}

void MainMenu::update()
{
	data->update();
	static State *menu = nullptr;

	switch (data->whichSelected()) {
		case ID::QUIT:
			manager.exit();
		break;

// TODO: this is very wasteful. Find a system (instances?) to only recreate the xxxxMenu,
// not the parent classes all over again
		case ID::PLAYMENU: 
			menu = new PlayMenu(manager);
			manager.change(menu);
			menu = nullptr;
		break;

		case ID::SETTINGS:
			menu = new SettingsMenu(manager);
			manager.change(menu);
			menu = nullptr;
		break;

		default:
		break;
	}
}