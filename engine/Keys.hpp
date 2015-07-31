#pragma once

#include <vector>
#include <string>

struct Key {
	enum class Mod : int {
		NONE = 0x0,
		CTRL = 0x01,
		ALT = 0x02,
		SUPER = 0x04
	} mod;

	// special values which don't correspond directly to letters
	// if they're not part of the ASCII character set, we'll give them a value > 127
	// TODO: expand this to support every NCurses key value
	enum Special : int {
		ESC = 27,
		SPACE = 40,
		BACK = 127,
		UP = 128,
		DOWN,
		LEFT,
		RIGHT,
		PPAGE,
		NPAGE,
		ENTER,
		UNKNOWN
	};

	int val;

	constexpr Key(int value):mod(Mod::NONE),val(value) {};
	constexpr Key(Mod mod, int value):mod(mod),val(value) {};
	//TODO: how to tell if it's modified? Right now this method is useless
	constexpr int value() const { return val; };

	constexpr bool operator==(Key key) const { return val == key.value(); };
	constexpr bool operator!=(Key key) const { return val != key.value(); };
};

using KeyMap = std::vector<Key>;

// TODO: add alt support somehow
constexpr Key ctrl(int key) {
	return {Key::Mod::CTRL, key};
}

std::string toStr(Key key); 