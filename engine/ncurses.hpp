#pragma once

#include "engine/Colours.hpp"

namespace Ncurses
{
	bool init();
	void exit();
	int getKey(int delay);
}