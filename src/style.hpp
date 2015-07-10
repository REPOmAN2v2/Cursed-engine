#pragma once

#include "window.hpp"

class Style
{
public:
	Style(int h, int w);
	virtual ~Style();
	virtual void create();
	virtual void destroy();
	//virtual void draw() {};
	Window *main;
protected:
	int _h, _w;
};