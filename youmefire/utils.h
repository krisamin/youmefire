#pragma once
#include <Windows.h>
#include <stdbool.h>

#ifndef UTILS_H
#define UTILS_H
HANDLE CONSOLE_INPUT, CONSOLE_OUTPUT;
HWND WINDOW_HANDLE;

INPUT_RECORD rec;
DWORD dwNOER;
HANDLE CIN;
int mouseX, mouseY, mouseC, mouseS;
#endif