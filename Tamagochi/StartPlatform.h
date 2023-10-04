#pragma once

#include "Config.h"

// ----------------------------- Класс Облако (фоновый задний план) ----------------------------------------------
class CStartPlatform
{
public:
    CStartPlatform();

    void Draw(HDC hdc, RECT& paintArea);
    void Clear(HDC hdc, RECT& paintArea);
    void Redraw();

    float pos_X;
    static constexpr float pos_Y = 340.0;

    static constexpr int downHeight = 40;
    static constexpr int topHeight = 15;
    static constexpr int downWidth = 64;
    static constexpr int topWidth = 70;

    RECT prevRect;
    RECT currentRect;
};
// -----------------------------------------------------------------------------------
