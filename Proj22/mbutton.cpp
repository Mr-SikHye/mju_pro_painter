#include <Windows.h>
#include <iostream>
#include "frame.h"
#include "mbutton.h"

MButton::MButton(std::wstring s, int x, int y, int width, int height) {
	text_ = s;
	x_ = x;
	y_ = y;
	width_ = width;
	height_ = height;
}
MButton::MButton(std::wstring s) {
	text_ = s;
	x_ = 0;
	y_ = 0;
	width_ = default_width;
	height_ = default_height;
}