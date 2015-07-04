#include "ncurses.hpp"
#include "Menu/Menu.hpp"
#include "Config/Globals.hpp"
#include <iostream>

int main()
{
	Globals::load();
	std::cout << Globals::Settings::height << std::endl;
	
	Ncurses::init();
	Menu menu;
	menu.createMainMenu();
	menu.draw();

	while (!menu.update()) {
		menu.draw();
	}

	menu.exit();
	Ncurses::exit();
}