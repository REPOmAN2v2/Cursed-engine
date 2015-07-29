#pragma once

#include "engine/Colours.hpp"

struct Key;

namespace Ncurses
{
	bool init();
	void exit();
	int getKey(int delay);
	Key getTestKey(int delay);
}