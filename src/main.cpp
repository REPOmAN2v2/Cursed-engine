#include "ncurses.hpp"
#include "State/Manager.hpp"
#include "Menu/MainMenu.hpp"
#include "Config/Globals.hpp"
#include <iostream>

int main()
{
	Globals::load();	
	Ncurses::init();

	Manager manager;
	State *state = new MainMenu(manager);

	manager.init(state);
	manager.loop();
	
	Ncurses::exit();
	Globals::save();
}