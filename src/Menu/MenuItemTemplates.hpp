#pragma once

#include <vector>
#include <string>

enum class Type {
	NONE,
	SIMPLE,
	NUMBER,
	LIST,
	TOGGLE
}; 

enum class ID {
	NONE,
	BACK,
	//specific to the main menu
	PLAYMENU,
	SETTINGS, 
	HELP, 
	QUIT,
	TEST0,
	TEST1,
	TEST2,
	//specific to the play menu
	PLAY,
	DOCTORS,
	INFECTED,
	NURSES,
	SOLDIERS,
	LUMBER,
	SPEED,
	STEP,
	RESET
};

struct MenuItemTemplate {
	const char *name;
	enum ID id;
	enum Type type;
	int min, max, start;
	std::vector<std::string> list;
	std::string def;

	MenuItemTemplate(
		const char *name, 
		enum ID id, 
		enum Type type,
		int min = 0,
		int max = 0,
		int start = 0):
		name(name),id(id),type(type),
		min(min),max(max),start(start),
		list({}), def("")
	{};


	MenuItemTemplate(
		const char *name, 
		enum ID id, 
		enum Type type,
		std::vector<std::string> list,
		std::string def):
		name(name),id(id),type(type),
		min(0),max(0),start(0),
		list(list), def(def)
	{};
};
