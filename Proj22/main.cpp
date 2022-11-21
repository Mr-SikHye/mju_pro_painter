
#include "frame.h"
#include <iostream>
#include <exception>

// 일단은 전역 변수 1개는 사용한다.
extern Frame* theFrame ;
int main() {
	try {
		theFrame = new Frame(L"객체1프로젝트2022", 1000,800);
		theFrame->run();
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	
}
