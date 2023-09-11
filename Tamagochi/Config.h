﻿#pragma once

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

	static constexpr int leftBorder = 0; //Границы с учётом отрисовки
	static constexpr int rightBorder = 800;
	static constexpr int topBorder = 0;
	static constexpr int downBorder = 600;
	static constexpr int FPS = 20;

	static constexpr int SizeScale = 1; //Целочисленный масштаб (При изменении масштаба, изменить также дробный FSizeScale)
	static constexpr float FSizeScale = 1.0f; //Дробный масштаб (При изменении масштаба, изменить также целочисленный )
	static constexpr float minShift = 1.0f;
	static constexpr float backgroundAcceleration = 0.05f;
	static constexpr float DinosaurConstPos_X = 100.0f;

	static float slowCurrentFrameValue; //Текущее значение кадра от начала игры с замедлением в 2 раза (+1 каждые 2 кадра). Используется для замедления анимации крыльев птицы и шагов Дино

	static unsigned int currentFrameValue; //Текущее значение кадра от начала игры

	static const CColor backgroundColor, mainBrightColor, secondPaleColor;

	static HWND Hwnd;

	static constexpr int MaxClouds = 4;
	static constexpr int MaxRoadStones = 2; //Количество маленьких камней на дороге
	static constexpr int MaxRoadBumps = 2;
	static constexpr int MaxRoadObjects = 1;
	static constexpr int MaxBackgroundObjects = MaxClouds + MaxRoadObjects + MaxRoadStones + MaxRoadBumps;

	static constexpr int MaxCactuses = 2;
	static constexpr int MaxBirds = 1;
	static constexpr int MaxCollisionObjects = MaxCactuses + MaxBirds; //(Всего создано 3 объекта, с которыми можно столкнуться (2 кактуса и 1 птица). Одновременно могут появится 2 из этих объектов
};
// -----------------------------------------------------------------------------------