#include "RoadLevel.h"

// ----------------------------- Класс задний фон --------------------------------------
void CBackground::MoveLegs(HWND hwnd)
{
    //// TO DO
    //prevDinoRect = dinoRect;
    //
    //DinoPos_X += DinoStep_X * DinoSpeed;
    ////DinoSpeed++;
    //
    //dinoRect.left = DinoPos_X;
    //dinoRect.top = DinoPos_Y;
    //dinoRect.right = dinoRect.left + DinoWidth * CConfig::SizeScale;
    //dinoRect.bottom = dinoRect.top + DinoHeight * CConfig::SizeScale;
    //
    //InvalidateRect(hwnd, &dinoRect, TRUE);
    //InvalidateRect(hwnd, &prevDinoRect, TRUE);
}

// ----------------------------- Класс дорога (фоновый задний план) --------------------------------------
CRoadLevel::CRoadLevel()
    :pos_X(0), pos_Y(80 * CConfig::SizeScale), RoadLevelPen(0), RoadLevelBrush(0)
{
}

void CRoadLevel::Init()
{
    RoadLevelPen = CreatePen(PS_SOLID, 0, RGB(19, 30, 24));

    RoadLevelBrush = CreateSolidBrush(RGB(19, 30, 24));
}

void CRoadLevel::Draw(HDC hdc, RECT& paintArea)
{
    DrawRoad(hdc, paintArea);
    DrawPit(hdc, paintArea, 10);
    DrawBump(hdc, paintArea, 40);
    DrawRocks(hdc, paintArea, 10, 15);
}

void CRoadLevel::DrawRoad(HDC hdc, RECT& paintArea)
{
    SelectObject(hdc, RoadLevelPen);
    SelectObject(hdc, RoadLevelBrush);

    //Контур дороги
    Rectangle(hdc, pos_X, pos_Y + 6 * CConfig::SizeScale, pos_X + 200 * CConfig::SizeScale, pos_Y + 8 * CConfig::SizeScale);
}

void CRoadLevel::DrawRocks(HDC hdc, RECT& paintArea, int offset_x, int offset_y)
{
    SelectObject(hdc, RoadLevelPen);
    SelectObject(hdc, RoadLevelBrush);

    int randomoffsetbetweenrocks_x = 5;
    int randomoffsetbetweenrocks_y = 5;
    //Камни на дороге
    Rectangle(hdc, pos_X + (10 + offset_x) * CConfig::SizeScale, pos_Y + (13 + offset_y) * CConfig::SizeScale, pos_X + (12 + offset_x) * CConfig::SizeScale, pos_Y + (15 + offset_y) * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (10 + offset_x + randomoffsetbetweenrocks_x) * CConfig::SizeScale, pos_Y + (13 + offset_y) * CConfig::SizeScale, pos_X + (13 + offset_x + randomoffsetbetweenrocks_x) * CConfig::SizeScale, pos_Y + (15 + offset_y) * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (10 + offset_x) * CConfig::SizeScale, pos_Y + (13 + offset_y + randomoffsetbetweenrocks_y) * CConfig::SizeScale, pos_X + (14 + offset_x) * CConfig::SizeScale, pos_Y + (15 + offset_y + randomoffsetbetweenrocks_y) * CConfig::SizeScale);
}

void CRoadLevel::DrawPit(HDC hdc, RECT& paintArea, int offset_x)
{
    //Яма

    //Рисуем пропуски фоновые
    SelectObject(hdc, CConfig::backgroundPen);
    SelectObject(hdc, CConfig::backgroundBrush);

    Rectangle(hdc, pos_X + (1 + offset_x) * CConfig::SizeScale, pos_Y + 6 * CConfig::SizeScale, pos_X + (15 + offset_x) * CConfig::SizeScale, pos_Y + 9 * CConfig::SizeScale);

    SelectObject(hdc, RoadLevelPen);
    SelectObject(hdc, RoadLevelBrush);

    Rectangle(hdc, pos_X + offset_x * CConfig::SizeScale, pos_Y + 7 * CConfig::SizeScale, pos_X + (2 + offset_x) * CConfig::SizeScale, pos_Y + 9 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (1 + offset_x) * CConfig::SizeScale, pos_Y + 8 * CConfig::SizeScale, pos_X + (3 + offset_x) * CConfig::SizeScale, pos_Y + 10 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (2 + offset_x) * CConfig::SizeScale, pos_Y + 9 * CConfig::SizeScale, pos_X + (14 + offset_x) * CConfig::SizeScale, pos_Y + 11 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (13 + offset_x) * CConfig::SizeScale, pos_Y + 8 * CConfig::SizeScale, pos_X + (15 + offset_x) * CConfig::SizeScale, pos_Y + 10 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (14 + offset_x) * CConfig::SizeScale, pos_Y + 7 * CConfig::SizeScale, pos_X + (16 + offset_x) * CConfig::SizeScale, pos_Y + 9 * CConfig::SizeScale);
}

void CRoadLevel::DrawBump(HDC hdc, RECT& paintArea, int offset_x)
{
    //Рисуем пропуски фоновые
    SelectObject(hdc, CConfig::backgroundPen);
    SelectObject(hdc, CConfig::backgroundBrush);
    Rectangle(hdc, pos_X + (2 + offset_x) * CConfig::SizeScale, pos_Y + 6 * CConfig::SizeScale, pos_X + (15 + offset_x) * CConfig::SizeScale, pos_Y + 8 * CConfig::SizeScale);

    //Кочка
    SelectObject(hdc, RoadLevelPen);
    SelectObject(hdc, RoadLevelBrush);

    Rectangle(hdc, pos_X + (1 + offset_x) * CConfig::SizeScale, pos_Y + 4 * CConfig::SizeScale, pos_X + (3 + offset_x) * CConfig::SizeScale, pos_Y + 6 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (2 + offset_x) * CConfig::SizeScale, pos_Y + 3 * CConfig::SizeScale, pos_X + (4 + offset_x) * CConfig::SizeScale, pos_Y + 5 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (3 + offset_x) * CConfig::SizeScale, pos_Y + 2 * CConfig::SizeScale, pos_X + (14 + offset_x) * CConfig::SizeScale, pos_Y + 4 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (13 + offset_x) * CConfig::SizeScale, pos_Y + 3 * CConfig::SizeScale, pos_X + (15 + offset_x) * CConfig::SizeScale, pos_Y + 5 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (14 + offset_x) * CConfig::SizeScale, pos_Y + 4 * CConfig::SizeScale, pos_X + (16 + offset_x) * CConfig::SizeScale, pos_Y + 6 * CConfig::SizeScale);

    
}
// -----------------------------------------------------------------------------------