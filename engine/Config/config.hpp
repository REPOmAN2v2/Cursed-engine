#pragma once

#include <libconfig.h++>
#include <string>

using namespace libconfig;

class ConfigIO 
{
public:
	Config * open(const char *file);
	Config * open(const std::string &file);
	void write(Config *config, const char *file);
	void write(Config *config, const std::string &file);
	Setting & addSetting(Setting &setting, const char *str, Setting::Type type);
	template<typename T>
	void lookup(Config *cfg, T &val, const char* str)
	{
		try {
			const Setting &tmp = cfg->lookup(str);
			val = tmp;
		} catch (const SettingNotFoundException) {
			// setting doesn't exist, we'll fall back to the hardcoded value
		}
	}
private:
};

template<>
void ConfigIO::lookup(Config *cfg, std::string &val, const char *str);
