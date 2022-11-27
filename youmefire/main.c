#include "easyDefine.h"

int IsInPixel(int x, int y, int lenX, int lenY) {
	if (mouseX >= x & mouseX <= x + lenX & mouseY >= y & mouseY <= y + lenY) {
		return 1;
	} else {
		return 0;
	}
}

int MainProcess() {
	initialize();
	InitAudio();
	InitMouse();
	InitImage(50);
}

int main() {
	MainProcess();
	Sleep(1000);

	//Intro();

	PlayAudio(L"ost", true);
	int type = Index();
	if (!type)return 0;
	StopAudio(L"ost");

	Layer background = { true, "image", "images/jingburger.bmp", 0, 0, 100 };
	Layer jingburgerDialog = { true, "image", "images/dialog/jingburger.bmp", 0, 0, 80 };
	Layer hoverText = { true, "text", "Pretendard Variable", 110, 760, 100, TEXT("안녕하세요. 이것은 테스트를 위한 글입니다."), 40, 700, 0, TA_LEFT, 0, RGB(0, 0, 0) };

	easyImage.reset(&easyImage);
	easyImage.setLayer(&easyImage, 0, background);
	easyImage.setLayer(&easyImage, 1, jingburgerDialog);
	easyImage.setLayer(&easyImage, 2, hoverText);
	easyImage.render(&easyImage);

	PlayAudio(L"yurusu", true);
	VolumeAudio(L"yurusu", 1000);

	Sleep(100000);
}