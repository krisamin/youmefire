#include "utils.h"

#include <stdio.h>
#include <windows.h>
#include <windowsx.h>
#include <process.h>
#include <stdbool.h>

// 마우스 클릭 및 위치
inline void checkMouseStateThread(void* param) {
  HWND consoleWND = GetConsoleWindow();
  POINT mousePos;
	int oldMouseX = -1, oldMouseY = -1;
  while (true) {
		GetCursorPos(&mousePos);
		ScreenToClient(consoleWND, &mousePos);
		mouseX = mousePos.x;
		mouseY = mousePos.y;
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			mouseC = 1;
		} else {
			mouseC = 0;
			mouseS = true;
		}

		if (oldMouseX != mouseX || oldMouseY != mouseY) {
			oldMouseX = mouseX;
			oldMouseY = mouseY;
		}
		Sleep(1);
  }
}

// 마우스 초기화
inline void InitMouse() {
  SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
  _beginthread(checkMouseStateThread, 0, NULL);
}