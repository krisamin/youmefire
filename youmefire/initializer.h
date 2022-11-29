#pragma once
#define _CRT_SECURE_NO_WARNINGS false

#include "utils.h"
#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <time.h>

#pragma comment(lib, "msimg32.lib")

inline void GetHandle() {
  CONSOLE_INPUT = GetStdHandle(STD_INPUT_HANDLE);
  CONSOLE_OUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
  WINDOW_HANDLE = GetConsoleWindow();
}

inline void SetConsole(int width, int height, bool fullscreen) {
  if (fullscreen) {
    keybd_event(VK_MENU, 0x38, 0, 0);
    keybd_event(VK_RETURN, 0x1c, 0, 0);
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);

    DEVMODE devmode;
    devmode.dmPelsWidth = WINDOW_WIDTH;
    devmode.dmPelsHeight = WINDOW_HEIGHT;
    devmode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
    devmode.dmSize = sizeof(DEVMODE);
    long result = ChangeDisplaySettings(&devmode, 0);
		Sleep(1000);
  }
  else {
    int displayWidth = GetSystemMetrics(SM_CXSCREEN);
    int displayHeight = GetSystemMetrics(SM_CYSCREEN);
    //printf("Resolution: %d %d\n", displayWidth, displayHeight);

    RECT wrect;
    GetWindowRect(WINDOW_HANDLE, &wrect);
    RECT crect;
    GetClientRect(WINDOW_HANDLE, &crect);
    POINT lefttop = { crect.left, crect.top }; // Practicaly both are 0
    ClientToScreen(WINDOW_HANDLE, &lefttop);
    POINT rightbottom = { crect.right, crect.bottom };
    ClientToScreen(WINDOW_HANDLE, &rightbottom);

    int left_border = lefttop.x - wrect.left; // Windows 10: includes transparent part
    int right_border = wrect.right - rightbottom.x; // As above
    int bottom_border = wrect.bottom - rightbottom.y; // As above
    int top_border_with_title_bar = lefttop.y - wrect.top; // There is no transparent part
    //printf("Border: %d %d %d %d\n", left_border, right_border, bottom_border, top_border_with_title_bar);

    if (displayWidth == width && displayHeight == height) {
      keybd_event(VK_MENU, 0x38, 0, 0);
      keybd_event(VK_RETURN, 0x1c, 0, 0);
      keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
      keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
    }
    else {
      int resizedWidth = width + left_border + right_border;
      int resizedHeight = height + top_border_with_title_bar + bottom_border;
      //printf("Size: %d %d\n", resizedWidth, resizedHeight);
      MoveWindow(
        WINDOW_HANDLE,
        displayWidth / 2 - resizedWidth / 2,
        displayHeight / 2 - resizedHeight / 2,
        resizedWidth,
        resizedHeight,
        TRUE);
    }
    Sleep(1000);
  }
}

inline void HideCursor() {
  CONSOLE_CURSOR_INFO cursorInfo;
  GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
  cursorInfo.bVisible = false;
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

inline void HideScrollBar() {
  /*HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

  CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
  GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);

  short winWidth = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left + 1;
  short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;

  short scrBufferWidth = scrBufferInfo.dwSize.X;
  short scrBufferHeight = scrBufferInfo.dwSize.Y;

  COORD newSize;
  newSize.X = scrBufferWidth;
  newSize.Y = winHeight;

  int Status = SetConsoleScreenBufferSize(hOut, newSize);
  if (Status == 0) {
    exit(Status);
  }*/

  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO info;
  GetConsoleScreenBufferInfo(handle, &info);
  COORD new_size = {
    info.srWindow.Right - info.srWindow.Left + 1,
    info.srWindow.Bottom - info.srWindow.Top + 1
  };
  SetConsoleScreenBufferSize(handle, new_size);
}

inline void initialize() {
	SetConsoleTitle(TEXT("Initialize"));

  GetHandle();
	SetProcessDPIAware();
  HideCursor();
  HideScrollBar();
	SetConsole(WINDOW_WIDTH, WINDOW_HEIGHT, false);
  HideCursor();
  HideScrollBar();
  setlocale(LC_ALL, "KOREAN");
  srand(time(NULL));

	SetConsoleTitle(L":: 누나 동생 청춘 ::");
}