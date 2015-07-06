#pragma once

#include <State/State.hpp>
#include "MenuStyle.hpp"
#include "MenuData.hpp"
#include "MenuItemTemplates.hpp"

class Menu : public State
{
public:
	Menu();
	void draw();
	void update(Manager *manager);
	void exit();
	void load();
private:
	void createMainMenu();
	void updateMainMenu(Manager *manager);
	void createPlayMenu();
	void updatePlayMenu(Manager *manager);
	void savePlaySettings();
	void createSettingsMenu();
	void updateSettingsMenu(Manager *manager);
	void saveSettingsSettings(); // yeah I know
	void resize();
	MenuStyle *style;
	MenuData *data;
	enum class MenuType {MAIN, PLAY, SETTINGS} curMenu;
};