#include <algorithm>

#include "engine/Keys.hpp"
#include "engine/ncurses.hpp"
#include "engine/Config/Globals.hpp"
#include "engine/Menu/MenuData.hpp"
#include "engine/window.hpp"
#include "engine/Menu/Items/MenuItem.hpp"
#include "engine/Menu/Items/MenuItemList.hpp"
#include "engine/Menu/Items/MenuItemNumber.hpp"
#include "engine/Menu/Items/MenuItemToggle.hpp"

MenuData::MenuData(int h, int w, int y, int x):
	_h(h),
	_w(w),
	_y(y),
	_x(x),
	current(nullptr),
	selected(nullptr),
	index(0)
{}

MenuData::~MenuData()
{
	clear();
}

void MenuData::clear()
{
	for (auto & elem : items) {
		delete elem;
		elem = nullptr;
	}

	items.clear();
}

void MenuData::addItem(MenuItem *item)
{
	items.push_back(item);

	if (items.size() == 1) {
		current = items.back();
	}

	for (size_t i = 0; i < items.size(); ++i) {
		if (items[i]) {
			current = items[i];
			index = i;
			break;
		}
	}
}

MenuItem * MenuData::findItem(unsigned id)
{
	auto it = std::find_if( items.begin(), items.end(), [&](MenuItem * it) -> bool {
							return it && it->id == id;});

	if (it == items.end()) {
		return nullptr;
	}

	return (*it);
}

void MenuData::removeItem(unsigned id)
{
	items.erase(
		std::remove_if(
			items.begin(),
			items.end(),
			[&](MenuItem* it) -> bool {
            	if (it && it->id == id) {
            		if (it == current) {
            			nextItem();
            			--index;
            		}
            		return true;
            	} 
				return false;
			}
			),
		items.end()
		);
}

void MenuData::nextItem()
{
	if (items.size() == 0) {
		return;
	} else if (items.size() == 1) {
		current = items.back();
		index = 0;
		return;
	} else if (current == items.back() && index == (items.size() - 1)) {
		firstItem();
		return;
	}

	++index;
	current = items[index];

	if (!current) {
		nextItem();
	}
}

void MenuData::prevItem()
{
	if (items.size() == 0) {
		return;
	} else if (items.size() == 1) {
		current = items.front();
		index = 0;
		return;
	} else if (current == items.front() && index == 0) {
		lastItem();
		return;
	}

	--index;
	current = items[index];

	if (!current) {
		prevItem();
	}
}

void MenuData::firstItem()
{
	if (items.size() == 0) {
		return;
	} else if (items.size() == 1) {
		current = items.front();
		index = 0;
		return;
	}

	current = items.front();
	index = 0;

	if (!current) {
		nextItem();
	}
}

void MenuData::lastItem()
{
	if (items.size() == 0) {
		return;
	} else if (items.size() == 1) {
		current = items.front();
		index = 0;
		return;
	}

	current = items.back();
	index = items.size() - 1;

	if (!current) {
		prevItem();
	}
}

void MenuData::draw(Window *window)
{
	size_t begin = 0;
	size_t end = items.size();

	if (_h < items.size()) {
		if (index <= _h/2) {
			end = _h - 1;
		} else if (index < (items.size() - _h/2) - 1) {
			begin = index - _h/2;
			end = index + _h/2;
		} else {
			begin = items.size() - _h;
		}
	}

	for (size_t i = begin, dy = 0; i < end; ++i, ++dy) {
		if ((i == begin) && (i != 0)) {
			window->print("(more)",
						  _y + dy,
						  _x + _w/2 - 3,
						  Globals::text["normal"]); // center the text
			continue;
		} else if ((i == end - 1) && (i != items.size() - 1)) {
			window->print("(more)",
						  _y + dy,
						  _x + _w/2 - 3,
						  Globals::text["normal"]);
			continue;
		} else if (!items[i]) {
			std::string line;
			line.append(_w - _x, '-');
			window->print(line,
						  _y + dy,
						  _x,
						  Globals::text["normal"]);
		} else {
			items[i]->draw(window, (items[i] == current), _w, _y + dy, _x);
		}
	}
}

void MenuData::update()
{
	Key key = Ncurses::getKey(-1);
	selected = nullptr;

	switch (key.val) {
		case Key::DOWN:
			nextItem();
		break;

		case Key::UP:
			prevItem();
		break;

		case Key::PPAGE:
			firstItem();
		break;

		case Key::NPAGE:
			lastItem();
		break;

		case Key::UNKNOWN:
		break;

		case Key::ENTER:
			selected = current; 
			// fallthrough
		default:
			if (current) {
				current->update(key);
			}
		break;
	}
}

unsigned MenuData::whichSelected()
{
	return selected ? selected->id : 0;
}

/* 	Ideally we could just call MenuItem::getValue() directly
	Sadly virtual templates or virtual auto returns aren't a thing
	neither are overloaded return types. */

template<>
int MenuData::get(unsigned id)
{
	MenuItem *tmp = findItem(id);
	if (!tmp) return 0;

	MenuItemNumber *item = dynamic_cast<MenuItemNumber*>(tmp);

	return item->getValue();
}

template<>
std::string MenuData::get(unsigned id)
{
	MenuItem *tmp = findItem(id);
	if (!tmp) return std::string();

	MenuItemList *item = dynamic_cast<MenuItemList*>(tmp);

	return item->getValue();
}

template<>
bool MenuData::get(unsigned id)
{
	MenuItem *tmp = findItem(id);
	if (!tmp) return false;

	MenuItemToggle *item = dynamic_cast<MenuItemToggle*>(tmp);

	return item->getValue();
}
