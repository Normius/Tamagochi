#include "Config.h"

// ----------------------------- Класс Color ----------------------------------------------

// ------------ Конструктор
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
{//123
	return minValue + rand() % (maxValue - minValue + 1);
}

const CColor CConfig::backgroundColor(97, 121, 107);
const CColor CConfig::mainBrightColor(19, 30, 24);
const CColor CConfig::secondPaleColor(60, 75, 67);

const float CConfig::FSizeScale = 1.0f; //Дробный масштаб (При изменении масштаба, изменить также целочисленный )
const float CConfig::minShift = 1.0f;
const float CConfig::backgroundAcceleration = 0.05f;

float CConfig::MovingLegsSpeed = 0.0f;

int CConfig::CurrentTimerValue = 0;

HWND CConfig::Hwnd;
