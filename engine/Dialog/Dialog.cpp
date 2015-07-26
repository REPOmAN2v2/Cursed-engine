#include <algorithm> // for std::move
#include <sstream> // for std::stringstream
#include <vector>

#include "engine/Config/Globals.hpp"
#include "engine/ncurses.hpp" //Ncurses::getkey()
#include "engine/window.hpp"
#include "engine/Dialog/Dialog.hpp"

static std::vector<std::string> split(const std::string &message)
{
	std::vector<std::string> strings;
	std::string it;
	std::stringstream ss(message);

	while (std::getline(ss, it, '\n')) {
		strings.push_back(std::move(it));
	}

	return strings;
}

static bool update(Window &dialog)
{
	bool current = true; // i.e. "Yes"
	int h = dialog.getH();
	int x = dialog.getW()/2 - 9/2; 

	do {
		dialog.print(std::string("Yes"), h - 2, x, current ? 
			Globals::text["highlight"] : Globals::text["normal"]);
		dialog.print(std::string(" | "), h - 2, x + 3, Globals::text["normal"]);
		dialog.print(std::string("No"), h - 2, x + 6, current ? 
			Globals::text["normal"] : Globals::text["highlight"]);

		dialog.refresh();
		refresh();

		int key = Ncurses::getKey(-1);
		if (key == KEY_LEFT || key == KEY_RIGHT) {
			current = !current;
		} else if (key == '\n') {
			return current;
		}
	} while (true);
}

static bool create(std::string message, std::string title, bool yesno)
{
	auto lines = split(message);

	int h = lines.size();
	int w = 0;

	for (const auto &it : lines) {
		w = w > it.size() ? w : it.size();
	}

	// TODO: check for w > Settings::max_width and trim lines if necessary
	// TODO: add scrolling if h > Settings::max_height

	int x = Globals::Settings::max_width/2 - w/2;
	int y = Globals::Settings::max_height/2 - h/2;
	h += yesno ? 4 : 2; // borders + Yes/No : borders
	w += 2; // borders

	Window dialog(h, w, y, x);

	if (!title.empty()) {
		dialog.setTitle(title);
	}

	dialog.print(lines, 1, 1, Globals::text["normal"]);

	if (yesno) {
		return update(dialog);
	}

	dialog.refresh();
	refresh();
	Ncurses::getKey(-1);
	return false;
}

bool Dialog::prompt(std::string message, std::string title)
{
	return create(message, title, true);
}

void Dialog::message(std::string message, std::string title)
{
	create(message, title, false);
}
