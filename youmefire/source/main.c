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
	InitImage(50);
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

	WCHAR* setName = (WCHAR*)malloc(sizeof(WCHAR) * 3);
	setName = L"세구\0";
	name = setName;
	ReadStory(L"CRISIS-V-B");

	GameIntro();

	PlayAudio(L"bgm/ost", true);
	int type = Index();
	if (!type)return 0;
	StopAudio(L"bgm/ost");
}