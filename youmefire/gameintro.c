#include "easyDefine.h"

int IntroGame() {
	Layer background = { true, 0, L"image", L"images/solid/101010.bmp", 0, 0, 100 };

	easyImage.reset(&easyImage);
	easyImage.setLayer(&easyImage, background);
	easyImage.render(&easyImage);
	PlayAudio(L"music/yurusu", true);
	Sleep(700);

	background.name = L"images/screen/intro/1.bmp";
	easyImage.setLayer(&easyImage, background);
	easyImage.render(&easyImage);
	Sleep(900);

	background.name = L"images/screen/intro/2.bmp";
	easyImage.setLayer(&easyImage, background);
	easyImage.render(&easyImage);
	Sleep(1500);

	background.name = L"images/screen/intro/3.bmp";
	easyImage.setLayer(&easyImage, background);
	easyImage.render(&easyImage);
	Sleep(900);

	background.name = L"images/screen/intro/4.bmp";
	easyImage.setLayer(&easyImage, background);
	easyImage.render(&easyImage);
	Sleep(1500);
	Sleep(1000);
	Sleep(2000);

	int volume = 1000;

	while (volume) {
		VolumeAudio(L"music/yurusu", volume);
		volume -= 10;
		Sleep(10);
	}
	StopAudio(L"music/yurusu");
}