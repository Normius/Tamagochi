#include "RoadLevel.h"

// ----------------------------- Класс дорога (фоновый задний план) --------------------------------------

// ------------ Конструктор
CRoadLevel::CRoadLevel()
    :pos_X(0), pos_Y(180 * CConfig::SizeScale)
{
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка всего
void CRoadLevel::Draw(HDC hdc, RECT& paintArea)
{
    DrawRoad(hdc, paintArea);
    DrawPit(hdc, paintArea, 10);
    DrawBump(hdc, paintArea, 40);
    DrawRocks(hdc, paintArea, 10, 15);
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка линии дороги
void CRoadLevel::DrawRoad(HDC hdc, RECT& paintArea)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    //Контур дороги
    Rectangle(hdc, pos_X, pos_Y + 6 * CConfig::SizeScale, pos_X + 200 * CConfig::SizeScale, pos_Y + 7 * CConfig::SizeScale);
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка камней (штрихи ниже дороги)
void CRoadLevel::DrawRocks(HDC hdc, RECT& paintArea, int offset_x, int offset_y)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    int randomoffsetbetweenrocks_x = 5;
    int randomoffsetbetweenrocks_y = 5;
    //Камни на дороге
    Rectangle(hdc, pos_X + (10 + offset_x) * CConfig::SizeScale, pos_Y + (13 + offset_y) * CConfig::SizeScale, pos_X + (12 + offset_x) * CConfig::SizeScale, pos_Y + (15 + offset_y) * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (10 + offset_x + randomoffsetbetweenrocks_x) * CConfig::SizeScale, pos_Y + (13 + offset_y) * CConfig::SizeScale, pos_X + (13 + offset_x + randomoffsetbetweenrocks_x) * CConfig::SizeScale, pos_Y + (15 + offset_y) * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (10 + offset_x) * CConfig::SizeScale, pos_Y + (13 + offset_y + randomoffsetbetweenrocks_y) * CConfig::SizeScale, pos_X + (14 + offset_x) * CConfig::SizeScale, pos_Y + (15 + offset_y + randomoffsetbetweenrocks_y) * CConfig::SizeScale);
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка ямы
void CRoadLevel::DrawPit(HDC hdc, RECT& paintArea, int offset_x)
{
    //Яма

    //Рисуем пропуски фоновые
    CConfig::backgroundColor.SelectColor(hdc);

    Rectangle(hdc, pos_X + (1 + offset_x) * CConfig::SizeScale, pos_Y + 6 * CConfig::SizeScale, pos_X + (14 + offset_x) * CConfig::SizeScale, pos_Y + 7 * CConfig::SizeScale);

    CConfig::mainBrightColor.SelectColor(hdc);

    Rectangle(hdc, pos_X + offset_x * CConfig::SizeScale, pos_Y + 7 * CConfig::SizeScale, pos_X + (2 + offset_x) * CConfig::SizeScale, pos_Y + 8 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (1 + offset_x) * CConfig::SizeScale, pos_Y + 8 * CConfig::SizeScale, pos_X + (3 + offset_x) * CConfig::SizeScale, pos_Y + 9 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (2 + offset_x) * CConfig::SizeScale, pos_Y + 9 * CConfig::SizeScale, pos_X + (13 + offset_x) * CConfig::SizeScale, pos_Y + 10 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (12 + offset_x) * CConfig::SizeScale, pos_Y + 8 * CConfig::SizeScale, pos_X + (14 + offset_x) * CConfig::SizeScale, pos_Y + 9 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (13 + offset_x) * CConfig::SizeScale, pos_Y + 7 * CConfig::SizeScale, pos_X + (15 + offset_x) * CConfig::SizeScale, pos_Y + 8 * CConfig::SizeScale);
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка кочки
void CRoadLevel::DrawBump(HDC hdc, RECT& paintArea, int offset_x)
{
    //Рисуем пропуски фоновые
    CConfig::backgroundColor.SelectColor(hdc);

    Rectangle(hdc, pos_X + (2 + offset_x) * CConfig::SizeScale, pos_Y + 6 * CConfig::SizeScale, pos_X + (14 + offset_x) * CConfig::SizeScale, pos_Y + 7 * CConfig::SizeScale);

    //Кочка
    CConfig::mainBrightColor.SelectColor(hdc);

    Rectangle(hdc, pos_X + (1 + offset_x) * CConfig::SizeScale, pos_Y + 5 * CConfig::SizeScale, pos_X + (3 + offset_x) * CConfig::SizeScale, pos_Y + 6 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (2 + offset_x) * CConfig::SizeScale, pos_Y + 4 * CConfig::SizeScale, pos_X + (4 + offset_x) * CConfig::SizeScale, pos_Y + 5 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (3 + offset_x) * CConfig::SizeScale, pos_Y + 3 * CConfig::SizeScale, pos_X + (13 + offset_x) * CConfig::SizeScale, pos_Y + 4 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (12 + offset_x) * CConfig::SizeScale, pos_Y + 4 * CConfig::SizeScale, pos_X + (14 + offset_x) * CConfig::SizeScale, pos_Y + 5 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (13 + offset_x) * CConfig::SizeScale, pos_Y + 5 * CConfig::SizeScale, pos_X + (15 + offset_x) * CConfig::SizeScale, pos_Y + 6 * CConfig::SizeScale);
}
// -----------------------------------------------------------------------------------