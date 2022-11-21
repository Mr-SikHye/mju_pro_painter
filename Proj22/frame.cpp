#include "frame.h"
#include "Misc.h"
#include "mbutton.h"
#include "component.h"
#include "checkbox.h"
#include <iostream>
#include <string>


// 어쩔 수 없이 전역 변수 1개는 사용한다.
Frame* theFrame = nullptr;
PaintFrame* PFrame = nullptr;
int posx;
int posy;
// 전역함수로는 윈도 메시지 처리 함수가 있다.
LRESULT CALLBACK WndProc(HWND Hw, UINT Msg, WPARAM wParam, LPARAM lParam)
{

	switch (Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
	case WM_LBUTTONDOWN:
		posx = LOWORD(lParam);
		posy = HIWORD(lParam);
		theFrame->findButton(posx, posy);
	case WM_LBUTTONDBLCLK:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONDBLCLK:
	case WM_RBUTTONUP:
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_CHAR:
	case WM_SIZE:
		if (theFrame != nullptr)
			theFrame->eventHandler(MEvent(Msg, wParam, lParam));
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(Hw, &ps);

		// 그리기 코드는 이걸로 끝!
		if (theFrame != nullptr)
			theFrame->repaint();
		
		
		EndPaint(Hw, &ps);  // BeginPaint의 짝이 된다
		
	}
	default: return DefWindowProc(Hw, Msg, wParam, lParam);
	}
}

Frame::Frame() :Frame(L"", 800, 600) {
	// 현재 사용되지 않고 있음.
}

Frame::Frame(std::wstring title, int width, int height) {
	hInst_ = GetModuleHandle(NULL);
	FreeConsole(); // No console
	// Register win class
	WNDCLASSEX Wc;

	Wc.cbSize = sizeof(WNDCLASSEX);
	Wc.style = CS_HREDRAW | CS_VREDRAW;
	Wc.lpfnWndProc = WndProc;
	Wc.cbClsExtra = 0;
	Wc.cbWndExtra = 0;
	Wc.hInstance = hInst_;
	Wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	Wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	Wc.lpszMenuName = NULL;
	Wc.lpszClassName = L"MyWin";
	Wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&Wc);

	hWnd_ = CreateWindowExW(WS_EX_TOPMOST, L"MyWIn", (WCHAR*)title.c_str(),
		WS_OVERLAPPED |
		WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | // 종료 최소화 최대화 아이콘
		WS_THICKFRAME,  // resize가 가능하게
		0, 0, width, height, // x, y, width, height
		NULL, NULL, hInst_, NULL);  // Parent, Menu, instance handle, lpParam
	if (!hWnd_) throw 0;

	ShowWindow(hWnd_, SW_SHOW);
	UpdateWindow(hWnd_); 
	SetFocus(hWnd_);
	hDC_ = GetDC(hWnd_);
	invalidate();
	initialize();
}


