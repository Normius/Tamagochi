#pragma once

#include <Windows.h>

// ----------------------------- Класс Color ----------------------------------------------
class CColor
{
public:
	CColor(unsigned char r, unsigned char g, unsigned char b);
	CColor(unsigned char r, unsigned char g, unsigned char b, int penWidth);

	void SelectColor(HDC hdc) const;
	int GetRGBColor() const;

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

	static constexpr float minShift = 1.0f;
	static constexpr float backgroundAcceleration = 0.035f;

	static float slowCurrentFrameValue; //Текущее значение кадра от начала игры с замедлением в 2 раза (+1 каждые 2 кадра). Используется для замедления анимации крыльев птицы и шагов Дино
	static unsigned int currentFrameValue; //Текущее значение кадра от начала игры

	static int score; //Количество очков в забеге

	static const CColor backgroundColor, mainBrightColor, secondPaleColor, paleCloudColor;

	static HWND Hwnd;

	static constexpr int MaxClouds = 4;
	static constexpr int MaxRoadStones = 2; //Количество маленьких камней на дороге
	static constexpr int MaxRoadBumps = 2;
	static constexpr int MaxRoadObjects = 1;

	static constexpr int MaxCactuses = 2;
	static constexpr int MaxBirds = 1;
	static constexpr int MaxCollisionObjects = MaxCactuses + MaxBirds; //(Всего создано 3 объекта, с которыми можно столкнуться (2 кактуса и 1 птица). Одновременно могут появится 2 из этих объектов
};
// -----------------------------------------------------------------------------------