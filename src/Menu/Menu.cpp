#include "Menu.hpp"
#include <vector>

// TODO: move these to a config file (JSON?)
static std::vector<MenuItemTemplate> mainMenuItems = {
	MenuItemTemplate("Play", ID::PLAYMENU, Type::SIMPLE),
	MenuItemTemplate("Settings", ID::SETTINGS, Type::SIMPLE),
	MenuItemTemplate("Help", ID::HELP, Type::SIMPLE),
	MenuItemTemplate("Quit", ID::QUIT, Type::SIMPLE)
};

static std::vector<std::string> simSpeed = {"Slow", "Normal", "Fast"};

static std::vector<MenuItemTemplate> playMenuItems = {
	MenuItemTemplate("Launch game", ID::PLAY, Type::SIMPLE),
	MenuItemTemplate("Back", ID::BACK, Type::SIMPLE),
	MenuItemTemplate(nullptr, ID::NONE, Type::NONE),
	MenuItemTemplate("Doctors", ID::DOCTORS, Type::NUMBER, 0, 100, 5),
	MenuItemTemplate("Infected", ID::INFECTED, Type::NUMBER, 0, 100, 8),
	MenuItemTemplate("Nurses", ID::NURSES, Type::NUMBER, 0, 100, 6),
	MenuItemTemplate("Soldiers", ID::SOLDIERS, Type::NUMBER, 0, 100, 10),
	MenuItemTemplate("Lumber", ID::LUMBER, Type::NUMBER, 0, 1000, 50),
	MenuItemTemplate(nullptr, ID::NONE, Type::NONE),
	MenuItemTemplate("Sim speed", ID::SPEED, Type::LIST, simSpeed, "Normal"),
	MenuItemTemplate("Step", ID::STEP, Type::TOGGLE),
	MenuItemTemplate("Reset", ID::RESET, Type::SIMPLE)
};

Menu::Menu():data(nullptr)
{
	style = new MenuStyle(20, 79);
}

void Menu::createMainMenu()
{
	createMenu(mainMenuItems);
}

void Menu::createMenu(std::vector<MenuItemTemplate> &itemTemplate)
{
	if (data) {
		delete data;
	}

	data = new MenuData(style->menu->getH() - 2,
						style->menu->getW() - 2,
						1,1);

	for (auto it : itemTemplate) {
		if (it.name) {
			MenuItem *item;

			if (it.type == Type::NUMBER) {
				item = new MenuItemNumber(it);
			} else if (it.type == Type::LIST) {
				item = new MenuItemList(it);
			} else {
				item = new MenuItem(it);
			}

			data->addItem(item);
		} else {
			data->addItem(nullptr);
		}
	}
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
			createMenu(playMenuItems);
		break;

		case ID::BACK:
			createMenu(mainMenuItems);
		break;

		default:
		break;
	} 

	return false;
}