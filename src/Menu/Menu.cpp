#include "Menu.hpp"
#include <vector>
#include <climits>

Menu::Menu():data(nullptr)
{
	style = new MenuStyle(20, 79);
}

void Menu::createMainMenu()
{
	if (data) {
		delete data;
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

void Menu::createPlayMenu()
{
	if (data) {
		delete data;
	}

	data = new MenuData(style->menu->getH() - 2,
						style->menu->getW() - 2,
						1,1);

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
	}

	data = new MenuData(style->menu->getH() - 2,
						style->menu->getW() - 2,
						1,1);

	MenuItem *item;
	item = new MenuItemNumber("Width", ID::WIDTH, Type::NUMBER, 0, INT_MAX, 79);
	data->addItem(item);
	item = new MenuItemNumber("Height", ID::HEIGHT, Type::NUMBER, 0, INT_MAX, 20);
	data->addItem(item);
	data->addItem(nullptr);
	item = new MenuItem("Back", ID::BACK, Type::SIMPLE);
	data->addItem(item);
}

Menu::~Menu()
{
	exit();
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

bool Menu::update()
{
	data->update();
	switch (data->whichSelected()) {
		case ID::QUIT:
			return true;
		break;

		case ID::PLAYMENU:
			createPlayMenu();
		break;

		case ID::SETTINGS:
			createSettingsMenu();
		break;

		case ID::BACK:
			createMainMenu();
		break;

		default:
		break;
	} 

	return false;
}

void Menu::resize()
{
	//style->menu->resize(y,x);
}