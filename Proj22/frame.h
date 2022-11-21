#pragma once
#include "Windows.h"
#include <string>
#include <list>
#include "Misc.h"
#include "mbutton.h"
#include "checkbox.h"
#include "component.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class Frame {
protected:
	// Window 프로그래밍을 위한 기본 변수들이다. 건드리지 않는다.
	HINSTANCE hInst_;
	HWND hWnd_;	 // 윈도 핸들을 저장해둔다.
	HDC hDC_;    // 이 변수가 있어야 그림을 그릴 수 있다.

	MButton* buttons_[100];
	checkbox* boxs_[100];

	// 응용을 위해 필요한 변수
	static const int FIG_NONE = 0;
	static const int FIG_RECT = 1;
	static const int FIG_ELLI = 2;
	static const int FIG_LINE = 3;
	static const int GRID = 4;

	MPoint start_;
	MPoint end_;

	int figType_ = FIG_NONE;
	int GRID_status = 0;
	int numButtons = 0;
	int numBoxs = 0;

	RECT r[100];
	int a = 0;
	RECT E[100];
	int b = 0;
	RECT L[100];
	int c = 0;

public:
	Frame();
	Frame(std::wstring, int, int);
	virtual void run();
	virtual void eventHandler( MEvent e);
	virtual void repaint();
	virtual void invalidate();
	virtual void initialize();
	void addButton(MButton*);
	void addcheckbox(checkbox*);
	virtual void drawButtons();
	void setFigType(int t);
	void setGridstatus(int t);
	void findButton(int x,int y);
};


class PaintFrame :public Frame {
public:
	void initialize() override;
	void drawButtons() override;
};