#pragma once

#include "Manager.hpp"

class State
{
public:
	State(Manager &manager):manager(manager) {};
	virtual ~State() {};
	virtual void load() = 0;
	virtual void exit() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	void change(State *state)
	{
		manager.change(state);
	}
protected:
	Manager &manager;
};