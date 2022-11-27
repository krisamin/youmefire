#include "easyDefine.h"

int IsInPixel(int x, int y, int lenX, int lenY) {
	if (mouseX >= x && mouseX <= x + lenX && mouseY >= y && mouseY <= y + lenY) {
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
	//Sleep(1000);

	//IntroGame();

	PlayAudio(L"music/ost", true);
	int type = Index();
	if (!type)return 0;
	StopAudio(L"music/ost");

	//ViichanIntro();
}