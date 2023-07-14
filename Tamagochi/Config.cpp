#include "Config.h"

// ----------------------------- Класс Color ----------------------------------------------
CColor::CColor(unsigned char r, unsigned char g, unsigned char b)
	:R(r), G(g), B(b)
{
}


// ----------------------------- Класс Config ----------------------------------------------
const CColor CConfig::backgroundColor(97, 121, 107);
const CColor CConfig::mainColor(19, 30, 24);
const CColor CConfig::cloudColor(60, 75, 67);

int CConfig::CurrentTimerValue = 0;

HPEN CConfig::backgroundPen;
HBRUSH CConfig::backgroundBrush;

HWND CConfig::Hwnd;

void CConfig::InitColors()
{
	backgroundPen = CreatePen(PS_SOLID, 0, RGB(backgroundColor.R, backgroundColor.G, backgroundColor.B));
	backgroundBrush = CreateSolidBrush(RGB(backgroundColor.R, backgroundColor.G, backgroundColor.B));
}

