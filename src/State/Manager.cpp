#include "Manager.hpp"
#include "State.hpp"

Manager::Manager():current(nullptr),quit(false)
{}

Manager::~Manager()
{
	if (current) {
		current->exit();
		delete current;
	}

	current = nullptr;
}

void Manager::init(State *state)
{
	current = state;
}

void Manager::loop()
{
	current->load();

	while (!quit) {
		current->draw();
		current->update(this);
	}

	current->exit();
	delete current;
	current = nullptr;
}

void Manager::exit()
{
	quit = true;
}