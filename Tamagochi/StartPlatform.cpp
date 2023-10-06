#include "StartPlatform.h"

// ----------------------------- Класс Стартовая платформа ------------------------

//Конструктор
CStartPlatform::CStartPlatform()
    :pos_X(0), currentRect{ 0 }, prevRect{ 0 }
{
}

//Отрисовка
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

//Очистка
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

//Заказ перерисовки
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

//Установка стартовой позиции по Х случайным образом
void CStartPlatform::SetRandomPos_X()
{
    pos_X = static_cast<float>(CConfig::GetRandom(200, 700));
}

//Возврат позиции по Х
float CStartPlatform::GetPos_X() const
{
    return pos_X;
}

//Возврат верхней ширины платформы
int CStartPlatform::GetTopWidth() const
{
    return topWidth;
}

//Возврат нижней ширины платформы
int CStartPlatform::GetDownWidth() const
{
    return downWidth;
}