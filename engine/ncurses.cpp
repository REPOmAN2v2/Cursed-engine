#include "ncurses.hpp"
#include "Config/Globals.hpp"
#include <ncurses.h>

bool Ncurses::init()
{
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	curs_set(0);
	start_color();

	Globals::Settings::max_height = LINES;
	Globals::Settings::max_width = COLS;


	/*  Color pair 0 is reserved for default colours, we start indexing at 1
		8 colours from 0 to 7: black, red, green, yellow, blue, magenta, cyan, white
		64 combinations so n=64 pairs. To get the colours i,j in the pair:
		i = (int)(n - 1)/8 and j = (n - 1)%8
		To get the pair from the colours:
		n = i*8 + 1 + j
		*/
	for (int i = COLOR_BLACK, k = 1; i <= COLOR_WHITE; ++i) {
		for (int j = COLOR_BLACK; j <= COLOR_WHITE; ++j) {
			init_pair(k, i, j);
			++k;
		}
	}

	/*	Now for just coloured text */
	use_default_colors();
	for (int i = 65, j = COLOR_BLACK; j <= COLOR_WHITE; ++i, ++j) {
		init_pair(i, j, -1);
	}

	// TODO: add some glue to move these assignments out of there;
	Globals::Colours::highlight = COLOR_GREEN;
	Globals::Colours::title = COLOR_RED;
	Globals::Colours::normal = -1;

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