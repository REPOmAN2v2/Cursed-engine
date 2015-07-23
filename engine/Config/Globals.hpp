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

	namespace Title
	{
		// http://patorjk.com/software/taag/#p=testall&v=0&f=Alpha&t=CURSED
		// for all your ASCII text needs
		extern std::vector<std::string> title;
		extern int length;
		extern int height;
	}
}