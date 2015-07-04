#pragma once

class State
{
public:
	virtual ~State() {};
	virtual void load() = 0;
	virtual void exit() = 0;
	virtual bool update() = 0;
	virtual void draw() = 0;
};