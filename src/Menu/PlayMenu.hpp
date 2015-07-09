#pragma once

#include "Menu.hpp"

class PlayMenu : public Menu {
public:
	PlayMenu(Manager &manager);
	void update() override;
	void load() override;
private:
	void saveSettings() override;
};