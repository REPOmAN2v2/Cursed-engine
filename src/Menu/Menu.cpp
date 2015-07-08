#include "Menu.hpp"
#include <Config/Globals.hpp>
#include <vector>
#include <climits>

// TODO: make each submenu inherit this class ? 

Menu::Menu():data(nullptr)
{}

void Menu::load()
{
	style = new MenuStyle(Globals::Settings::height, Globals::Settings::width);
	createMainMenu();
}

void Menu::createMainMenu()
{
	if (data) {
		delete data;
		data = nullptr;
	}

	data = new MenuData(style->menu->getH() - 2,
						style->menu->getW() - 2,
						1,1);

	curMenu = MenuType::MAIN;

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

void Menu::createPlayMenu()
{
	if (data) {
		delete data;
		data = nullptr;
	}

	data = new MenuData(style->menu->getH() - 2,
						style->menu->getW() - 2,
						1,1);

	curMenu = MenuType::PLAY;

	static const std::vector<std::string> simSpeed = {"Slow", "Normal", "Fast"};

	MenuItem *item;
	item = new MenuItem("Launch game", ID::PLAY, Type::SIMPLE);
	data->addItem(item);
	item = new MenuItem("Back", ID::BACK, Type::SIMPLE);
	data->addItem(item);
	data->addItem(nullptr);
	item = new MenuItemNumber("Doctors", ID::DOCTORS, Type::NUMBER, 0, 100, 5);
	data->addItem(item);
	item = new MenuItemNumber("Infected", ID::INFECTED, Type::NUMBER, 0, 100, 8);
	data->addItem(item);
	item = new MenuItemNumber("Nurses", ID::NURSES, Type::NUMBER, 0, 100, 6);
	data->addItem(item);
	item = new MenuItemNumber("Soldiers", ID::SOLDIERS, Type::NUMBER, 0, 100, 10);
	data->addItem(item);
	item = new MenuItemNumber("Lumber", ID::LUMBER, Type::NUMBER, 0, 1000, 50);
	data->addItem(item);
	data->addItem(nullptr);
	item = new MenuItemList("Sim speed", ID::SPEED, Type::LIST, simSpeed, "Normal");
	data->addItem(item);
	item = new MenuItemToggle("Step", ID::STEP, Type::TOGGLE, false);
	data->addItem(item);
	item = new MenuItem("Reset", ID::RESET, Type::SIMPLE);
	data->addItem(item);
}

void Menu::createSettingsMenu()
{
	if  (data) {
		delete data;
		data = nullptr;
	}

	data = new MenuData(style->menu->getH() - 2,
						style->menu->getW() - 2,
						1,1);

	curMenu = MenuType::SETTINGS;

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

void Menu::update(Manager *manager)
{
	data->update();
	if (curMenu == MenuType::MAIN) {
		updateMainMenu(manager);
	} else if (curMenu == MenuType::PLAY) {
		updatePlayMenu(manager);
	} else if (curMenu == MenuType::SETTINGS) {
		updateSettingsMenu(manager);
	}
}

void Menu::updateMainMenu(Manager *manager)
{
	switch (data->whichSelected()) {
		case ID::QUIT:
			manager->exit();
		break;

		case ID::PLAYMENU:
			createPlayMenu();
		break;

		case ID::SETTINGS:
			createSettingsMenu();
		break;

		default:
		break;
	}
}

void Menu::updatePlayMenu(Manager *manager)
{
	switch (data->whichSelected()) {
		case ID::PLAY:
			/* State *game = new Game();
			manager->change(game);*/
		break;

		case ID::BACK:
			savePlaySettings();
			createMainMenu();
		break;

		case ID::RESET:
		// overkill but easier that way right now
		// TODO: iterate over items and reset them one by one
		// probably faster and they already store their original value
			createPlayMenu(); 
		break;

		default:
		break;
	}
}

void Menu::updateSettingsMenu(Manager *manager)
{
	switch (data->whichSelected()) {
		case ID::BACK:
			saveSettingsSettings(); 
			/*resize();*/
			createMainMenu();
		break;

		case ID::RESET:
			createSettingsMenu();
		break;

		default:
		break;
	}
}

void Menu::savePlaySettings()
{
	// empty for now
}

void Menu::saveSettingsSettings()
{
	Globals::Settings::width = data->get<int>(ID::WIDTH);
	Globals::Settings::height = data->get<int>(ID::HEIGHT);
}

void Menu::resize()
{
	//style->menu->resize(y,x);
}