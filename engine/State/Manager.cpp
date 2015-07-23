#include "engine/State/Manager.hpp"
#include "engine/State/State.hpp"

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
	closeState();
	current = state;
}

void Manager::loop()
{
	current->load();

	while (!quit) {
		current->draw();
		current->update();
	}

	closeState();
}

void Manager::exit()
{
	quit = true;
}

void Manager::change(State *state)
{
	init(state);
	current->load();
}

void Manager::closeState()
{
	if (current) {
		current->exit();
		delete current;
		current = nullptr;
	}
}