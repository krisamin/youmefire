#include "../headers/easyDefine.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <wchar.h>

// 레이어 초기화
void InitImage(int count) {
	easyImage = DEFAULT_EASY_IMAGE;
	easyImage.initialize(&easyImage);

	easyImage.count = count;
	Layer* layer = (Layer*)malloc(sizeof(Layer) * easyImage.count);
	easyImage.layer = layer;

	easyImage.reset(&easyImage);
	easyImage.render(&easyImage);
}

// 글씨 자르기
WCHAR* SubStr(WCHAR* src, int m, int n) {
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

// 서서히 출력
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
			layer->text = SubStr(string, 0, index++);
			easyImage.setLayer(&easyImage, *layer);
			easyImage.render(&easyImage);
			if (index > wcslen(string)) break;
		}
		count++;
		Sleep(1);
	}
}

// 클릭 대기
void WaitClick() {
	while (!(mouseC & mouseS)) Sleep(1);
	mouseS = false;
}

// 이미지 패이딩
void FadeImage(Layer* layer, int from, int to) {
	int opacity = from;
	layer->opacity = opacity;
	easyImage.setLayer(&easyImage, *layer);
	easyImage.render(&easyImage);
	while ((to > from && opacity < to) || (to < from && opacity > to)) {
		if (to > from) opacity += 10;
		if (to < from) opacity -= 10;
		if ((to > from && opacity >= to) || (to < from && opacity <= to)) opacity = to;
		layer->opacity = opacity;
		easyImage.setLayer(&easyImage, *layer);
		easyImage.render(&easyImage);
	}
}

// 글씨 치환
int wcsrpl(const wchar_t* wstr, const wchar_t* wsubstr, const wchar_t* wrepl) {
	register int i = 0;
	wchar_t* chr = NULL;
	size_t sub_len = 0;
	size_t repl_len = 0;

	assert(wstr != NULL);
	assert(wsubstr != NULL);
	assert(wrepl != NULL);

	chr = wcsstr(wstr, wsubstr);
	if (chr == NULL) return 0;

	sub_len = wcslen(wsubstr);
	repl_len = wcslen(wrepl);

	for (i = 0; i < (int)sub_len && i < (int)repl_len; i++)	{
		*chr = wrepl[i];
		chr++;
		if (chr == '\0') break;
	}

	return i;
}

// 마우스 위치 확인
int IsInPixel(int x, int y, int lenX, int lenY) {
	if (mouseX >= x && mouseX <= x + lenX && mouseY >= y && mouseY <= y + lenY) {
		return 1;
	}
	else {
		return 0;
	}
}