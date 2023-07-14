#include "Cloud.h"

// ----------------------------- Класс Облако на заднем плане ----------------------------------------------
CCloud::CCloud()
    :pos_X(90 * CConfig::SizeScale), pos_Y(30 * CConfig::SizeScale), cloudPen(0), cloudBrush(0)
{
}

void CCloud::Init()
{
    cloudPen = CreatePen(PS_SOLID, 0, RGB(60, 75, 67));

    cloudBrush = CreateSolidBrush(RGB(60, 75, 67));
}


void CCloud::Draw(HDC hdc, RECT& paintArea)
{
    //RECT intersectionRect; //Нужен для ф-ции проверки пересечения прямоугольников, в него сохраняется область пересечения или 0

    //if (!IntersectRect(&intersectionRect, &paintArea, &dinoRect))
    //{
    //    return;
    //}

    SelectObject(hdc, cloudPen);
    SelectObject(hdc, cloudBrush);

    //Тело
    Rectangle(hdc, pos_X, pos_Y, pos_X + 58 * CConfig::SizeScale, pos_Y + 16 * CConfig::SizeScale);

    //Фоновые пропуски
    SelectObject(hdc, CConfig::backgroundPen);
    SelectObject(hdc, CConfig::backgroundBrush);

    //Верхние края
    Rectangle(hdc, pos_X, pos_Y, pos_X + 6 * CConfig::SizeScale, pos_Y + 11 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 6 * CConfig::SizeScale, pos_Y, pos_X + 16 * CConfig::SizeScale, pos_Y + 7 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 16 * CConfig::SizeScale, pos_Y, pos_X + 20 * CConfig::SizeScale, pos_Y + 6 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 20 * CConfig::SizeScale, pos_Y, pos_X + 23 * CConfig::SizeScale, pos_Y + 4 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 23 * CConfig::SizeScale, pos_Y, pos_X + 25 * CConfig::SizeScale, pos_Y + 3 * CConfig::SizeScale);

    Rectangle(hdc, pos_X + 38 * CConfig::SizeScale, pos_Y, pos_X + 40 * CConfig::SizeScale, pos_Y + 2 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 40 * CConfig::SizeScale, pos_Y, pos_X + 43 * CConfig::SizeScale, pos_Y + 5 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 43 * CConfig::SizeScale, pos_Y, pos_X + 47 * CConfig::SizeScale, pos_Y + 6 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 47 * CConfig::SizeScale, pos_Y, pos_X + 49 * CConfig::SizeScale, pos_Y + 7 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 49 * CConfig::SizeScale, pos_Y, pos_X + 52 * CConfig::SizeScale, pos_Y + 8 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 51 * CConfig::SizeScale, pos_Y, pos_X + 55 * CConfig::SizeScale, pos_Y + 11 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 55 * CConfig::SizeScale, pos_Y, pos_X + 58 * CConfig::SizeScale, pos_Y + 13 * CConfig::SizeScale);

    //Внутри облака
    Rectangle(hdc, pos_X + 2 * CConfig::SizeScale, pos_Y + 13 * CConfig::SizeScale, pos_X + 54 * CConfig::SizeScale, pos_Y + 14 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 8 * CConfig::SizeScale, pos_Y + 9 * CConfig::SizeScale, pos_X + 49 * CConfig::SizeScale, pos_Y + 14 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 42 * CConfig::SizeScale, pos_Y + 8 * CConfig::SizeScale, pos_X + 46 * CConfig::SizeScale, pos_Y + 9 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 39 * CConfig::SizeScale, pos_Y + 7 * CConfig::SizeScale, pos_X + 42 * CConfig::SizeScale, pos_Y + 9 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 35 * CConfig::SizeScale, pos_Y + 8 * CConfig::SizeScale, pos_X + 39 * CConfig::SizeScale, pos_Y + 9 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 28 * CConfig::SizeScale, pos_Y + 2 * CConfig::SizeScale, pos_X + 35 * CConfig::SizeScale, pos_Y + 9 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 35 * CConfig::SizeScale, pos_Y + 3 * CConfig::SizeScale, pos_X + 37 * CConfig::SizeScale, pos_Y + 6 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 22 * CConfig::SizeScale, pos_Y + 6 * CConfig::SizeScale, pos_X + 23 * CConfig::SizeScale, pos_Y + 9 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 23 * CConfig::SizeScale, pos_Y + 5 * CConfig::SizeScale, pos_X + 25 * CConfig::SizeScale, pos_Y + 9 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 25 * CConfig::SizeScale, pos_Y + 4 * CConfig::SizeScale, pos_X + 28 * CConfig::SizeScale, pos_Y + 9 * CConfig::SizeScale);
}
// -----------------------------------------------------------------------------------