#include "../headers/easyDefine.h"

//#include <cstdio>
#include <stdlib.h>

// pick random name in names.txt file
WCHAR* GetRandomName() {
	WCHAR* nameList = GetReadFile("data/names.txt");
	WCHAR* buffer;
	WCHAR* splitName = wcstok(nameList, L"\n", &buffer);
	int index = 0;
	int inRand = rand() % 20;
	while (splitName != NULL) {
		if (inRand == index++) {
			WCHAR* returnName = (WCHAR*)malloc(sizeof(WCHAR) * lstrlenW(splitName));
			wcscpy(returnName, splitName);
			free(nameList);
			return returnName;
		}
		splitName = wcstok(NULL, L"\n", &buffer);
	}
}


void NewGame() {
  name = GetRandomName();
	int currentMenu = 0;
	bool nameUpdate = true;

	Layer nameLayer = { true, 1, L"text", L"Pretendard Bold", 960, 540, 100, TEXT(""), 96, 400, 0, TA_CENTER, 1, RGB(255, 255, 255)};

	easyImage.reset(&easyImage);
	while (true) {
		if (IsInPixel(629, 809, 341, 91)) {
			currentMenu = 1;
			if (mouseC && mouseS) {
				PlayAudio(L"effect/button", false);
				mouseS = false;
				name = GetRandomName();
				nameUpdate = true;
			}
		}
		else if (IsInPixel(1018, 809, 274, 91)) {
			currentMenu = 2;
			if (mouseC && mouseS) {
				PlayAudio(L"effect/button", false);
				mouseS = false;
				StopAudio(L"bgm/ost");
				ReadStory(L"ENDING-V-A");
				break;
			}
		}
		else {
			currentMenu = 0;
		}


		WCHAR* imgPath = (WCHAR*)malloc(sizeof(WCHAR) * 100);
		wsprintf(imgPath, L"images/screen/newgame/%d.bmp", currentMenu);
		Layer background = { true, 0, L"image", imgPath, 0, 0, 100 };

		if (nameUpdate) {
			nameUpdate = false;
			nameLayer.text = name;
		}

		/*easyImage.count = 5;
		Layer layer[5];
		easyImage.layer = layer;*/
		easyImage.setLayer(&easyImage, background);
		easyImage.setLayer(&easyImage, nameLayer);
		easyImage.render(&easyImage);
	}
}