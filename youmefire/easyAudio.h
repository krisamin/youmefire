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

inline void InitAudio() {
	OpenAudio(L"sounds/music/ost.mp3", L"music/ost");
	OpenAudio(L"sounds/music/yurusu.mp3", L"music/yurusu");
	OpenAudio(L"sounds/music/それぞれの大晦日.mp3", L"music/viichanintro");

	OpenAudio(L"sounds/effect/button.mp3", L"effect/button");
	OpenAudio(L"sounds/effect/jab.mp3", L"effect/jab");
	OpenAudio(L"sounds/effect/calling.mp3", L"effect/calling");
}