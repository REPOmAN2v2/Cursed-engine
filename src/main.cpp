#include "ncurses.hpp"
#include "Menu/Menu.hpp"
#include "Lua/ConfigParser.hpp"

int main()
{
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