#pragma once

#include "style.hpp"
#include "window.hpp"
#include "MenuData.hpp"

class MenuStyle : public Style
{
public:
	MenuStyle(int h, int w);
	~MenuStyle();
	void draw(MenuData *data);
	void resize(MenuData *data, int h, int w);
	void create() override;
	void destroy() override;
	Window *menu;
private:
	void clearScreen();
};