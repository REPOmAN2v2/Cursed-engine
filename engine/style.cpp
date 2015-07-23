#include "engine/Config/Globals.hpp"
#include "engine/window.hpp"
#include "engine/style.hpp"

Style::Style(int h, int w):main(nullptr),_h(h),_w(w)
{}

using namespace Globals;

void Style::create()
{
	int y, x;

	if (_h == -1 || _h > Settings::max_height) {
		_h = Settings::max_height;
	}

	if (_w == -1 || _w > Settings::max_width) {
		_w = Settings::max_width;
	}

	y = (Settings::max_height - _h) / 2;
	x = (Settings::max_width - _w) / 2;

	destroy();
	main = new Window(_h, _w, y, x);
}

void Style::destroy()
{
	if (main) {
		delete main;
		main = nullptr;
	}
}

Style::~Style()
{
	destroy();
}
