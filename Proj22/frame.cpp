#include "frame.h"
#include "Misc.h"
#include "mbutton.h"
#include "component.h"
#include "checkbox.h"
#include <iostream>
#include <string>


// ��¿ �� ���� ���� ���� 1���� ����Ѵ�.
Frame* theFrame = nullptr;
PaintFrame* PFrame = nullptr;
int posx;
int posy;
// �����Լ��δ� ���� �޽��� ó�� �Լ��� �ִ�.
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

		// �׸��� �ڵ�� �̰ɷ� ��!
		if (theFrame != nullptr)
			theFrame->repaint();
		
		
		EndPaint(Hw, &ps);  // BeginPaint�� ¦�� �ȴ�
		
	}
	default: return DefWindowProc(Hw, Msg, wParam, lParam);
	}
}

Frame::Frame() :Frame(L"", 800, 600) {
	// ���� ������ �ʰ� ����.
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
		WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | // ���� �ּ�ȭ �ִ�ȭ ������
		WS_THICKFRAME,  // resize�� �����ϰ�
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


// run �Լ��� �����ϸ� ������.
void Frame::run() {
	HACCEL hAccelTable = LoadAccelerators(hInst_, MAKEINTRESOURCE(IDI_APPLICATION));

	MSG msg;

	// �⺻ �޽��� �����Դϴ�:
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

	// TODO: ���⿡ ���� �ڵ� �߰�.
	OutputDebugString(L"Event\n");
	std::cout << L"Event\n" << std::endl;  // ����� cmd â���� ���

	// �̺�Ʈ�� ������ �ľ��ؼ� �簢�� �׸��⸦ ���⼭ ���ش�.
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
	// �׷����� ��� ���� ���⿡. �Ʒ� �� ���� �����̴� �������Ѵ�.
	drawButtons();

	for (int i = 0; i < 100; i++) {
		Rectangle(hDC_, r[i].left, r[i].top, r[i].right, r[i].bottom);
		Ellipse(hDC_, E[i].left, E[i].top, E[i].right, E[i].bottom);
		MoveToEx(hDC_, L[i].left, L[i].top, NULL);
		LineTo(hDC_, L[i].right, L[i].bottom);
	}
}

void Frame::invalidate() {
	// �� �޼ҵ带 �θ��� ȭ���� �ٽ� �׸��� �ȴ�.

	InvalidateRect(hWnd_, nullptr, true);

}

void Frame::initialize() {
	MButton* b1 = new MButton(L"�簢��");
	MButton* b2 = new MButton(L"Ÿ��");
	MButton* b3 = new MButton(L"����");
	checkbox* box1 = new checkbox(L"[ ]�׸���");
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
		if (temp == L"[ ]�׸���") {
			boxs_[0]->chanwstring(L"[v]�׸���");
			boxs_[0]->draw(hDC_);
		}
		else {
			boxs_[0]->chanwstring(L"[ ]�׸���");
			boxs_[0]->draw(hDC_);
		}
		boxs_[0]->onClick();
	}
}

void Frame::setGridstatus(int t) {
	GRID_status = t;
}

//paint frame

