#include "Manager.hpp"

Manager::Manager():current(nullptr)
{}

Manager::~Manager()
{
	if (current) {
		current->exit();
		delete current;
	}

	current = nullptr;
}

void Manager::loop(State *state)
{
	current = state;
	current->load();

	do {
		current->draw();
	} while (!current->update());

	current->exit();
	delete current;
	current = nullptr;
}