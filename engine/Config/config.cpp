#include <cstdlib> // for std::exit(1), EXIT_FAILURE
#include <iostream>

#include "engine/Config/config.hpp"

// TODO: check if library functions are already overloaded for char*/std:string
Config * ConfigIO::open(const char *file)
{
	auto cfg = new Config();

	try {
		cfg->readFile(file);
	} catch (const FileIOException &fioex) {
		std::cerr << "Config file could not be read, falling back to hardcoded defaults." << std::endl;
		delete cfg;
		cfg = nullptr;
	} catch (const ParseException &pex) {
		std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
	          << " - " << pex.getError() << std::endl;
		std::exit(EXIT_FAILURE);
	}

	return cfg;
}

/*template<typename T>
void ConfigIO::lookup(Config *cfg, T &val, const char* str)
{
	try {
		const Setting &tmp = cfg->lookup(str);
		val = tmp;
	} catch (const SettingNotFoundException) {
		// setting doesn't exist, we'll fall back to the hardcoded value
	}
}*/

template<>
void ConfigIO::lookup(Config *cfg, std::string &val, const char* str)
{
	try {
		const Setting &tmp = cfg->lookup(str);
		const char* cstr = tmp;
		val = std::string(cstr);
	} catch (const SettingNotFoundException) {
		// setting doesn't exist, we'll fall back to the hardcoded value
	}
}

Setting & ConfigIO::addSetting(Setting &setting, const char *str, Setting::Type type)
{
	if (!setting.exists(str)) {
		return setting.add(str, type);
	}

	return setting[str];
}

void ConfigIO::write(Config *cfg, const char *file)
{
	try {
		cfg->writeFile(file);
		std::cerr << "Updated configuration file written to: " << file << std::endl;
	} catch (const FileIOException &fioex) {
		std::cerr << "I/O error while writing file: " << file << std::endl;
	}
}
