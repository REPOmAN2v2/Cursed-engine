#pragma once

#include <string>

extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

class ConfigParser
{
public:
	ConfigParser(const std::string config);
	~ConfigParser();

	template<typename T>
	T get(const std::string &var)
	{
		T value;
		if (exists(var)) {
			value = getValue<T>();
		} else {
			value = getDefault<T>();
		}

		clean();
		return value;
	}

	template<typename T>
	T getValue()
	{
		return 0;
	}

	template<typename T>
	T getDefault()
	{
		return 0;
	}

private:
	lua_State *L;
	const std::string config;
	bool exists(const std::string &var);
	void clean();
};

// getValue() and getDefault() template specialisations

template<>
inline bool ConfigParser::getValue<bool>()
{
	return (bool)lua_toboolean(L, -1);
}

template<>
inline float ConfigParser::getValue<float>()
{
	if (lua_isnumber(L, -1)) {
		return (float)lua_tonumber(L,-1);
	}

	return getDefault<float>();
}

template<>
inline int ConfigParser::getValue<int>()
{
	if (lua_isnumber(L, -1)) {
		return (int)lua_tonumber(L,-1);
	}

	return getDefault<int>();
}

template<>
inline std::string ConfigParser::getDefault<std::string>()
{
	return nullptr;
}

template<>
inline std::string ConfigParser::getValue<std::string>()
{
	if (lua_isstring(L, -1)) {
		return std::string(lua_tostring(L, -1));
	}

	return getDefault<std::string>();
}

