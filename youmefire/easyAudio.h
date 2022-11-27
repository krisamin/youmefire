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
	OpenAudio(L"sounds/music/ost.mp3", L"ost");
	OpenAudio(L"sounds/music/yurusu.mp3", L"yurusu");
	OpenAudio(L"sounds/effect/button.mp3", L"button");
}