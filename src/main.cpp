#include "ncurses.hpp"
#include "State/Manager.hpp"
#include "Menu/Menu.hpp"
#include "Config/Globals.hpp"
#include <iostream>

int main()
{
	Globals::load();	
	Ncurses::init();

	Manager manager;
	State *state = new Menu();

	manager.loop(state);
	
	/*menu.createMainMenu();
	menu.draw();

	while (!menu.update()) {
		menu.draw();
	}

	menu.exit();*/
	Ncurses::exit();
}