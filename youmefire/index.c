#include "easyDefine.h"

int Index() {
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
			}
			else if (IsInPixel(825, 850, 270, 50)) {
				currentMenu = 2;
				if (mouseC & mouseS) {
					PlayAudio(L"button", false);
					mouseS = false;
					currentPage = 2;
					currentMenu = 0;
				}
			}
			else {
				currentMenu = 0;
			}
		}
		else if (currentPage == 2) {
			if (IsInPixel(842, 732, 120, 50)) {
				currentMenu = 1;
				if (mouseC & mouseS) {
					PlayAudio(L"button", false);
					mouseS = false;
					currentPage = 1;
					currentMenu = 0;
				}
			}
			else if (IsInPixel(1026, 732, 50, 50)) {
				currentMenu = 2;
				if (mouseC & mouseS) {
					PlayAudio(L"button", false);
					mouseS = false;
					return 0;
				}
			}
			else {
				currentMenu = 0;
			}
		}

		char imgPath[100];
		sprintf(imgPath, "images/screen/index/%d%d.bmp", currentPage, currentMenu);
		Layer background = { true, "image", imgPath, 0, 0, 100};

		TCHAR mousePosition[100];
		wsprintf(mousePosition, TEXT("X: %-4d, Y: %-4d, C: %-2d, S: %-2d"), mouseX, mouseY, mouseC, mouseS);
		Layer positionText = { true, "text", "D2Coding", 0, 0, 100, mousePosition, 50, 900, 0, TA_LEFT, 0, RGB(0, 0, 0) };

		/*easyImage.count = 5;
		Layer layer[5];
		easyImage.layer = layer;*/
		easyImage.reset(&easyImage);
		easyImage.setLayer(&easyImage, 0, background);
		easyImage.setLayer(&easyImage, 1, positionText);
		easyImage.render(&easyImage);
	}
}