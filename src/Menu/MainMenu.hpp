#pragma once

#include "Menu.hpp"

class MainMenu : public Menu {
public:
	MainMenu(Manager &manager);
	void update() override;
	void load() override;
private:
	void saveSettings() override {};
	void spawnHelp();
};