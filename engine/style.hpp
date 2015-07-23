#pragma once

#include "window.hpp"

class Window;

class Style
{
public:
	Style(int h, int w);
	virtual ~Style();
	virtual void create();
protected:
	virtual void destroy();
	Window *main;
	int _h, _w;
};
