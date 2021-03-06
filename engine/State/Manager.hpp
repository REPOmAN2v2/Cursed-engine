#pragma once

class State;

class Manager
{
public:
	Manager();
	~Manager();
	void init(State *state);
	void change(State *state);
	void loop();
	void exit();
private:
	void closeState();
	State *current;
	bool quit;
};