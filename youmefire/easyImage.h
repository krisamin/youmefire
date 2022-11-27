#include "utils.h"

#include <windows.h>
#include <stdbool.h>
#include <stdio.h>
#pragma comment(lib, "msimg32.lib")

typedef struct {
	char* name;
	int x, y;
	int opacity;
}Image;

typedef struct {
	char* name;
	int x, y;
	int opacity;
	char* text;
	int fontSize;
	int fontWeight;
	int fontAngle;
	int fontAlignX;
	int fontAlignY;
	COLORREF fontColor;
}Text;

typedef struct {
	bool enable;
	char* type;
	char* name;
	int x, y;
	int opacity;
	char* text;
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

	void (*setLayer)(struct _EasyImage*, int index, Layer layer);
	void (*reset)(struct _EasyImage*);
	void (*initialize)(struct _EasyImage*);
	void (*render)(struct _EasyImage*);
	void (*applyToDC)(HDC);
}EasyImage;

typedef struct {
	int width, height;
}Size;

inline Size GetBitmapSize(HBITMAP bitmap) {
	BITMAP tmpBitmap;
	GetObject(bitmap, sizeof(BITMAP), &tmpBitmap);
	const Size bitmapSize = { tmpBitmap.bmWidth, tmpBitmap.bmHeight };
	return bitmapSize;
}

inline HDC CreateNewBackDC(HDC compatibleDC) {
	const HDC backDC = CreateCompatibleDC(compatibleDC);
	const HBITMAP backBitmap = CreateCompatibleBitmap(compatibleDC, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(backDC, backBitmap);
	DeleteObject(backBitmap);
	return backDC;
}

inline BLENDFUNCTION GetBlendFunction(int alpha) {
	BLENDFUNCTION bf;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.BlendFlags = 0;
	bf.BlendOp = AC_SRC_OVER;
	bf.SourceConstantAlpha = alpha;
	return bf;
}

inline void PutBitmapToBackDC(HDC backDC, HDC consoleDC, Layer image, UINT transparentColor) {
	wchar_t fileNameWChar[100];
	swprintf(fileNameWChar, 100, L"%hs", image.name);

	const HDC bitmapDC = CreateCompatibleDC(backDC);
	const HBITMAP bitmap = (HBITMAP)LoadImage(NULL, fileNameWChar, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(bitmapDC, bitmap);

	const int x = image.x;
	const int y = image.y;
	const Size bitmapSize = GetBitmapSize(bitmap);
	const int width = bitmapSize.width;
	const int height = bitmapSize.height;

	if (image.opacity == 100) {
		TransparentBlt(backDC, x, y, width, height, bitmapDC, 0, 0, bitmapSize.width, bitmapSize.height, transparentColor);
	} else {
		const HDC alphaDC = CreateNewBackDC(consoleDC);
		BitBlt(alphaDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, backDC, 0, 0, SRCCOPY);
		BitBlt(alphaDC, x, y, width, height, bitmapDC, 0, 0, SRCPAINT);
		AlphaBlend(backDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, alphaDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetBlendFunction(255 * image.opacity / 100));
		DeleteDC(alphaDC);
	}

	DeleteObject(bitmap);
	DeleteDC(bitmapDC);
}

inline void PutTextToBackDC(HDC backDC, HDC consoleDC, Layer text) {
	wchar_t fontNameWChar[100];
	swprintf(fontNameWChar, 100, L"%hs", text.name);

	const HFONT font = CreateFont(text.fontSize, 0, text.fontAngle, 0, text.fontWeight, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, fontNameWChar);
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

inline void _setLayer(EasyImage* self, int index, Layer layer) {
	self->layer[index].enable = layer.enable;
	self->layer[index].type = layer.type;

	self->layer[index].name = layer.name;
	self->layer[index].x = layer.x;
	self->layer[index].y = layer.y;
	self->layer[index].opacity = layer.opacity;
	self->layer[index].text = layer.text;
	self->layer[index].fontSize = layer.fontSize;
	self->layer[index].fontWeight = layer.fontWeight;
	self->layer[index].fontAngle = layer.fontAngle;
	self->layer[index].fontAlignX = layer.fontAlignX;
	self->layer[index].fontAlignY = layer.fontAlignY;
	self->layer[index].fontColor = layer.fontColor;
}

inline void _reset(EasyImage* self) {
	for (int i = 0; i < self->count; i++) {
		self->layer[i].enable = false;
	}
}

inline void ApplyToDC(HDC dstDC, HDC srcDC) {
	BitBlt(dstDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, srcDC, 0, 0, SRCCOPY);
}

inline void _initialize(EasyImage* self) {
	self->_windowHandle = GetConsoleWindow();
	self->_consoleDC = GetDC(self->_windowHandle);
}

inline void _render(EasyImage* self) {
	const HDC backDC = CreateNewBackDC(self->_consoleDC);
	for (int _ = 0; _ < self->count; _++) {
		if (self->layer[_].enable) {
			if (self->layer[_].type == "image") {
				PutBitmapToBackDC(backDC, self->_consoleDC, self->layer[_], self->transparentColor);
			}
			else if (self->layer[_].type == "text") {
				PutTextToBackDC(backDC, self->_consoleDC, self->layer[_]);
			}
		}
	}
	ApplyToDC(self->_consoleDC, backDC);
	DeleteDC(backDC);
}

static const EasyImage DEFAULT_EASY_IMAGE = { NULL, NULL, 0, RGB(0,0,0), NULL, NULL, _setLayer, _reset, _initialize, _render, NULL };