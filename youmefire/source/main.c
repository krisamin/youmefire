#include "../headers/easyDefine.h"

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
	InitImage(30);

	/*WCHAR* setName = (WCHAR*)malloc(sizeof(WCHAR) * 3);
	setName = L"세구\0";
	name = setName;
	ReadStory(L"ENDING-V-A");*/

	//GameIntro();
	while (true) {
		int type = Index();
		if (!type) return 0;
	}
}

int main() {
	MainProcess();
	//Sleep(1000);

	//const size = lstrlenW(content);
	//WCHAR wcs[] = L"|N Hello.";
	//WCHAR wcs[size];
	//wcsncpy(wcs, content, size);
	//wcs[lstrlenW(content)] = '\0';
	//wprintf(L"%c\n", wcs[0]);
}