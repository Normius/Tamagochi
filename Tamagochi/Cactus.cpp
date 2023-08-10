#include "Cactus.h"

// ----------------------------- Класс Кактуса (препятствие) ----------------------------------------------

// ------------ Конструктор
CCactus::CCactus()
    :pos_X(60 * CConfig::SizeScale), pos_Y(150 * CConfig::SizeScale)
{

}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка
void CCactus::Draw(HDC hdc, RECT& paintArea)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    //Ствол кактуса
    Rectangle(hdc, pos_X + 8 * CConfig::SizeScale, pos_Y + 2 * CConfig::SizeScale, pos_X + 14 * CConfig::SizeScale, pos_Y + 48 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 10 * CConfig::SizeScale, pos_Y, pos_X + 12 * CConfig::SizeScale, pos_Y + 2 * CConfig::SizeScale);

    //Левая ветка кактуса
    Rectangle(hdc, pos_X + 3 * CConfig::SizeScale, pos_Y + 29 * CConfig::SizeScale, pos_X + 8 * CConfig::SizeScale, pos_Y + 31 * CConfig::SizeScale);
    Rectangle(hdc, pos_X, pos_Y + 15 * CConfig::SizeScale, pos_X + 3 * CConfig::SizeScale, pos_Y + 29 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 1 * CConfig::SizeScale, pos_Y + 13 * CConfig::SizeScale, pos_X + 2 * CConfig::SizeScale, pos_Y + 15 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 1 * CConfig::SizeScale, pos_Y + 29 * CConfig::SizeScale, pos_X + 4 * CConfig::SizeScale, pos_Y + 30 * CConfig::SizeScale);

    //Правая ветка кактуса
    Rectangle(hdc, pos_X + 14 * CConfig::SizeScale, pos_Y + 27 * CConfig::SizeScale, pos_X + 19 * CConfig::SizeScale, pos_Y + 29 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 19 * CConfig::SizeScale, pos_Y + 13 * CConfig::SizeScale, pos_X + 22 * CConfig::SizeScale, pos_Y + 27 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 20 * CConfig::SizeScale, pos_Y + 11 * CConfig::SizeScale, pos_X + 21 * CConfig::SizeScale, pos_Y + 13 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 19 * CConfig::SizeScale, pos_Y + 27 * CConfig::SizeScale, pos_X + 21 * CConfig::SizeScale, pos_Y + 28 * CConfig::SizeScale);

    //Левая ветка кактуса вариант 2
    //Rectangle(hdc, pos_X + 3 * CConfig::SizeScale, pos_Y + 29 - 6 * CConfig::SizeScale, pos_X + 8 * CConfig::SizeScale, pos_Y + 31 - 6 * CConfig::SizeScale);
    //Rectangle(hdc, pos_X, pos_Y + 15 - 6 * CConfig::SizeScale, pos_X + 3 * CConfig::SizeScale, pos_Y + 29 - 6 * CConfig::SizeScale);
    //Rectangle(hdc, pos_X + 1 * CConfig::SizeScale, pos_Y + 13 - 6 * CConfig::SizeScale, pos_X + 2 * CConfig::SizeScale, pos_Y + 15 - 6 * CConfig::SizeScale);
    //Rectangle(hdc, pos_X + 1 * CConfig::SizeScale, pos_Y + 29 - 6 * CConfig::SizeScale, pos_X + 4 * CConfig::SizeScale, pos_Y + 30 - 6 * CConfig::SizeScale);

    //Правая ветка кактуса вариант 2
    //Rectangle(hdc, pos_X + 14 * CConfig::SizeScale, pos_Y + 27 * CConfig::SizeScale, pos_X + 19 * CConfig::SizeScale, pos_Y + 29 * CConfig::SizeScale);
    //Rectangle(hdc, pos_X + 19 * CConfig::SizeScale, pos_Y + 13 * CConfig::SizeScale, pos_X + 22 * CConfig::SizeScale, pos_Y + 27 * CConfig::SizeScale);
    //Rectangle(hdc, pos_X + 20 * CConfig::SizeScale, pos_Y + 11 * CConfig::SizeScale, pos_X + 21 * CConfig::SizeScale, pos_Y + 13 * CConfig::SizeScale);
    //Rectangle(hdc, pos_X + 19 * CConfig::SizeScale, pos_Y + 27 * CConfig::SizeScale, pos_X + 21 * CConfig::SizeScale, pos_Y + 28 * CConfig::SizeScale);

    //Левая ветка кактуса вариант 2
    //Rectangle(hdc, pos_X + 3 * CConfig::SizeScale, pos_Y + 29 - 6 * CConfig::SizeScale, pos_X + 8 * CConfig::SizeScale, pos_Y + 31 - 6 * CConfig::SizeScale);
    //Rectangle(hdc, pos_X, pos_Y + 15 - 6 * CConfig::SizeScale, pos_X + 3 * CConfig::SizeScale, pos_Y + 29 - 6 * CConfig::SizeScale);
    //Rectangle(hdc, pos_X + 1 * CConfig::SizeScale, pos_Y + 13 - 6 * CConfig::SizeScale, pos_X + 2 * CConfig::SizeScale, pos_Y + 15 - 6 * CConfig::SizeScale);
    //Rectangle(hdc, pos_X + 1 * CConfig::SizeScale, pos_Y + 29 - 6 * CConfig::SizeScale, pos_X + 4 * CConfig::SizeScale, pos_Y + 30 - 6 * CConfig::SizeScale);

    //Правая ветка кактуса вариант 2
    //Rectangle(hdc, pos_X + 14 * CConfig::SizeScale, pos_Y + 27 * CConfig::SizeScale, pos_X + 19 * CConfig::SizeScale, pos_Y + 29 * CConfig::SizeScale);
    //Rectangle(hdc, pos_X + 19 * CConfig::SizeScale, pos_Y + 13 * CConfig::SizeScale, pos_X + 22 * CConfig::SizeScale, pos_Y + 27 * CConfig::SizeScale);
    //Rectangle(hdc, pos_X + 20 * CConfig::SizeScale, pos_Y + 11 * CConfig::SizeScale, pos_X + 21 * CConfig::SizeScale, pos_Y + 13 * CConfig::SizeScale);
    //Rectangle(hdc, pos_X + 19 * CConfig::SizeScale, pos_Y + 27 * CConfig::SizeScale, pos_X + 21 * CConfig::SizeScale, pos_Y + 28 * CConfig::SizeScale);
}
// -----------------------------------------------------------------------------------