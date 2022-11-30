#define _CRT_SECURE_NO_WARNINGS false
#pragma once
#ifndef DEFINE_H
#define DEFINE_H

#include "global.h"

//#include "easyDisplay.h"
#include "easyImage.h"
#include "easyAudio.h"
#include "easyMouse.h"
#include "easyFile.h"

#include "utils.h"
#include "initializer.h"

HANDLE CONSOLE_INPUT, CONSOLE_OUTPUT;
HWND WINDOW_HANDLE;
EasyImage easyImage;

void InitAudio();
void InitMouse();
void InitImage();
void ResetImage();

#endif