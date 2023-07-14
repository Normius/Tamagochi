#pragma once

#include <Windows.h>

// ----------------------------- Класс Color ----------------------------------------------
class CColor
{
public:
	CColor(unsigned char r, unsigned char g, unsigned char b);

	unsigned char R, G, B;
};

// ----------------------------- Класс Config ----------------------------------------------
class CConfig
{
public:
	static void InitColors();

	static const int SizeScale = 1;

	static int CurrentTimerValue;

	static const int FPS = 10;

	static const CColor backgroundColor, mainColor, cloudColor;

	static HWND Hwnd;

	static HPEN backgroundPen;
	static HBRUSH backgroundBrush;

};