#pragma once

#include "Config.h"
//TO DO
// ----------------------------- Класс задний фон --------------------------------------
class CBackground
{
public:
    void MoveLegs(HWND hwnd);

private:
    RECT dinoRect{};
    RECT prevDinoRect{};
};

// ----------------------------- Класс дорога (фоновый задний план) ----------------------------------------------
class CRoadLevel
{
public:
    CRoadLevel();

    void Init();
    void Draw(HDC hdc, RECT& paintArea);

    int pos_X;
    int pos_Y;

    HPEN RoadLevelPen;
    HBRUSH RoadLevelBrush;

private:
    void DrawRoad(HDC hdc, RECT& paintArea);
    void DrawPit(HDC hdc, RECT& paintArea, int offset_x);
    void DrawBump(HDC hdc, RECT& paintArea, int offset_x);
    void DrawRocks(HDC hdc, RECT& paintArea, int offset_x, int offset_y);
};
