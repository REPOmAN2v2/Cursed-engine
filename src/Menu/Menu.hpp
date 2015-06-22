#pragma once

#include "MenuStyle.hpp"
#include "MenuData.hpp"
#include "MenuItemTemplates.hpp"

class Menu
{
public:
	Menu();
	~Menu();
	void createMainMenu();
	void createPlayMenu();
	void draw();
	bool update();
	void exit();
private:
	MenuStyle *style;
	MenuData *data;
};