// run 함수는 수정하면 위험함.
void Frame::run() {
	HACCEL hAccelTable = LoadAccelerators(hInst_, MAKEINTRESOURCE(IDI_APPLICATION));

	MSG msg;

	// 기본 메시지 루프입니다:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

void Frame::eventHandler(MEvent e)
{

	// TODO: 여기에 구현 코드 추가.
	OutputDebugString(L"Event\n");
	std::cout << L"Event\n" << std::endl;  // 여기는 cmd 창으로 출력

	// 이벤트의 종류를 파악해서 사각형 그리기를 여기서 해준다.
	if (figType_ == 1 && GRID_status == 0) {
		if (e.isLButtonDownEvent()) {
			start_ = e.getPoint();
			OutputDebugString(L"Down\n");
		}
		else if (e.isLButtonUpEvent()) {
			end_ = e.getPoint();
			Rectangle(hDC_, start_.x_, start_.y_, end_.x_, end_.y_);
			r[a++] = { start_.x_, start_.y_, end_.x_, end_.y_ };
		}
	}
	if (figType_ == 1 && GRID_status==1) {
		if (e.isLButtonDownEvent()) {
			start_ = e.getPoint();
			OutputDebugString(L"Down\n");
		}
		else if (e.isLButtonUpEvent()) {
			end_ = e.getPoint();
			Rectangle(hDC_, (start_.x_ + 10) / 20 * 20, (start_.y_ + 10) / 20 * 20, (end_.x_ + 10) / 20 * 20, (end_.y_ + 10) / 20 * 20);
			r[a++] = { (start_.x_ + 10) / 20 * 20, (start_.y_ + 10) / 20 * 20, (end_.x_ + 10) / 20 * 20, (end_.y_ + 10) / 20 * 20 };
		}
	}
	if (figType_ == 2 && GRID_status == 0) {
		if (e.isLButtonDownEvent()) {
			start_ = e.getPoint();
			OutputDebugString(L"Down\n");
		}
		else if (e.isLButtonUpEvent()) {
			end_ = e.getPoint();
			Ellipse(hDC_, (start_.x_ + 10) / 20 * 20, (start_.y_ + 10) / 20 * 20, (end_.x_ + 10) / 20 * 20, (end_.y_ + 10) / 20 * 20);
			E[b++] = { (start_.x_ + 10) / 20 * 20, (start_.y_ + 10) / 20 * 20, (end_.x_ + 10) / 20 * 20, (end_.y_ + 10) / 20 * 20 };
		}
	}
	if (figType_ == 2 && GRID_status == 1) {
		if (e.isLButtonDownEvent()) {
			start_ = e.getPoint();
			OutputDebugString(L"Down\n");
		}
		else if (e.isLButtonUpEvent()) {
			end_ = e.getPoint();
			Ellipse(hDC_, (start_.x_ + 10) / 20 * 20, (start_.y_ + 10) / 20 * 20, (end_.x_ + 10) / 20 * 20, (end_.y_ + 10) / 20 * 20);
			E[b++] = { (start_.x_ + 10) / 20 * 20, (start_.y_ + 10) / 20 * 20, (end_.x_ + 10) / 20 * 20, (end_.y_ + 10) / 20 * 20 };
		}
	}
	if (figType_ == 3 && GRID_status == 0) {
		if (e.isLButtonDownEvent()) {
			start_ = e.getPoint();
			OutputDebugString(L"Down\n");
		}
		else if (e.isLButtonUpEvent()) {
			end_ = e.getPoint();
			MoveToEx(hDC_, start_.x_, start_.y_, NULL);
			LineTo(hDC_, end_.x_, end_.y_);
			L[c++] = { (start_.x_ + 10) / 20 * 20, (start_.y_ + 10) / 20 * 20, (end_.x_ + 10) / 20 * 20, (end_.y_ + 10) / 20 * 20 };
		}
	}
	if (figType_ == 3 && GRID_status == 1) {
		if (e.isLButtonDownEvent()) {
			start_ = e.getPoint();
			OutputDebugString(L"Down\n");
		}
		else if (e.isLButtonUpEvent()) {
			end_ = e.getPoint();
			MoveToEx(hDC_, (start_.x_ + 10) / 20 * 20, (start_.y_ + 10) / 20 * 20, NULL);
			LineTo(hDC_, (end_.x_ + 10) / 20 * 20, (end_.y_ + 10) / 20 * 20);
			L[c++] = { (start_.x_ + 10) / 20 * 20, (start_.y_ + 10) / 20 * 20, (end_.x_ + 10) / 20 * 20, (end_.y_ + 10) / 20 * 20 };
		}
	}
}

void Frame::repaint() {
	// 그려야할 모든 것은 여기에. 아래 두 줄은 샘플이니 지워야한다.
	drawButtons();

	for (int i = 0; i < 100; i++) {
		Rectangle(hDC_, r[i].left, r[i].top, r[i].right, r[i].bottom);
		Ellipse(hDC_, E[i].left, E[i].top, E[i].right, E[i].bottom);
		MoveToEx(hDC_, L[i].left, L[i].top, NULL);
		LineTo(hDC_, L[i].right, L[i].bottom);
	}
}

void Frame::invalidate() {
	// 이 메소드를 부르면 화면을 다시 그리게 된다.

	InvalidateRect(hWnd_, nullptr, true);

}

void Frame::initialize() {
	MButton* b1 = new MButton(L"사각형");
	MButton* b2 = new MButton(L"타원");
	MButton* b3 = new MButton(L"선분");
	checkbox* box1 = new checkbox(L"[ ]그리드");
	b1->setCommand(FIG_RECT);
	b2->setCommand(FIG_ELLI);
	b3->setCommand(FIG_LINE);
	box1->setCommand(GRID);
	b2->setX(100);
	b3->setX(200);
	box1->setX(300);

	addButton(b1);
	addButton(b2);
	addButton(b3);
	addcheckbox(box1);

}

void Frame::addButton(MButton* m) {
	buttons_[numButtons] = m;
	numButtons = numButtons + 1;
}

void Frame::addcheckbox(checkbox* c) {
	boxs_[numBoxs] = c;
	numBoxs++;
}

void Frame::drawButtons() {
	int i = 0;
	for (i = 0; i<numButtons; i++) {
		buttons_[i]->draw(hDC_);
	}
	for (i = 0; i < numBoxs; i++) {
		boxs_[i]->draw(hDC_);
	}
}

void Frame::setFigType(int t) {
	figType_ = t;
}

void Frame::findButton(int x,int y) {
	int i = 0;
	for (i = 0; i < numButtons; i++) {
		buttons_[i]->setFrame(theFrame);
	}
	boxs_[0]->setFrame(theFrame);
	if (buttons_[0]->include(x, y) == true) {
		buttons_[0]->onClick();
	}
	else if (buttons_[1]->include(x, y) == true) {
		buttons_[1]->onClick();
	}
	else if (buttons_[2]->include(x, y) == true) {
		buttons_[2]->onClick();
	}
	else if (boxs_[0]->include(x, y) == true) {
		std::wstring temp = boxs_[0]->getwstring();
		if (temp == L"[ ]그리드") {
			boxs_[0]->chanwstring(L"[v]그리드");
			boxs_[0]->draw(hDC_);
		}
		else {
			boxs_[0]->chanwstring(L"[ ]그리드");
			boxs_[0]->draw(hDC_);
		}
		boxs_[0]->onClick();
	}
}

void Frame::setGridstatus(int t) {
	GRID_status = t;
}

//paint frame

