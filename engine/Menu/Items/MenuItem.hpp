#pragma once

#include <string>

class Window;

class MenuItem
{
public:
	enum class Type : unsigned int {
		NONE = 0,
		SIMPLE,
		NUMBER,
		LIST,
		TOGGLE
	} type; 
	
	MenuItem(const char *label, unsigned id, MenuItem::Type type);
	virtual ~MenuItem() {};
	virtual void draw(Window *window, bool cur, int w, int y, int x);
	virtual void update(int) {};
	virtual void reset() {};

	unsigned id;
	std::string label;
};
