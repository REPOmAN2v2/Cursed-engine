#pragma once

#include "Manager.hpp"

class State
{
public:
	virtual ~State() {};
	virtual void load() = 0;
	virtual void exit() = 0;
	virtual void update(Manager *manager) = 0;
	virtual void draw() = 0;
	void change(Manager *manager, State *state)
	{
		manager->change(state);
	}
};