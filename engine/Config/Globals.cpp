#include "engine/Config/Globals.hpp" // for Globals namepace
#include "engine/Config/config.hpp" // for ConfigIO, Setting, Config classes

// TODO: once proper color support is added, add it to config file
// TODO: add title as well with special function to tokenize on \n and save it ?

int Globals::Settings::height = 20;
int Globals::Settings::max_height = 20;
int Globals::Settings::width = 79;
int Globals::Settings::max_width = 79;
int Globals::Colours::highlight = -1;
int Globals::Colours::title = -1;
int Globals::Colours::normal = -1;
std::vector<std::string> Globals::Title::title = {"     _/_/_/  _/    _/  _/_/_/      _/_/_/  _/_/_/_/  _/_/_/ ",
												  "  _/        _/    _/  _/    _/  _/        _/        _/    _/",
												  " _/        _/    _/  _/_/_/      _/_/    _/_/_/    _/    _/ ",
												  "_/        _/    _/  _/    _/        _/  _/        _/    _/  ",
	 											  "_/_/_/    _/_/    _/    _/  _/_/_/    _/_/_/_/  _/_/_/      " };
int Globals::Title::length = 60;
int Globals::Title::height = 6;

static const char *file = "menu.cfg";
static ConfigIO IO;

void Globals::load()
{
	Config *cfg = IO.open(file);
	if (!cfg) return;

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

static void writeSettingsMenu(Config *cfg)
{
	Setting &root = cfg->getRoot();
	Setting &settings = IO.addSetting(root, "settings", Setting::TypeGroup);
	Setting &size = IO.addSetting(settings, "size", Setting::TypeGroup);
	Setting &height = IO.addSetting(size, "height", Setting::TypeInt);
	Setting &width = IO.addSetting(size, "width", Setting::TypeInt);

	height = Globals::Settings::height;
	width = Globals::Settings::width;
}

void Globals::save()
{
	Config *cfg = IO.open(file);
	if (!cfg) return;
	writeSettingsMenu(cfg);

	IO.write(cfg, file);

	delete cfg;
}
