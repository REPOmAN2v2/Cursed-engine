#pragma once

#include <string>
#include <utility>

namespace Colours
{
	struct Colour {
		enum ColourName : char {
			DEFAULT,
			RED,
			BLUE,
			GREEN,
			YELLOW,
			MAGENTA,
			CYAN,
			BLACK,
			WHITE,
			RGB
		} name;

		unsigned char r = 0;
		unsigned char g = 0;
		unsigned char b = 0;

		constexpr Colour():name(DEFAULT) {};
		constexpr Colour(ColourName name):name(name) {};
		constexpr Colour(unsigned char r, unsigned char g, unsigned char b)
			:name(RGB), r(r), g(g), b(b) {};
	};

	typedef std::pair<Colour, Colour> ColourPair;

	constexpr bool operator==(const Colour &lhs, const Colour &rhs)
	{
		return lhs.name == rhs.name && lhs.r == rhs.r && lhs.g == rhs.g
			   && lhs.b == rhs.b;
	}

	constexpr bool operator!=(const Colour &lhs, const Colour &rhs)
	{
		return !(lhs == rhs);
	}

	inline bool operator<(Colour lhs, Colour rhs)
	{
		if (lhs.name == Colour::RGB && lhs.name == rhs.name) {
			return lhs.r == rhs.r ? 
				   (lhs.g == rhs.g ? lhs.b < rhs.b : lhs.g < rhs.g)
				   : lhs.r < rhs.r;
		}
	       
	    return lhs.name < rhs.name;
	}

	Colour toColour(std::string str);
	std::string toString(Colour colour);
}