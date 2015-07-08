#include "MenuItemList.hpp"

MenuItemList::MenuItemList(
	const char *label, ID id, Type type,
	std::vector<std::string> list,
	std::string def):
	MenuItem(label, id, type),
	list(list),
	def(def),
	index(0)
{
	for (size_t i = 0; i < list.size(); ++i) {
		if (list[i] == def) {
			index = i;
			break;
		}
	}
}

void MenuItemList::draw(Window *window, bool cur, int w, int y, int x)
{
	std::string opt = list[index];

	window->print(label.substr(0, w - opt.size()), y, x, cur ? COLOR_GREEN : -1, -1);
	window->print(opt, y, w - opt.size(), cur ? COLOR_GREEN : -1, -1);
}

void MenuItemList::update(int key)
{
	if (key == KEY_LEFT) {
		if (index != 0) {
			--index;
		} else {
			index = list.size() - 1;
		}
	} else if (key == KEY_RIGHT) {
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