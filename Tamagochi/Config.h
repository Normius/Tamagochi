#pragma once

#include <Windows.h>

// ----------------------------- Класс Color ----------------------------------------------
class CColor
{
public:
	CColor(unsigned char r, unsigned char g, unsigned char b);

	void SelectColor(HDC hdc) const;

	unsigned char R, G, B;
	HPEN pen;
	HBRUSH brush;
};
// -----------------------------------------------------------------------------------

// ----------------------------- Класс Config ----------------------------------------------
class CConfig
{
public:
	static int GetRandom(int minValue, int maxValue);

	static const int leftBorder = 0; //Границы с учётом отрисовки
	static const int rightBorder = 800;
	static const int topBorder = 0;
	static const int downBorder = 600;

	static const int SizeScale = 1; //Целочисленный масштаб (При изменении масштаба, изменить также дробный FSizeScale)
	static const int FPS = 20;

	static const float FSizeScale; //Дробный масштаб
	static const float minShift;
	static const float backgroundAcceleration;

	static float slowCurrentTimerValue;


	static int currentTimerValue;


	static const CColor backgroundColor, mainBrightColor, secondPaleColor;

	static HWND Hwnd;

	static const int MaxBackgroundObjects = 10;
	static const int MaxClouds = 4;
};
// -----------------------------------------------------------------------------------