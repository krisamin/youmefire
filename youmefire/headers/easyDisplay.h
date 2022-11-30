#define _CRT_SECURE_NO_WARNINGS false

#include <windows.h>
#include <stdbool.h>
#pragma comment(lib, "msimg32.lib")

// 위치로 이동
void GotoXY(int cursor_x, int cursor_y) {
  COORD pos = { cursor_x, cursor_y };
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}