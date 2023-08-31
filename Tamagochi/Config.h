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
	static const float DinosaurConstPos_X;

	static float slowCurrentFrameValue; //Текущее значение кадра от начала игры с замедлением в 2 раза (+1 каждые 2 кадра). Используется для замедления анимации крыльев птицы и шагов Дино

	static unsigned int currentFrameValue; //Текущее значение кадра от начала игры

	static const CColor backgroundColor, mainBrightColor, secondPaleColor;

	static HWND Hwnd;

	static const int MaxClouds = 4;
	static const int MaxRoadStones = 2; //Количество маленьких камней на дороге
	static const int MaxRoadBumps = 2;
	static const int MaxRoadObjects = 1;
	static const int MaxBackgroundObjects = MaxClouds + MaxRoadObjects + MaxRoadStones + MaxRoadBumps;

	static const int MaxCactuses = 2;
	static const int MaxBirds = 1;
	static const int MaxCollisionObjects = MaxCactuses + MaxBirds; //(Всего создано 3 объекта, с которыми можно столкнуться (2 кактуса и 1 птица). Одновременно могут появится 2 из этих объектов
};
// -----------------------------------------------------------------------------------