#include "easyDefine.h"

void InitImage(int count) {
	easyImage = DEFAULT_EASY_IMAGE;
	easyImage.initialize(&easyImage);

	easyImage.count = count;
	Layer* layer = (Layer*)malloc(sizeof(Layer) * easyImage.count);
	easyImage.layer = layer;

	easyImage.reset(&easyImage);
	easyImage.render(&easyImage);
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

void StepPrint(WCHAR* string, Layer* layer) {
	int count = 0, index = 1;
	while (true) {
		if (mouseC & mouseS) {
			mouseS = false;
			layer->text = string;
			easyImage.setLayer(&easyImage, *layer);
			easyImage.render(&easyImage);
			break;
		}
		if (count >= 10) {
			count = 0;
			layer->text = substr(string, 0, index++);
			easyImage.setLayer(&easyImage, *layer);
			easyImage.render(&easyImage);
			if (index > wcslen(string)) break;
		}
		count++;
		Sleep(1);
	}
}

void WaitClick() {
	while (!(mouseC & mouseS)) continue;
	mouseS = false;
}