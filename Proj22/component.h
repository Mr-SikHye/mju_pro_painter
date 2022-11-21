#pragma once
#include <Windows.h>
#include <iostream>
#include "frame.h"

class Frame;
class Component {
protected:
	std::wstring text_;
	LPCWSTR string = text_.c_str();
	int n; //wstring length
	Frame* frame;

public:
	Component();
	Component(std::wstring s, int x, int y, int width, int height);
	Component(std::wstring s);
	bool include(int x, int y);
	bool include(MPoint p);
	void setX(int x);
	int getHeigjt();
	int getWidth();
	void draw(HDC);
	virtual void onClick();
	void setFrame(Frame*);
	void setCommand(int i);
	int x_, y_, width_, height_;
	int Command;
	static const int default_height = 30;
	static const int default_width = 100;
};