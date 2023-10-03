#include "StartPlatform.h"

// ----------------------------- Класс Стартовая платформа ------------------------

//Конструктор
CStartPlatform::CStartPlatform()
    :pos_X(0), prevRect{ 0 }, currentRect{ 0 }
{
}
// -----------------------------------------------------------------------------------

// Метод отрисовки
void CStartPlatform::Draw(HDC hdc, RECT& paintArea)
{
    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    CConfig::mainBrightColor.SelectColor(hdc);

    //Верхняя часть (шляпка)
    RoundRect(hdc, pos_x, pos_y, pos_x + topWidth, pos_y + topHeight, 3, 3);

    //Нижняя часть
    Rectangle(hdc, pos_x + topWidth / 2 - downWidth / 2, pos_y + topHeight, pos_x + topWidth / 2 - downWidth / 2 + downWidth, pos_y + topHeight + downHeight);

    CConfig::secondPaleColor.SelectColor(hdc);

    //Разделение между частями
    Rectangle(hdc, pos_x + topWidth / 2 - downWidth / 2, pos_y + topHeight, pos_x + topWidth / 2 - downWidth / 2 + downWidth, pos_y + topHeight + 1);
}
// -----------------------------------------------------------------------------------

// Метод очистки
void CStartPlatform::Clear(HDC hdc, RECT& paintArea)
{
    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    CConfig::backgroundColor.SelectColor(hdc);

    //Верхняя часть (шляпка)
    RoundRect(hdc, pos_x, pos_y, pos_x + topWidth, pos_y + topHeight, 3, 3);

    //Нижняя часть
    Rectangle(hdc, pos_x + topWidth / 2 - downWidth / 2, pos_y + topHeight, pos_x + topWidth / 2 - downWidth / 2 + downWidth, pos_y + topHeight + downHeight);
}
// -----------------------------------------------------------------------------------

// Метод очистки
void CStartPlatform::Redraw()
{
    prevRect = currentRect;

    currentRect.left = static_cast<int>(pos_X);
    currentRect.top = static_cast<int>(pos_Y);
    currentRect.right = currentRect.left + topWidth;
    currentRect.bottom = currentRect.top + topHeight + downHeight;

    InvalidateRect(CConfig::Hwnd, &prevRect, FALSE);
    InvalidateRect(CConfig::Hwnd, &currentRect, FALSE);
}
// -----------------------------------------------------------------------------------