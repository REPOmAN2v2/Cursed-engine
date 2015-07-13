#include "MenuStyle.hpp"
#include <Config/Globals.hpp>
#include <algorithm>

MenuStyle::MenuStyle(int h, int w):
	Style(h, w),
	menu(nullptr)
{
	create();
}

void MenuStyle::create()
{
	Style::create();
	destroy();

	title = new Window(main, Globals::title_height + 2, -1, 1, 1);

	int hh = main->getH() - title->getH() - 2;
	int ww = main->getW() / 3;
	int y = title->getH() + 1;
	int x = main->getW() / 3 - 2;

	menu = new Window(main, hh, ww, y, x);

	// windows should be pushed from the background to the foreground
	// otherwise expect the unexpected
	windows.push_back(&main);
	windows.push_back(&title);
	windows.push_back(&menu);
}

MenuStyle::~MenuStyle()
{
	destroy();
}

void MenuStyle::destroy()
{
	if (menu) {
		delete menu;
		menu = nullptr;
	}
}

void MenuStyle::draw(MenuData *data)
{
	clear();
	data->draw(menu);
	title->print(Globals::title, 1, title->getW() / 2 - Globals::title_length/2, COLOR_RED, -1);
	refresh();
}

void MenuStyle::resize(MenuData *data, int h, int w)
{
	_h = h;
	_w = w;
	clearScreen();
	create();
	draw(data);
}

void MenuStyle::clearScreen()
{
	clear();
	refresh();
}

void MenuStyle::clear()
{
	std::for_each(windows.begin(), windows.end(), [this](Window** &w){(**w).clear();});
}

void MenuStyle::refresh()
{
	std::for_each(windows.rbegin(), windows.rend(), [this](Window** &w){(**w).refresh();});
}

void MenuStyle::setBorders()
{
	std::for_each(windows.begin(), windows.end(), [this](Window** &w){(**w).setBorders();});
}