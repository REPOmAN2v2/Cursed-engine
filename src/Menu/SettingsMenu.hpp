#pragma once

#include "Menu.hpp"

class SettingsMenu : public Menu {
public:
	SettingsMenu(Manager &manager);
	void update() override;
	void load() override;
private:
	void saveSettings() override;
};