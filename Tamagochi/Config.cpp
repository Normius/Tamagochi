#include "Config.h"

// ----------------------------- Класс Color ----------------------------------------------

CColor::CColor(unsigned char r, unsigned char g, unsigned char b)
	:R(r), G(g), B(b)
{
	pen = CreatePen(PS_SOLID, 0, RGB(r, g, b));
	brush = CreateSolidBrush(RGB(r, g, b));
}

// ------------ Выбор цвета и назначение его для карандаша и кисти
void CColor::SelectColor(HDC hdc) const
{
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);
}

// ----------------------------- Класс Config ----------------------------------------------

// ------------ Вычисляет псевдослучайное число в диапазоне [minValue, .. maxValue]
int CConfig::GetRandom(int minValue, int maxValue)
{ 
	return minValue + rand() % (maxValue - minValue + 1);
}

float CConfig::slowCurrentFrameValue = 0.0f;

unsigned int CConfig::currentFrameValue = 0;

const CColor CConfig::backgroundColor(97, 121, 107);
const CColor CConfig::mainBrightColor(19, 30, 24);
const CColor CConfig::secondPaleColor(60, 75, 67);

HWND CConfig::Hwnd;
//static const CColor backgroundColor(0, 0, 0);