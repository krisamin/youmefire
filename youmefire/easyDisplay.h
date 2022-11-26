#define _CRT_SECURE_NO_WARNINGS false

#include <windows.h>
#include <stdbool.h>
#pragma comment(lib, "msimg32.lib")

HWND WINDOW_HANDLE;
HWND GetConsoleWindowHandle() {
  WCHAR title[2048] = { 0 };
  GetConsoleTitle(title, 2048);
  HWND hWnd = FindWindow(NULL, title);
  SetConsoleTitle(title);
  return hWnd;
}

void GotoXY(int cursor_x, int cursor_y) {
  COORD pos = { cursor_x, cursor_y };
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void SetConsole(int width, int height) {
  int displayWidth = GetSystemMetrics(SM_CXSCREEN);
  int displayHeight = GetSystemMetrics(SM_CYSCREEN);
	printf("Resolution: %d %d\n", displayWidth, displayHeight);

  HWND hWnd = GetConsoleWindowHandle();
  RECT wrect;
  GetWindowRect(hWnd, &wrect);
  RECT crect;
  GetClientRect(hWnd, &crect);
  POINT lefttop = { crect.left, crect.top }; // Practicaly both are 0
  ClientToScreen(hWnd, &lefttop);
  POINT rightbottom = { crect.right, crect.bottom };
  ClientToScreen(hWnd, &rightbottom);

  int left_border = lefttop.x - wrect.left; // Windows 10: includes transparent part
  int right_border = wrect.right - rightbottom.x; // As above
  int bottom_border = wrect.bottom - rightbottom.y; // As above
  int top_border_with_title_bar = lefttop.y - wrect.top; // There is no transparent part
  printf("Border: %d %d %d %d\n", left_border, right_border, bottom_border, top_border_with_title_bar);

  if (displayWidth == width && displayHeight == height) {
    keybd_event(VK_MENU, 0x38, 0, 0);
    keybd_event(VK_RETURN, 0x1c, 0, 0);
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
  } else {
	  int resizedWidth = width + left_border + right_border;
		int resizedHeight = height + top_border_with_title_bar + bottom_border;
		printf("Size: %d %d\n", resizedWidth, resizedHeight);
    MoveWindow(
      hWnd,
      displayWidth / 2 - resizedWidth / 2,
      displayHeight / 2 - resizedHeight /2,
      resizedWidth,
      resizedHeight,
      TRUE);
  }
	Sleep(1000);
}

void HideCursor() {
  CONSOLE_CURSOR_INFO cursorInfo;
  GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
  cursorInfo.bVisible = false;
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void HideScrollBar() {
  // get handle to the console window
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

  // retrieve screen buffer info
  CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
  GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);

  // current window size
  short winWidth = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left + 1;
  short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;

  // current screen buffer size
  short scrBufferWidth = scrBufferInfo.dwSize.X;
  short scrBufferHeight = scrBufferInfo.dwSize.Y;

  // to remove the scrollbar, make sure the window height matches the screen buffer height
  COORD newSize;
  newSize.X = scrBufferWidth;
  newSize.Y = winHeight;

  // set the new screen buffer dimensions
  int Status = SetConsoleScreenBufferSize(hOut, newSize);
  if (Status == 0) {
    //cout << "SetConsoleScreenBufferSize() failed! Reason : " << GetLastError() << endl;
    exit(Status);
  }
}