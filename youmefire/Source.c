#define _CRT_SECURE_NO_WARNINGS false

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "easyDefine.h"
#include "easyDisplay.h"
#include "easyImage.h"
#include "easyAudio.h"
#include "easyMouse.h"

void init() {
	SetConsoleTitle(TEXT("Initialize"));
	printf("Initialize\n");
	HideCursor();
	printf("Hide Cursor\n");
	HideScrollBar();
	printf("Hide ScrollBar\n");
	SetProcessDPIAware();
	printf("Set DPI\n");
	SetConsole(WINDOW_WIDTH, WINDOW_HEIGHT);
	printf("Set Console\n");
	StartMouseInputThread();
	printf("Start Mouse Thread\n");

	printf("Open Sounds\n");
	OpenAudio(L"sounds/music/ost.mp3", L"ost");
	OpenAudio(L"sounds/music/yurusu.mp3", L"yurusu");
	OpenAudio(L"sounds/effect/button.mp3", L"button");

	SetConsoleTitle(TEXT(":: 누나 동생 청춘 ::"));
}

int IsInPixel(int x, int y, int lenX, int lenY) {
	if (mouseX >= x & mouseX <= x + lenX & mouseY >= y & mouseY <= y + lenY) {
		return 1;
	} else {
		return 0;
	}
}

int Index(EasyImage easyImage) {
	int currentPage = 1;
	int currentMenu = 0;

	while (true) {
		if (currentPage == 1) {
			if (IsInPixel(825, 765, 270, 50)) {
				currentMenu = 1;
				if (mouseC & mouseS) {
					PlayAudio(L"button", false);
					mouseS = false;
					return 1;
				}
			} else if (IsInPixel(825, 850, 270, 50)) {
				currentMenu = 2;
				if (mouseC & mouseS) {
					PlayAudio(L"button", false);
					mouseS = false;
					currentPage = 2;
					currentMenu = 0;
				}
			} else {
				currentMenu = 0;
			}
		} else if (currentPage == 2) {
			if (IsInPixel(842, 732, 120, 50)) {
				currentMenu = 1;
				if (mouseC & mouseS) {
					PlayAudio(L"button", false);
					mouseS = false;
					currentPage = 1;
					currentMenu = 0;
				}
			} else if (IsInPixel(1026, 732, 50, 50)) {
				currentMenu = 2;
				if (mouseC & mouseS) {
					PlayAudio(L"button", false);
					mouseS = false;
					return 0;
				}
			} else {
				currentMenu = 0;
			}
		}

		char imgPath[20];
		sprintf(imgPath, "images/index/%d%d.bmp", currentPage, currentMenu);

		TCHAR mousePosition[100];
		wsprintf(mousePosition, TEXT("X: %-4d, Y: %-4d, C: %-2d, S: %-2d"), mouseX, mouseY, mouseC, mouseS);

		easyImage.count = 2;
		Layer layer[2] = {
			{
				"image",
				imgPath, 0, 0, 100
			}, {
				"text",
				"D2Coding", 0, 0, 100, mousePosition, 50, 900, 0, TA_LEFT, 0, RGB(0, 0, 0)
			}
		};
		easyImage.layer = layer;
		easyImage.render(&easyImage);
	}
}

int intro(EasyImage easyImage) {
	Sleep(800);
	printf("page1\n");
	Sleep(1000);
	printf("page2\n");
	Sleep(1600);
	printf("page3\n");
	Sleep(1000);
	printf("page4\n");
	Sleep(1600);
	printf("page5\n");
	Sleep(1000);
	printf("page6\n");
	Sleep(2000);
}

int main() {
	init();
	EasyImage easyImage = DEFAULT_EASY_IMAGE;
	easyImage.initialize(&easyImage);

	easyImage.count = 1;
	Layer background[1] = {
		{
			"image",
			"images/solid/101010.bmp", 0, 0, 100
		}
	};
	easyImage.layer = background;
	easyImage.render(&easyImage);

	/*PlayAudio(L"yurusu", true);
	intro(easyImage);
	int volume = 1000;
	while (volume --) {
		VolumeAudio(L"yurusu", volume);
		Sleep(1);
	}
	StopAudio(L"yurusu");*/

	PlayAudio(L"ost", true);
	int type = Index(easyImage);
	if (!type) {
		return 0;
	}
	StopAudio(L"ost");

	easyImage.count = 3;
	Layer layer[3] = {
		{
			"image",
			"images/jingburger.bmp", 0, 0, 100
		}, {
			"image",
			"images/dialog/jingburger.bmp", 0, 0, 80
		}, {
			"text",
			"Pretendard Variable", 110, 760, 100, TEXT("안녕하세요. 이것은 테스트를 위한 글입니다."), 40, 700, 0, TA_LEFT, 0, RGB(0, 0, 0)
		}
	};
	easyImage.layer = layer;
	easyImage.render(&easyImage);

	PlayAudio(L"yurusu", true);
	VolumeAudio(L"yurusu", 1000);

	Sleep(100000);
}