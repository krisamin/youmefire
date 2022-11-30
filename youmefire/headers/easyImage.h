#include "utils.h"

#include <windows.h>
#include <stdbool.h>
#include <stdio.h>
#pragma comment(lib, "msimg32.lib")

// 구조체 선언
typedef struct {
	WCHAR* name;
	int x, y;
	int opacity;
}Image;

typedef struct {
	WCHAR* name;
	int x, y;
	int opacity;
	WCHAR* text;
	int fontSize;
	int fontWeight;
	int fontAngle;
	int fontAlignX;
	int fontAlignY;
	COLORREF fontColor;
}Text;

typedef struct {
	bool enable;
	int index;
	WCHAR* type;
	WCHAR* name;
	int x, y;
	int opacity;
	WCHAR* text;
	int fontSize;
	int fontWeight;
	int fontAngle;
	int fontAlignX;
	int fontAlignY;
	COLORREF fontColor;
}Layer;

typedef struct _EasyImage {
	Image* images;
	Layer* layer;
	int count;
	UINT transparentColor;

	HWND _windowHandle;
	HDC _consoleDC;

	void (*setLayer)(struct _EasyImage*, Layer layer);
	void (*reset)(struct _EasyImage*);
	void (*initialize)(struct _EasyImage*);
	void (*render)(struct _EasyImage*);
	void (*applyToDC)(HDC);
}EasyImage;

typedef struct {
	int width, height;
}Size;

// 비트맵 사이즈 반환
inline Size GetBitmapSize(HBITMAP bitmap) {
	BITMAP tmpBitmap;
	GetObject(bitmap, sizeof(BITMAP), &tmpBitmap);
	const Size bitmapSize = { tmpBitmap.bmWidth, tmpBitmap.bmHeight };
	return bitmapSize;
}

// 빈 DC 생성
inline HDC CreateNewBackDC(HDC compatibleDC) {
	const HDC backDC = CreateCompatibleDC(compatibleDC);
	const HBITMAP backBitmap = CreateCompatibleBitmap(compatibleDC, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(backDC, backBitmap);
	DeleteObject(backBitmap);
	return backDC;
}

// 투명도를 위한 BF
inline BLENDFUNCTION GetBlendFunction(int alpha) {
	BLENDFUNCTION bf;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.BlendFlags = 0;
	bf.BlendOp = AC_SRC_OVER;
	bf.SourceConstantAlpha = alpha;
	return bf;
}

// 이미지 추가
inline void PutBitmapToBackDC(HDC backDC, HDC consoleDC, Layer image, UINT transparentColor) {
	const HDC bitmapDC = CreateCompatibleDC(backDC);
	const HBITMAP bitmap = (HBITMAP)LoadImage(NULL, image.name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(bitmapDC, bitmap);

	const int x = image.x;
	const int y = image.y;
	const Size bitmapSize = GetBitmapSize(bitmap);
	const int width = bitmapSize.width;
	const int height = bitmapSize.height;

	AlphaBlend(backDC, x, y, width, height, bitmapDC, 0, 0, width, height, GetBlendFunction(255 * image.opacity / 100));
	//if (image.opacity == 100) {
	//	TransparentBlt(backDC, x, y, width, height, bitmapDC, 0, 0, bitmapSize.width, bitmapSize.height, transparentColor);
	//} else {
	//	const HDC alphaDC = CreateNewBackDC(consoleDC);
	//	//TransparentBlt(alphaDC, x, y, WINDOW_WIDTH, WINDOW_HEIGHT, backDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, transparentColor);
	//	//TransparentBlt(alphaDC, x, y, width, height, bitmapDC, 0, 0, width, height, transparentColor);
	//	AlphaBlend(backDC, x, y, width, height, bitmapDC, 0, 0, width, height, GetBlendFunction(255 * image.opacity / 100));
	//	/*BitBlt(alphaDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, backDC, 0, 0, SRCCOPY);
	//	BitBlt(alphaDC, x, y, width, height, bitmapDC, 0, 0, SRCPAINT);
	//	AlphaBlend(backDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, alphaDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetBlendFunction(255 * image.opacity / 100));*/
	//	DeleteDC(alphaDC);
	//}

	DeleteObject(bitmap);
	DeleteDC(bitmapDC);
}

// 텍스트 추가
inline void PutTextToBackDC(HDC backDC, HDC consoleDC, Layer text) {

	const HFONT font = CreateFont(text.fontSize, 0, text.fontAngle, 0, text.fontWeight, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, text.name);
	SelectObject(backDC, font);

	SetBkMode(backDC, TRANSPARENT);
	SetTextColor(backDC, text.fontColor);
	SetTextAlign(backDC, text.fontAlignX);

	SIZE offset;
	GetTextExtentPoint32(backDC, text.text, strlen(text.text), &offset);
	if (text.fontAlignY == 1) {
		text.y -= offset.cy / 2;
	}

	TextOut(backDC, text.x, text.y, text.text, lstrlen(text.text));

	PAINTSTRUCT paint;
	EndPaint(WINDOW_HANDLE, &paint);
	DeleteObject(font);
}

// 레이어 추가
inline void _setLayer(EasyImage* self, Layer layer) {
	self->layer[layer.index] = layer;
}

// 레이어 초기화
inline void _reset(EasyImage* self) {
	for (int i = 0; i < self->count; i++) {
		self->layer[i].enable = false;
	}
}

// 화면에 적용
inline void ApplyToDC(HDC dstDC, HDC srcDC) {
	BitBlt(dstDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, srcDC, 0, 0, SRCCOPY);
}

// 초기화
inline void _initialize(EasyImage* self) {
	self->_windowHandle = GetConsoleWindow();
	self->_consoleDC = GetDC(self->_windowHandle);
}

// 렌더링
inline void _render(EasyImage* self) {
	const HDC backDC = CreateNewBackDC(self->_consoleDC);
	for (int _ = 0; _ < self->count; _++) {
		if (self->layer[_].enable) {
			if (self->layer[_].type == L"image") {
				PutBitmapToBackDC(backDC, self->_consoleDC, self->layer[_], self->transparentColor);
			}
			else if (self->layer[_].type == L"text") {
				PutTextToBackDC(backDC, self->_consoleDC, self->layer[_]);
			}
		}
	}
	ApplyToDC(self->_consoleDC, backDC);
	DeleteDC(backDC);
}

static const EasyImage DEFAULT_EASY_IMAGE = { NULL, NULL, 0, RGB(0, 0, 0), NULL, NULL, _setLayer, _reset, _initialize, _render, NULL };