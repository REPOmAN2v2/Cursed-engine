#pragma once

#include "State.hpp"

class Manager
{
public:
	Manager();
	~Manager();
	void change(State *state);
	void loop(State *state);
private:
	State *current;
};