#pragma once

#include "Config.h"
// ----------------------------- Класс дорога (фоновый задний план) ----------------------------------------------
class CRoadLevel
{
public:
    CRoadLevel();

    void Draw(HDC hdc, RECT& paintArea);

    int pos_X;
    int pos_Y;

private:
    void DrawRoad(HDC hdc, RECT& paintArea);
    void DrawPit(HDC hdc, RECT& paintArea, int offset_x);
    void DrawBump(HDC hdc, RECT& paintArea, int offset_x);
    void DrawRocks(HDC hdc, RECT& paintArea, int offset_x, int offset_y);
};
// -----------------------------------------------------------------------------------
