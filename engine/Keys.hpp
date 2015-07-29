#pragma once

#include <vector>

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
		PAGEUP,
		PAGEDOWN,
		UNKNOWN
	};

	int val;

	constexpr Key(int value):mod(Mod::NONE),val(value) {};
	constexpr Key(Mod mod, int value):mod(mod),val(value) {};
	constexpr int value() const { return val; }; //TODO: how to tell if it's modified?

	constexpr bool operator==(Key key) const { return val == key.value(); };
	constexpr bool operator!=(Key key) const { return val != key.value(); };
};

constexpr Key ctrl(int key) {
	return {Key::Mod::CTRL, key};
}

using Keys = std::vector<Key>;