#include "easyDefine.h"

int Intro() {
	Layer background = { true, "image", "images/solid/101010.bmp", 0, 0, 100 };

	easyImage.reset(&easyImage);
	easyImage.setLayer(&easyImage, 0, background);
	easyImage.render(&easyImage);
	PlayAudio(L"yurusu", true);
	Sleep(700);

	background.name = "images/screen/intro/1.bmp";
	easyImage.setLayer(&easyImage, 1, background);
	easyImage.render(&easyImage);
	Sleep(900);

	background.name = "images/screen/intro/2.bmp";
	easyImage.setLayer(&easyImage, 1, background);
	easyImage.render(&easyImage);
	Sleep(1500);

	background.name = "images/screen/intro/3.bmp";
	easyImage.setLayer(&easyImage, 1, background);
	easyImage.render(&easyImage);
	Sleep(900);

	background.name = "images/screen/intro/4.bmp";
	easyImage.setLayer(&easyImage, 1, background);
	easyImage.render(&easyImage);
	Sleep(1500);
	Sleep(1000);
	Sleep(2000);

	int volume = 1000;

	while (volume) {
		VolumeAudio(L"yurusu", volume);
		volume -= 10;
		Sleep(10);
	}
	StopAudio(L"yurusu");
}