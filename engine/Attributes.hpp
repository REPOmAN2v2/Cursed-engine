#pragma once

#include <stdint.h>
#include "engine/Colours.hpp"

struct Attributes {
	enum Flags : uint8_t {
		NORMAL = 0x0,
		BOLD = 0x01,
		UNDERLINE = 0x02,
		DIM = 0x04,
		REVERSE = 0x8,
		BLINK = 0x10, 
		// Deprecated, can be used to mark text as protected (eg shouldn't be deleted in a form)
		PROTECT = 0x20, 
		INVIS = 0x40,
		UNUSED0 = 0x80,
		// This flag is basically deprecated, repurpose it
		STANDOUT = UNDERLINE | BOLD | BLINK
	} flags;
	Colours::Colour fg;
	Colours::Colour bg;

	constexpr Attributes(Colours::Colour fg = Colours::Colour::DEFAULT,
						 Colours::Colour bg = Colours::Colour::DEFAULT,
						 Flags flags = Flags::NORMAL) :
						 flags(flags), fg(fg), bg(bg) {};
};

constexpr bool operator==(const Attributes &lhs, const Attributes &rhs)
{
	return lhs.flags == rhs.flags 
		   && lhs.fg == rhs.fg 
		   && lhs.bg == rhs.bg;
}

constexpr bool operator!=(const Attributes &lhs, const Attributes &rhs)
{
	return !(lhs == rhs);
}
