#pragma once

#include <State/State.hpp>
#include "MenuStyle.hpp"
#include "MenuData.hpp"
#include "MenuItemTemplates.hpp"

class Menu : public State
{
public:
	Menu();
	~Menu();
	void createMainMenu();
	void createPlayMenu();
	void createSettingsMenu();
	void draw();
	bool update();
	void exit();
	void resize();
	void load();
private:
	MenuStyle *style;
	MenuData *data;
};