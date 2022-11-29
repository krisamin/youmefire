#include "utils.h"

#include <windows.h>
#pragma comment(lib, "winmm.lib")

inline void OpenAudio(WCHAR* fileName, WCHAR* alias) {
	WCHAR command[100];
	wsprintf(command, TEXT("open %s alias %s"), fileName, alias);
	mciSendString(command, NULL, 0, 0);
}

inline void StopAudio(WCHAR* alias) {
	WCHAR command[100];
	wsprintf(command, TEXT("stop %s"), alias);
	mciSendString(command, NULL, 0, NULL);
}

inline void PlayAudio(WCHAR* alias, int repeat) {
	WCHAR command[100];
	wsprintf(command, TEXT("seek %s to start"), alias);
	mciSendString(command, NULL, 0, 0);
	if (repeat)
		wsprintf(command, TEXT("play %s repeat"), alias);
	else
		wsprintf(command, TEXT("play %s"), alias);
	mciSendString(command, NULL, 0, 0);
}

inline void VolumeAudio(WCHAR* alias, int volume) {
	WCHAR command[100];
	wsprintf(command, TEXT("setaudio %s volume to %d"), alias, volume);
	mciSendString(command, NULL, 0, 0);
}

inline void FadeAudio(WCHAR* alias, int from, int to) {
	int volume = from;
	WCHAR command[100];
	wsprintf(command, TEXT("setaudio %s volume to %d"), alias, from);
	mciSendString(command, NULL, 0, 0);
	while ((to > from && volume < to) || (to < from && volume > to)) {
		if (to > from) volume += 10;
		if (to < from) volume -= 10;
		if ((to > from && volume >= to) || (to < from && volume <= to)) volume = to;
		VolumeAudio(alias, volume);
		Sleep(10);
	}
}

inline void InitAudio() {
	OpenAudio(L"sounds/bgm/ost.mp3", L"bgm/ost");
	OpenAudio(L"sounds/bgm/yurusu.mp3", L"bgm/yurusu");
	OpenAudio(L"sounds/bgm/intro.mp3", L"bgm/intro");
	OpenAudio(L"sounds/bgm/prologue1.mp3", L"bgm/prologue1");
	OpenAudio(L"sounds/bgm/prologue2.mp3", L"bgm/prologue2");
	OpenAudio(L"sounds/bgm/interlude.mp3", L"bgm/interlude");
	OpenAudio(L"sounds/bgm/jingburger1.mp3", L"bgm/jingburger1");
	OpenAudio(L"sounds/bgm/crisis1.mp3", L"bgm/crisis1");
	OpenAudio(L"sounds/bgm/crisis2.mp3", L"bgm/crisis2");
	OpenAudio(L"sounds/bgm/crisis3.mp3", L"bgm/crisis3");

	OpenAudio(L"sounds/effect/button.mp3", L"effect/button");
	OpenAudio(L"sounds/effect/jab.mp3", L"effect/jab");
	OpenAudio(L"sounds/effect/calling.mp3", L"effect/calling");
	OpenAudio(L"sounds/effect/doing.mp3", L"effect/doing");
	OpenAudio(L"sounds/effect/alert.mp3", L"effect/alert");
	OpenAudio(L"sounds/effect/snow.mp3", L"effect/snow");
	OpenAudio(L"sounds/effect/knock.mp3", L"effect/knock");
	OpenAudio(L"sounds/effect/dingdong.mp3", L"effect/dingdong");
}