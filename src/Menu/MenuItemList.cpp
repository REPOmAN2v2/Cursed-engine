#include "MenuItemList.hpp"

MenuItemList::MenuItemList(MenuItemTemplate &tem):
	MenuItem(tem),
	list(tem.list),
	def(tem.def),
	current(0)
{
	for (size_t i = 0; i < list.size(); ++i) {
		if (list[i] == def) {
			current = i;
			break;
		}
	}
}

void MenuItemList::draw(Window *window, bool cur, int w, int y, int x)
{
	std::string opt = list[current];

	window->print(label.substr(0, w - opt.size()), y, x, cur ? COLOR_GREEN : -1, -1);
	window->print(opt, y, w - opt.size(), cur ? COLOR_GREEN : -1, -1);
}

void MenuItemList::update(int key)
{
	if (key == KEY_LEFT) {
		if (current != 0) {
			--current;
		} else {
			current = list.size() - 1;
		}
	} else if (key == KEY_RIGHT) {
		if ((current + 1) < list.size()){ 
			++current;
		} else {
			current = 0;
		}
	}
}