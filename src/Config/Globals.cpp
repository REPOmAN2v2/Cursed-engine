#include "Globals.hpp"
#include <libconfig.h++>
#include <iostream>

int Globals::Settings::height = 20;
int Globals::Settings::max_height = 20;
int Globals::Settings::width = 79;
int Globals::Settings::max_width = 79;
int Globals::Colours::highlight = -1;
int Globals::Colours::title = -1;
int Globals::Colours::normal = -1;

static const char *config = "config.cfg";

using namespace libconfig;

static Config * open(const char *file)
{
	auto   cfg = new Config();

	try {
		cfg->readFile(file);
	} catch (const FileIOException &fioex) {
		std::cerr << "I/O error while reading file." << std::endl;
		exit(EXIT_FAILURE);
	} catch (const ParseException &pex) {
		std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
	          << " - " << pex.getError() << std::endl;
		exit(EXIT_FAILURE);
	}

	return cfg;
}

void Globals::load()
{
	Config *cfg = open(config);

	try {
		const Setting &tmp = cfg->lookup("settings.size.height");
		Globals::Settings::height = tmp;
	} catch (const SettingNotFoundException) {
		// setting doesn't exist, we'll fall back to the hardcoded value
	}

	try {
		const Setting &tmp = cfg->lookup("settings.size.width");
		Globals::Settings::width = tmp;
	} catch (const SettingNotFoundException) {
	}

	delete cfg;
}

static Setting & addSetting(Setting &setting, const char *str, Setting::Type type)
{
	if (!setting.exists(str)) {
		return setting.add(str, type);
	}

	return setting[str];
}

static void writeSettingsMenu(Config *cfg)
{
	Setting &root = cfg->getRoot();
	Setting &settings = addSetting(root, "settings", Setting::TypeGroup);
	Setting &size = addSetting(settings, "size", Setting::TypeGroup);
	Setting &height = addSetting(size, "height", Setting::TypeInt);
	Setting &width = addSetting(size, "width", Setting::TypeInt);

	height = Globals::Settings::height;
	width = Globals::Settings::width;
}

void Globals::save()
{
	Config *cfg = open(config);
	writeSettingsMenu(cfg);

	try {
		cfg->writeFile(config);
		std::cerr << "Updated configuration file written to: " << config << std::endl;
	} catch (const FileIOException &fioex) {
		std::cerr << "I/O error while writing file: " << config << std::endl;
	}

	delete cfg;
}
