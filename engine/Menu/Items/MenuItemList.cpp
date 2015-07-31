#include <utility>

#include "engine/Config/Globals.hpp"
#include "engine/Keys.hpp"
#include "engine/Menu/Items/MenuItemList.hpp"
#include "engine/window.hpp"

MenuItemList::MenuItemList(
	const char *label, unsigned id, MenuItem::Type type,
	std::vector<std::string> list,
	std::string def):
	MenuItem(label, id, type),
	list(std::move(list)),
	def(std::move(def)),
	index(0)
{
	reset();
}

using namespace Globals;

void MenuItemList::draw(Window *window, bool cur, int w, int y, int x)
{
	std::string opt = list[index];

	window->print(label.substr(0, w - opt.size()), y, x, cur ? Globals::text["highlight"] : Globals::text["normal"]);
	window->print(opt, y, w - opt.size(), cur ? Globals::text["highlight"] : Globals::text["normal"]);
}

void MenuItemList::update(Key key)
{
	if (key.val == Key::LEFT) {
		if (index != 0) {
			--index;
		} else {
			index = list.size() - 1;
		}
	} else if (key.val == Key::RIGHT) {
		if ((index + 1) < list.size()){ 
			++index;
		} else {
			index = 0;
		}
	}
}

std::string MenuItemList::getValue()
{
	return list[index];
}

void MenuItemList::reset()
{
	for (size_t i = 0; i < list.size(); ++i) {
		if (list[i] == def) {
			index = i;
			break;
		}
	}
}
