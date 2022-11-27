#include "easyDefine.h"

int Intro() {

	Layer background = { true, "image", "images/solid/101010.bmp", 0, 0, 100 };
	Layer by1 = { true, "text", "Pretendard Variable", 960, 496, 100, TEXT("제작자"), 80, 700, 0, TA_CENTER, 1, RGB(255, 255, 255) };
	Layer by2 = { true, "text", "Pretendard Variable", 960, 608, 100, TEXT("박성민           조현우"), 40, 400, 0, TA_CENTER, 1, RGB(255, 255, 255) };

	easyImage.reset(&easyImage);
	easyImage.setLayer(&easyImage, 0, background);
	easyImage.render(&easyImage);
	PlayAudio(L"yurusu", true);
	Sleep(800);

	easyImage.setLayer(&easyImage, 1, by1);
	easyImage.render(&easyImage);
	Sleep(1000);

	easyImage.setLayer(&easyImage, 2, by2);
	easyImage.render(&easyImage);
	Sleep(1600);
	printf("page3\n");
	Sleep(1000);
	printf("page4\n");
	Sleep(1600);
	printf("page5\n");
	Sleep(1000);
	printf("page6\n");
	Sleep(2000);
	int volume = 1000;
	while (volume--) {
		VolumeAudio(L"yurusu", volume);
		Sleep(1);
	}
	StopAudio(L"yurusu");
}