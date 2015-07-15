#pragma once

#include "../window.hpp"
#include "Items/MenuItemNumber.hpp"
#include "Items/MenuItemList.hpp"
#include "Items/MenuItemToggle.hpp"
#include "Items/MenuItem.hpp"
#include <vector>

class MenuData
{
public:
	MenuData(int h, int w, int y, int x);
	~MenuData();
	void clear();
	void addItem(MenuItem *item);
	void removeItem(ID id);
	void draw(Window *window);
	void nextItem();
	void prevItem();
	void firstItem();
	void lastItem();
	void update();
	ID whichSelected();
	template<typename T>
	T get(ID) {
		return nullptr;
	};
private:
	MenuItem * findItem(ID id);
	int _h, _w, _y, _x;
	std::vector<MenuItem*> items;
	MenuItem *current, *selected;
	size_t index;
};

template<>
int MenuData::get(ID id);