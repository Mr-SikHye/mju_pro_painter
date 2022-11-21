#pragma once
#include <Windows.h>
#include <iostream>
#include "frame.h"
#include "component.h"

class Frame;
class MButton :public Component{
public:
	MButton(std::wstring s, int x, int y, int width, int height);
	MButton(std::wstring s);
};