#include "Globals.hpp"
#include <libconfig.h++>
#include <iostream>

int Globals::Settings::height = 20;
int Globals::Settings::width = 79;

using namespace libconfig;

void Globals::load()
{
	Config cfg;

	try {
		cfg.readFile("config.cfg");
	} catch (const FileIOException &fioex) {
		std::cerr << "I/O error while reading file." << std::endl;
		exit(EXIT_FAILURE);
	} catch (const ParseException &pex) {
		std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
	          << " - " << pex.getError() << std::endl;
		exit(EXIT_FAILURE);
	}

	const Setting &root = cfg.getRoot();

	if (root.exists("settings")) {
		const Setting &settings = root["settings"];
		if (settings.exists("size")) {
			const Setting &size = settings["size"];
			int h, w;
			if (size.lookupValue("height", h))
				Globals::Settings::height = h;
			if (size.lookupValue("width", w))
				Globals::Settings::width = w;
		}
	}
}