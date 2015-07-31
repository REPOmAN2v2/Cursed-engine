#include <memory>
#include <algorithm>
#include <cstdio>
#include <stddef.h>

#include "Colours.hpp"

using namespace Colours;

// This array should be in the same order as Colour::ColourName
static constexpr const char * names[] = {
	"default",
	"red",
	"blue",
	"green",
	"yellow",
	"magenta",
	"cyan",
	"black",
	"white"
};

// TODO: move this to a utils header
template<typename ... Args>
static std::string string_format( const char* format, Args ... args )
{
    size_t size = std::snprintf( nullptr, 0, format, args ... ) + 1; // Extra space for '\0'
    std::unique_ptr<char[]> buf( new char[ size ] ); 
    std::snprintf( buf.get(), size, format, args ... );
    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}

// either a colour name or an hexadecimal RGB sequence
Colour toColour(std::string str)
{
	auto it = std::find_if(names, std::end(names), [&](const char *c){return str.c_str() == c;});

	if (it != std::end(names)) {
		return static_cast<Colour::ColourName>(it - names);
	}

	auto hex = [&str](char c) -> int
	{
		if (c >= 'A' && c <= 'F')
			return 10 + c -'A';
		else if (c >= 'a' && c <= 'f')
			return 10 + c -'a';
		else if (c >= '0' && c <= '9')
			return c -'0';
		return 0;
	};

	if (str.size() == 6) {
		return { static_cast<unsigned char>(hex(str[0]) * 16 + hex(str[1])),
				 static_cast<unsigned char>(hex(str[2]) * 16 + hex(str[3])),
				 static_cast<unsigned char>(hex(str[4]) * 16 + hex(str[5])) };
	}

	return Colour::DEFAULT;
}

std::string toColour(Colour colour)
{
	if (colour.name == Colour::RGB) {
		return string_format("%02x%02x%02x", colour.r, colour.g, colour.b);
	}

	return names[static_cast<size_t>(colour.name)];
}