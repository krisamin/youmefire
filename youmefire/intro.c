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

	easyImage.reset(&easyImage);
	background.name = L"images/screen/intro/sorry.bmp";
	easyImage.setLayer(&easyImage, background);
	FadeImage(100, 0, &black);

	int volume = 500;
	while (volume < 1000) {
		volume += 10;
		VolumeAudio(L"music/viichanintro", volume);
		Sleep(10);
	}

	easyImage.setLayer(&easyImage, dialog);
	easyImage.setLayer(&easyImage, nameTag);
	StepPrint(L"앗.. 죄송합니다", &dialogText);
	WaitClick();

	easyImage.reset(&easyImage);
	easyImage.setLayer(&easyImage, background);
	easyImage.setLayer(&easyImage, black);
	FadeImage(0, 80, &black);
	StepPrint(L"여자가 말했다.", &hoverText);
	WaitClick();
	StepPrint(L"주인공은 부딪힌 여자를 어디선가 본 것 같았지만, 그냥 무시하고 집으로 갔다.", &hoverText);
	WaitClick();

	easyImage.reset(&easyImage);
	easyImage.setLayer(&easyImage, background);
	FadeImage(80, 100, &black);

	easyImage.reset(&easyImage);
	easyImage.setLayer(&easyImage, black);
	StepPrint(L"못 한 짐정리를 마저 하고, 쉬려던 찰나,", &hoverText);
	WaitClick();

	PlayAudio(L"effect/calling", false);
	Sleep(1000);
	background.name = L"images/screen/intro/calling.bmp";
	easyImage.setLayer(&easyImage, background);
	FadeImage(100, 80, &black);

	StepPrint(L"초등학교 때 부터 친하게 지내던 징버거 누나의 전화가 왔다.", &hoverText);
	WaitClick();
	FadeImage(80, 0, &black);

	nameTag.name = L"images/dialog/jingburger.bmp";
	easyImage.setLayer(&easyImage, dialog);
	easyImage.setLayer(&easyImage, nameTag);
	WCHAR* line = (WCHAR*)malloc(sizeof(WCHAR) * 100);
	wsprintf(line, L"%s아 뭐해? 할 거 없으면 상포역으로 나와", name);
	StepPrint(line, &dialogText);
	WaitClick();
	easyImage.reset(&easyImage);
	easyImage.setLayer(&easyImage, background);
	FadeImage(0, 100, &black);
	PlayAudio(L"effect/doing", false);
	StepPrint(L"징버거 누나의 전화를 받고, 급하게 근처 상포역으로 갈 준비를 했다.", &hoverText);
	WaitClick();
}