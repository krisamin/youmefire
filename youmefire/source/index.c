#include "../headers/easyDefine.h"

// 첫 게임 화면
int Index() {
	// 화면 관련 변수
	int currentPage = 1;
	int currentMenu = 0;
	int oldPage = -1;
	int oldMenu = -1;

	// 음악 재생
	PlayAudio(L"bgm/ost", true);
	easyImage.reset(&easyImage);
	while (true) {
		// 마우스 위치 및 클릭 처리
		if (currentPage == 1) {
			if (IsInPixel(825, 765, 270, 50)) {
				currentMenu = 1;
				if (mouseC && mouseS) {
					PlayAudio(L"effect/button", false);
					mouseS = false;
					if (CheckFileExists("data/save.txt")) {
						currentPage = 3;
						currentMenu = 0;
					}
					else {
						NewGame();
						return 1;
					}
				}
			}
			else if (IsInPixel(825, 850, 270, 50)) {
				currentMenu = 2;
				if (mouseC && mouseS) {
					PlayAudio(L"effect/button", false);
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
					PlayAudio(L"effect/button", false);
					mouseS = false;
					currentPage = 1;
					currentMenu = 0;
				}
			}
			else if (IsInPixel(1026, 732, 50, 50)) {
				currentMenu = 2;
				if (mouseC & mouseS) {
					PlayAudio(L"effect/button", false);
					mouseS = false;
					return 0;
				}
			}
			else {
				currentMenu = 0;
			}
		}
		else if (currentPage == 3) {
			if (IsInPixel(769, 731, 267, 50)) {
				currentMenu = 1;
				if (mouseC & mouseS) {
					PlayAudio(L"effect/button", false);
					mouseS = false;
					NewGame();
					return 1;
				}
			}
			else if (IsInPixel(1101, 730, 50, 50)) {
				currentMenu = 2;
				if (mouseC & mouseS) {
					PlayAudio(L"effect/button", false);
					mouseS = false;
					WCHAR* buffer;
					WCHAR* userData = GetReadFile("data/save.txt");
					WCHAR* dataName = wcstok(userData, L":", &buffer);
					WCHAR* dataSection = wcstok(NULL, L":", &buffer);
					name = dataName;
					StopAudio(L"bgm/ost");
					ReadStory(dataSection);
					return 1;
				}
			}
			else {
				currentMenu = 0;
			}
		}

		// 화면 업데이트시 실행
		if (currentPage != oldPage || currentMenu != oldMenu) {
			oldPage = currentPage;
			oldMenu = currentMenu;

			WCHAR* imgPath = (WCHAR*)malloc(100);
			wsprintf(imgPath, L"images/screen/index/%d%d.bmp", currentPage, currentMenu);
			Layer background = { true, 0, L"image", imgPath, 0, 0, 100 };

			/*TCHAR mousePosition[100];
			wsprintf(mousePosition, TEXT("X: %-4d, Y: %-4d, C: %-2d, S: %-2d"), mouseX, mouseY, mouseC, mouseS);
			Layer positionText = { true, "text", "D2Coding", 0, 0, 100, mousePosition, 50, 900, 0, TA_LEFT, 0, RGB(0, 0, 0) };
			easyImage.setLayer(&easyImage, 1, positionText);*/

			easyImage.setLayer(&easyImage, background);
			easyImage.render(&easyImage);
		}
	}
}