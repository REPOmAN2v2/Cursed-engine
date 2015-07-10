#include "MenuStyle.hpp"

MenuStyle::MenuStyle(int h, int w):
	Style(h, w),
	menu(nullptr)
{
	create();
}

void MenuStyle::create()
{
	Style::create();
	int hh = main->getH() - 11;
	int ww = main->getW() / 3;
	int y = 11;
	int x = main->getW() / 3;

	destroy();
	menu = new Window(main, hh, ww, y, x);
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
	main->clear();
	menu->clear();
	data->draw(menu);
	menu->setBorders();
	main->setBorders();
	menu->refresh();
	main->refresh();
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
	main->clear();
	menu->clear();
	menu->refresh();
	main->refresh();
}