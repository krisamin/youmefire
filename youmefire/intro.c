#include "easyDefine.h"

int Intro() {
	Layer background = { true, 0, L"image", L"images/solid/101010.bmp", 0, 0, 100 };
	Layer black = { true, 9, L"image", L"images/solid/101010.bmp", 0, 0, 100 };
	Layer dialog = { true, 7, L"image", L"images/dialog/dialog.bmp", 72, 700, 60 };
	Layer nameTag = { true, 8, L"image", L"images/dialog/viichan.bmp", 120, 671, 100 };
	Layer hoverText = { true, 10, L"text", L"Pretendard Bold", 960, 540, 100, L"", 50, 400, 0, TA_CENTER, 1, RGB(255, 255, 255) };
	Layer dialogText = { true, 10, L"text", L"Pretendard SemiBold", 110, 760, 100, L"", 50, 400, 0, TA_LEFT, 0, RGB(0, 0, 0) };

	easyImage.reset(&easyImage);
	easyImage.setLayer(&easyImage, black);

	PlayAudio(L"music/viichanintro", true);
	VolumeAudio(L"music/viichanintro", 500);
	StepPrint(L"주인공은 기숙사 고등학생이다.", &hoverText);
	WaitClick();

	StepPrint(L"오랜만에 전체귀가를 하게 되어 사는 동네를 가게 되었다.", &hoverText);
	WaitClick();
	StepPrint(L"집에 들어와 짐을 풀고, 간단하게 끼니를 해결하려 했지만,", &hoverText);
	WaitClick();
	StepPrint(L"집에 먹을게 없어서 편의점으로 가게 된다.", &hoverText);
	WaitClick();
	StepPrint(L"편의점에서 계산을 하고 나오려던 찰나,", &hoverText);
	WaitClick();

	PlayAudio(L"effect/jab", false);
	Sleep(700);
	StepPrint(L"주인공은 어두운 회색 머리에, 검은색 머리핀을 한 여자와 부딪치게 된다.", &hoverText);
	WaitClick();

	int volume = 500;
	while (volume < 1000) {
		volume += 10;
		VolumeAudio(L"music/viichanintro", volume);
		Sleep(10);
	}

	/*Layer menuBackground = { true, 12, L"image", L"images/solid/000000.bmp", 0, 0, 80 };
	easyImage.setLayer(&easyImage, menuBackground);*/

	background.name = L"images/screen/introviichan/sorry.bmp";
	black.opacity = 0;
	easyImage.setLayer(&easyImage, black);
	easyImage.setLayer(&easyImage, background);
	easyImage.setLayer(&easyImage, dialog);
	easyImage.setLayer(&easyImage, nameTag);
	StepPrint(L"앗.. 죄송합니다", &dialogText);
	WaitClick();

	easyImage.reset(&easyImage);
	black.opacity = 80;
	easyImage.setLayer(&easyImage, background);
	easyImage.setLayer(&easyImage, black);
	StepPrint(L"여자가 말했다.", &hoverText);
	WaitClick();
	StepPrint(L"주인공은 부딪힌 여자를 어디선가 본 것 같았지만, 그냥 무시하고 집으로 갔다.", &hoverText);
	WaitClick();
	background.opacity = 0;
	easyImage.setLayer(&easyImage, background);
	StepPrint(L"못 한 짐정리를 마저 하고, 쉬려던 찰나,", &hoverText);
	WaitClick();
	PlayAudio(L"effect/calling", false);
	Sleep(2000);
	StepPrint(L"초등학교 때 부터 친하게 지내던 징버거 누나의 전화가 왔다.", &hoverText);
	WaitClick();
}