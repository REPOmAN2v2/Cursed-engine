#pragma once

#include <vector>
#include <string>

namespace Globals
{
	void load();
	void save();

	namespace Settings
	{
		extern int height;
		extern int max_height;
		extern int width;
		extern int max_width;
	}

	namespace Colours
	{
		extern int highlight;
		extern int title;
		extern int normal;
	}

	// http://patorjk.com/software/taag/#p=testall&v=0&f=Alpha&t=CURSED
	// for all your ASCII text needs
	const std::vector<std::string> title = {"     _/_/_/  _/    _/  _/_/_/      _/_/_/  _/_/_/_/  _/_/_/ ",
											"  _/        _/    _/  _/    _/  _/        _/        _/    _/",
											" _/        _/    _/  _/_/_/      _/_/    _/_/_/    _/    _/ ",
											"_/        _/    _/  _/    _/        _/  _/        _/    _/  ",
 											"_/_/_/    _/_/    _/    _/  _/_/_/    _/_/_/_/  _/_/_/      " };
	const int title_length = 60;
	const int title_height = 6;
}