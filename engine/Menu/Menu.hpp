#pragma once

#include "../Config/Globals.hpp"
#include "../State/State.hpp"
#include "MenuData.hpp"
#include "MenuStyle.hpp"

class Manager;
class MenuData;
class MenuStyle;

class Menu : public State
{
public:
	explicit Menu(Manager &manager);
	void draw() override;
	virtual void update() override = 0;
	void exit() override;
	virtual void load() override = 0;
protected:
	virtual void saveSettings() = 0;
	void changeMenu(State *state);
	void resize();
	static MenuStyle *style;
	MenuData *data;
	bool quit;
};
