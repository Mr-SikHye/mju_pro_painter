#include <Windows.h>
#include <iostream>
#include "frame.h"
#include "component.h"


Component::Component() {

}
Component::Component(std::wstring s, int x, int y, int width, int height) {
	text_ = s;
	x_ = x;
	y_ = y;
	width_ = width;
	height_ = height;
}
Component::Component(std::wstring s) {
	text_ = s;
	x_ = 0;
	y_ = 0;
	width_ = default_width;
	height_ = default_height;
}
bool Component::include(int x, int y) {
	if (x >= x_ && x < width_ && y >= y_ && y < height_) {
		return true;
	}
	else false;
}
bool Component::include(MPoint p) {
	if ((p.x_ >= x_ && p.x_ < width_) && (p.y_ >= y_ && p.y_ < height_)) {
		return true;
	}
	else false;
}
void Component::setX(int x) {
	x_ = x;
	width_ += x;
}
int Component::getHeigjt() {
	return height_;
}
int Component::getWidth() {
	return width_;
}
void Component::draw(HDC hdc) {
	Rectangle(hdc, x_, y_, width_, height_);
	n = text_.length();
	TextOut(hdc, x_ + 10, y_ + 10, string, n);
}
void Component::onClick() {
	frame->setFigType(this->Command);
}
void Component::setCommand(int i) {
	Command = i;
}
void Component::setFrame(Frame* f) {
	frame = f;
}