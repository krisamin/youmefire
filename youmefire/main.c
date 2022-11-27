#include "easyDefine.h"

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

WCHAR* substr(WCHAR* src, int m, int n) {
	// 목적지 문자열의 길이를 얻는다.
	int len = n - m;

	// 대상에 (len + 1) 문자를 할당합니다(추가 null 문자의 경우 +1).
	WCHAR* dest = (WCHAR*)malloc(sizeof(WCHAR) * (len + 1));

	// 소스 문자열에서 m번째와 n번째 인덱스 사이의 문자를 추출합니다.
	// 대상 문자열에 복사
	for (int i = m; i < n && (src[i] != '\0'); i++) {
		dest[i] = src[i];
	}

	// 대상 문자열을 null 종료
	dest[len] = '\0';
	return dest;
}

int main() {
	MainProcess();
	//Sleep(1000);

	Intro();

	PlayAudio(L"ost", true);
	int type = Index();
	if (!type)return 0;
	StopAudio(L"ost");

	Layer background = { true, L"image", L"images/solid/101010.bmp", 0, 0, 100 };
	Layer dialog = { true, L"image", L"images/dialog/dialog.bmp", 72, 700, 60 };
	Layer nameTag = { true, L"image", L"images/dialog/viichan.bmp", 120, 671, 100 };
	Layer hoverText = { true, L"text", L"Pretendard Bold", 960, 540, 100, L"", 50, 400, 0, TA_CENTER, 1, RGB(255, 255, 255)};
	Layer dialogText = { true, L"text", L"Pretendard SemiBold", 110, 760, 100, L"", 50, 400, 0, TA_LEFT, 0, RGB(0, 0, 0)};

	easyImage.reset(&easyImage);
	easyImage.setLayer(&easyImage, 0, background);

	WCHAR* string = L"주인공은 기숙사 고등학생이다.";
	int count = 0, index = 1;
	while (true) {
		if (mouseC & mouseS) {
			mouseS = false;
			hoverText.text = string;
			easyImage.setLayer(&easyImage, 10, hoverText);
			easyImage.render(&easyImage);
			break;
		}
		if (count >= 20) {
			count = 0;
			hoverText.text = substr(string, 0, index++);
			easyImage.setLayer(&easyImage, 10, hoverText);
			easyImage.render(&easyImage);
			if (index > wcslen(string)) break;
		}
		count++;
		Sleep(1);
	}

	getch();

	hoverText.text = L"오랜만에 전체귀가를 하게 되어 사는 동네를 가게 되었다.";
	easyImage.setLayer(&easyImage, 10, hoverText);
	easyImage.render(&easyImage);

	getch();

	hoverText.text = L"집에 들어와 짐을 풀고, 간단하게 끼니를 해결하려 했지만, 집에 먹을게 없어서 편의점으로 가게 된다.";
	easyImage.setLayer(&easyImage, 10, hoverText);
	easyImage.render(&easyImage);

	getch();

	hoverText.text = L"편의점에서 계산을 하고 나오려던 찰나,";
	easyImage.setLayer(&easyImage, 10, hoverText);
	easyImage.render(&easyImage);

	getch();

	hoverText.text = L"주인공은 어두운 회색 머리에, 검은색 머리핀을 한 여자와 부딪치게 된다.";
	easyImage.setLayer(&easyImage, 10, hoverText);
	easyImage.render(&easyImage);

	getch();

	background.name = L"images/screen/introviichan/sorry.bmp";
	dialogText.text = L"앗.. 죄송합니다";
	easyImage.setLayer(&easyImage, 0, background);
	easyImage.setLayer(&easyImage, 7, dialog);
	easyImage.setLayer(&easyImage, 8, nameTag);
	easyImage.setLayer(&easyImage, 10, dialogText);
	easyImage.render(&easyImage);

	//easyImage.setLayer(&easyImage, 1, jingburgerDialog);

	PlayAudio(L"yurusu", true);
	VolumeAudio(L"yurusu", 1000);

	Sleep(100000);
}