#include "../headers/easyDefine.h"

//#include <cstdio>
#include <stdlib.h>

// pick random name in names.txt file
WCHAR* GetRandomName() {
	WCHAR* temp = (WCHAR*)malloc(sizeof(WCHAR) * 0);
	WCHAR* pLine;
	FILE* fp;
	fopen_s(&fp, "data/names.txt", "r,ccs=UTF-8");

	int length = 0;
	while (true) {
		temp = (WCHAR*)realloc(temp, sizeof(WCHAR) * (length + 1));
		temp[length] = fgetwc(fp);
		if(temp[length] == WEOF) break;
		length ++;
	}
	fclose(fp);

	WCHAR* buffer;
	WCHAR* splitName = wcstok(temp, L"\n", &buffer);
	int index = 0;
	int inRand = rand() % 20;
	while (splitName != NULL) {
		if (inRand == index++) {
			WCHAR* returnName = (WCHAR*)malloc(sizeof(WCHAR) * lstrlenW(splitName));
			wcscpy(returnName, splitName);
			free(temp);
			return returnName;
		}
		splitName = wcstok(NULL, L"\n", &buffer);
	}
}


int NewGame() {
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
				ReadStory(L"INTRO");
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