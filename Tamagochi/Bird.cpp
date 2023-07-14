#include "Bird.h"

// ----------------------------- Класс птицы (противник) ----------------------------------------------
CBird::CBird()
    :pos_X(160 * CConfig::SizeScale), pos_Y(40 * CConfig::SizeScale), BirdPen(0), BirdBrush(0)
{
}

void CBird::Init()
{
    BirdPen = CreatePen(PS_SOLID, 0, RGB(19, 30, 24));

    BirdBrush = CreateSolidBrush(RGB(19, 30, 24));
}

void CBird::DrawBird(HDC hdc, RECT& paintArea)
{
    SelectObject(hdc, BirdPen);
    SelectObject(hdc, BirdBrush);

    //Тело
    Rectangle(hdc, pos_X + 13 * CConfig::SizeScale, pos_Y + 13 * CConfig::SizeScale, pos_X + 46 * CConfig::SizeScale, pos_Y + 23 * CConfig::SizeScale);

    //Голова
    Rectangle(hdc, pos_X, pos_Y + 7 * CConfig::SizeScale, pos_X + 13 * CConfig::SizeScale, pos_Y + 16 * CConfig::SizeScale);

    //Фоновые пропуски
    SelectObject(hdc, CConfig::backgroundPen);
    SelectObject(hdc, CConfig::backgroundBrush);

    //Голова
    Rectangle(hdc, pos_X, pos_Y + 7 * CConfig::SizeScale, pos_X + 8 * CConfig::SizeScale, pos_Y + 8 * CConfig::SizeScale);
    Rectangle(hdc, pos_X, pos_Y + 8 * CConfig::SizeScale, pos_X + 6 * CConfig::SizeScale, pos_Y + 10 * CConfig::SizeScale);
    Rectangle(hdc, pos_X, pos_Y + 10 * CConfig::SizeScale, pos_X + 4 * CConfig::SizeScale, pos_Y + 12 * CConfig::SizeScale);
    Rectangle(hdc, pos_X, pos_Y + 12 * CConfig::SizeScale, pos_X + 2 * CConfig::SizeScale, pos_Y + 14 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 11 * CConfig::SizeScale, pos_Y + 7 * CConfig::SizeScale, pos_X + 13 * CConfig::SizeScale, pos_Y + 10 * CConfig::SizeScale);

    //Тело
    Rectangle(hdc, pos_X + 13 * CConfig::SizeScale, pos_Y + 18 * CConfig::SizeScale, pos_X + 15 * CConfig::SizeScale, pos_Y + 20 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 13 * CConfig::SizeScale, pos_Y + 20 * CConfig::SizeScale, pos_X + 17 * CConfig::SizeScale, pos_Y + 22 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 13 * CConfig::SizeScale, pos_Y + 22 * CConfig::SizeScale, pos_X + 19 * CConfig::SizeScale, pos_Y + 24 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 31 * CConfig::SizeScale, pos_Y + 13 * CConfig::SizeScale, pos_X + 46 * CConfig::SizeScale, pos_Y + 15 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 33 * CConfig::SizeScale, pos_Y + 15 * CConfig::SizeScale, pos_X + 46 * CConfig::SizeScale, pos_Y + 17 * CConfig::SizeScale);

    //Хвост
    Rectangle(hdc, pos_X + 39 * CConfig::SizeScale, pos_Y + 19 * CConfig::SizeScale, pos_X + 46 * CConfig::SizeScale, pos_Y + 21 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 44 * CConfig::SizeScale, pos_Y + 21 * CConfig::SizeScale, pos_X + 46 * CConfig::SizeScale, pos_Y + 23 * CConfig::SizeScale);

    //Глаз
    Rectangle(hdc, pos_X + 7 * CConfig::SizeScale, pos_Y + 11 * CConfig::SizeScale, pos_X + 9 * CConfig::SizeScale, pos_Y + 12 * CConfig::SizeScale);
}

void CBird::DrawUpWing(HDC hdc, RECT& paintArea)
{
    SelectObject(hdc, BirdPen);
    SelectObject(hdc, BirdBrush);

    //Крыло
    Rectangle(hdc, pos_X + 15 * CConfig::SizeScale, pos_Y, pos_X + 17 * CConfig::SizeScale, pos_Y + 4 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 17 * CConfig::SizeScale, pos_Y + 1 * CConfig::SizeScale, pos_X + 19 * CConfig::SizeScale, pos_Y + 13 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 19 * CConfig::SizeScale, pos_Y + 3 * CConfig::SizeScale, pos_X + 21 * CConfig::SizeScale, pos_Y + 13 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 21 * CConfig::SizeScale, pos_Y + 5 * CConfig::SizeScale, pos_X + 23 * CConfig::SizeScale, pos_Y + 13 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 23 * CConfig::SizeScale, pos_Y + 7 * CConfig::SizeScale, pos_X + 25 * CConfig::SizeScale, pos_Y + 13 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 25 * CConfig::SizeScale, pos_Y + 9 * CConfig::SizeScale, pos_X + 27 * CConfig::SizeScale, pos_Y + 13 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 27 * CConfig::SizeScale, pos_Y + 11 * CConfig::SizeScale, pos_X + 29 * CConfig::SizeScale, pos_Y + 13 * CConfig::SizeScale);
}

void CBird::DrawDownWing(HDC hdc, RECT& paintArea)
{
    SelectObject(hdc, BirdPen);
    SelectObject(hdc, BirdBrush);

    //Крыло
    Rectangle(hdc, pos_X + 17 * CConfig::SizeScale, pos_Y + 22 * CConfig::SizeScale, pos_X + 19 * CConfig::SizeScale, pos_Y + 34 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 19 * CConfig::SizeScale, pos_Y + 23 * CConfig::SizeScale, pos_X + 21 * CConfig::SizeScale, pos_Y + 31 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 21 * CConfig::SizeScale, pos_Y + 23 * CConfig::SizeScale, pos_X + 23 * CConfig::SizeScale, pos_Y + 27 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 23 * CConfig::SizeScale, pos_Y + 23 * CConfig::SizeScale, pos_X + 25 * CConfig::SizeScale, pos_Y + 25 * CConfig::SizeScale);
}

void CBird::Draw(HDC hdc, RECT& paintArea)
{
    DrawBird(hdc, paintArea);
    DrawUpWing(hdc, paintArea);
    //DrawDownWing(hdc, paintArea);
}
// -----------------------------------------------------------------------------------