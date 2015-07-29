#include <ncurses.h>

#include "engine/Config/Globals.hpp"
#include "engine/ncurses.hpp"
#include "engine/Keys.hpp"

bool Ncurses::init()
{
	initscr();
	raw();
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

// if delay == -1, wait until we get a key
// if delay == 0, don't wait at all
int Ncurses::getKey(int delay)
{
	timeout(delay);
	int c = getch();
	timeout(0);
	return c;
}

Key Ncurses::getTestKey(int delay)
{
	timeout(delay);

	const int c = getch();

	// First, we'll check for special values
	// We start with ctrl + letter
	if (c > 0 && c < 27) {
		// convert c to its corresponding letter then to a key
		// eg '^A' = 1 and 'a' = 97
		return ctrl(c - 1 + 'a');
	} 

	// Now named keys
	switch (c) {
		case 27: return Key::ESC;
		case 40: return Key::SPACE;
		case KEY_BACKSPACE: // fallthrough
		case 127: return Key::BACK;
		case KEY_UP: return Key::UP;
		case KEY_DOWN: return Key::DOWN;
		case KEY_LEFT: return Key::LEFT;
		case KEY_RIGHT: return Key::RIGHT;
		case KEY_PPAGE: return Key::PAGEUP;
		case KEY_NPAGE: return Key::PAGEDOWN;
	}

	return (c >=0 && c < 256) ? c : Key::UNKNOWN;
}
