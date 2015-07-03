#include "ConfigParser.hpp"
#include <vector>
#include <sstream>

std::vector<std::string> split(const std::string &s, char delim) 
{
	std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

ConfigParser::ConfigParser(const std::string config):config(config)
{
	L = luaL_newstate();
	luaL_dofile(L, config.c_str());
	luaL_openlibs(L);
}

ConfigParser::~ConfigParser()
{
	if (L) {
		lua_close(L);
	}
}

bool ConfigParser::exists(const std::string &var)
{
	if (var.empty()) {
		return false;
	}

	int depth = 0;
	auto tokens = split(var, '.');
	for (auto &it : tokens) {
		// Push the tokens and check if they actually exist in the file
		if (!depth) {
			lua_getglobal(L, it.c_str());
		} else {
			lua_getfield(L, -1, it.c_str());
		}

		if (lua_isnil(L, -1)) {
			return false;
		} else {
			++depth;
		}
	}

	return true;
}

void ConfigParser::clean()
{
	int n = lua_gettop(L);
	lua_pop(L, n);
}