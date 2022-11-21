#include <Windows.h>
#include <iostream>
#include "frame.h"
#include "component.h"
#include "checkbox.h"

checkbox::checkbox(std::wstring s) {
	text_ = s;
	x_ = 0;
	y_ = 0;
	width_ = default_width;
	height_ = default_height;
}

void checkbox::onClick() {
	if (grid_status == 0) {
		grid_status = 1;
		frame->setGridstatus(1);
	}
	else if (grid_status == 1) {
		grid_status = 0;
		frame->setGridstatus(0);
	}
}

std::wstring checkbox::getwstring() {
	return text_;
}

void checkbox::chanwstring(std::wstring s) {
	text_ = s;
}