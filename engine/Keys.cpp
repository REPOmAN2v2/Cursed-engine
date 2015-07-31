#include "Keys.hpp"

#include <algorithm>
#include <memory>

// TODO: Fix SPACE! right now it's captured as ^M !
// TODO: Fix TAB! right now it's captured as ^I !

static constexpr struct NamedKeys {
	const char *name;
	int val;
} names[] = {
	{"escape", Key::ESC},
	{"space", Key::SPACE},
	{"backspace", Key::BACK},
	{"up", Key::UP},
	{"down", Key::DOWN},
	{"left", Key::LEFT},
	{"right", Key::RIGHT},
	{"pageup", Key::PPAGE},
	{"pagedown", Key::NPAGE},
	{"enter", Key::ENTER},
	{"unknown", Key::UNKNOWN}
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

std::string toStr(Key key)
{
	auto it = std::find_if(names, std::end(names), [&key](const NamedKeys &name) {return name.val == key.val;});

	if (it != std::end(names)) {
		return it->name;
	}

	std::string val = string_format("%c", key.val);
	std::string mod;
	if (key.mod == Key::Mod::CTRL) {
		mod = "Ctrl-";
	}
	if (key.mod == Key::Mod::ALT) {
		mod += "Alt-";
	}
	return mod + val;
}