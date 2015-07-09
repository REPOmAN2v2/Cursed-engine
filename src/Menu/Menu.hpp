#pragma once

#include <State/State.hpp>
#include <Config/Globals.hpp>
#include "MenuStyle.hpp"
#include "MenuData.hpp"
#include "Items/MenuItemTemplates.hpp"

class Menu : public State
{
public:
	Menu(Manager &manager);
	void draw();
	virtual void update() = 0;
	void exit();
	virtual void load() = 0;
protected:
	virtual void saveSettings() = 0;
	void resize();
	MenuStyle *style;
	MenuData *data;
};