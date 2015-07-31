#pragma once

#include "engine/Colours.hpp"

struct Key;

namespace Ncurses
{
	bool init();
	void exit();
	int getRawKey(int delay);
	Key getKey(int delay);
}