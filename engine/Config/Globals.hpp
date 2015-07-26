#pragma once

#include <vector>
#include <string>
#include <map>

//#include "engine/Attributes.hpp"

struct Attributes;

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

	/*namespace Text
	{
		const Attributes highlight(Colours::Colour::GREEN);
		const Attributes title(Colours::Colour::RED, Colours::Colour::DEFAULT, Attributes::BLINK);
		const Attributes normal();
		const Attributes highlight(Colours::Colour::GREEN);
		const Attributes title(Colours::Colour::RED, Colours::Colour::DEFAULT, Attributes::BLINK);
		const Attributes normal(); 
	}*/

	extern std::map<std::string, Attributes> text;

	namespace Title
	{
		// http://patorjk.com/software/taag/#p=testall&v=0&f=Alpha&t=CURSED
		// for all your ASCII text needs
		extern std::vector<std::string> title;
		extern int length;
		extern int height;
	}
}