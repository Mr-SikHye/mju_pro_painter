#include "Misc.h"

MEvent::MEvent(UINT msg, WPARAM wParam, LPARAM lParam) :
	msg_(msg), wParam_(wParam), lParam_(lParam) 
{
	//  Nothing to do here.
}

bool MEvent::isLButtonDownEvent() {
	if (msg_ == WM_LBUTTONDOWN) {
		return true;
	}
	else{
		return false;
	}
}
bool MEvent::isLButtonUpEvent() {
	if (msg_ == WM_LBUTTONUP) {
		return true;
	}
	else {
		return false;
	}
}
bool MEvent::isRButtonDownEvent() {
	if (msg_ == WM_RBUTTONDOWN) {
		return true;
	}
	else {
		return false;
	}
}
bool MEvent::isRButtonUpEvent() {
	if (msg_ == WM_RBUTTONUP) {
		return true;
	}
	else {
		return false;
	}
}
bool MEvent::isCtrlKeyDown() {
	if (msg_ == MK_CONTROL) {
		return true;
	}
	else {
		return false;
	}
}
bool MEvent::isShiftKeyDown() {
	if (msg_ == MK_SHIFT) {
		return true;
	}
	else {
		return false;
	}
}
int MEvent::getX() {
	int i = LOWORD(lParam_);
	return i;
}
int MEvent::getY() {
	int i = HIWORD(lParam_);
	return i;
}


MPoint::MPoint(int x, int y): x_(x), y_(y){

}

MPoint::MPoint() : x_(0), y_(0) {

}

MPoint MEvent::getPoint() {
	MPoint temp(LOWORD(lParam_), HIWORD(lParam_));
	return temp;
}