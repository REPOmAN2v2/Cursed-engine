#include <ncurses.h>

#include "engine/Config/Globals.hpp"
#include "engine/ncurses.hpp"

bool Ncurses::init()
{
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	curs_set(0);
	start_color();
	use_default_colors();

	Globals::Settings::max_height = LINES;
	Globals::Settings::max_width = COLS;

	// TODO: add some glue to move these assignments out of there;

	refresh();

	return true; // TODO: error handling
}

void Ncurses::exit()
{
	erase();
	refresh();
	endwin();
}

int Ncurses::getKey(int delay)
{
	timeout(delay);
	int c = getch();
	timeout(0);
	return c;
}
