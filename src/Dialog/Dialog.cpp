#include "Dialog.hpp"
#include <Config/Globals.hpp>
#include <window.hpp>

using namespace Globals;

bool Dialog::prompt(std::string message, std::string title)
{
	size_t len = 0;

	if (message.size() > Settings::max_width) {
		len = Settings::max_width - 10;
	}

	int x = Settings::max_width/2 - len/2;
	int y = Settings::max_height/2 - 3;

	Window dialog(6, len + 5, y, x);

	if (!title.empty()) {
		dialog.setTitle(title);
	}

	dialog.refresh();
}