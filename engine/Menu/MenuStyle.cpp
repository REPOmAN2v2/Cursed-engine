#include <algorithm>
#include <string>

#include "engine/Config/Globals.hpp"
#include "engine/Menu/MenuStyle.hpp"
#include "engine/window.hpp"
#include "engine/Menu/MenuData.hpp"

MenuStyle::MenuStyle(int h, int w):
	Style(h, w),
	title(nullptr),
	menu(nullptr)
{
	create();
}

void MenuStyle::create()
{
	Style::create();
	destroy();

	title = new Window(main, Globals::Title::height + 2, -1, 1, 1);

	int h = main->getH() - title->getH() - 2;
	int w = main->getW() / 3;
	int y = title->getH() + 1;
	int x = main->getW()/2 - w/2;

	menu = new Window(main, h, w, y, x);

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

	if (title) {
		delete title;
		title = nullptr;
	}
}

void MenuStyle::draw(MenuData *data)
{
	clear();
	data->draw(menu);
	title->print(Globals::Title::title, 1, title->getW() / 2 - Globals::Title::length/2, COLOR_RED, -1);
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
	std::for_each(windows.begin(), windows.end(), [this](Window** &w){(**w).toggleBorders();});
}
