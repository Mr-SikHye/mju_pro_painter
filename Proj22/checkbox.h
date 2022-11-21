#pragma once
#include <Windows.h>
#include <iostream>
#include "frame.h"
#include "component.h"

class checkbox:public Component {
public:
	checkbox(std::wstring s);
	int grid_status = 0;
	void onClick() override;
	void chanwstring(std::wstring s);
	std::wstring getwstring();
};