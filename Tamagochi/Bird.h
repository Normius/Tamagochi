#pragma once

#include "Config.h"

// ----------------------------- Класс Птица (препятствие, противник) ----------------------------------------------
class CBird
{
public:
    CBird();

    void Draw(HDC hdc, RECT& paintArea);
    void Redraw();
    void Move(float maxSpeed);

    float pos_X;
    float pos_Y;

private:
    void DrawBird(HDC hdc);

    void DrawUpWing(HDC hdc);

    void DrawDownWing(HDC hdc);

    void MoveWings(HDC hdc);

    const int upWingHeight = 23;
    const int downWingHeight = 27;
    const int width = 46;

    int height;

    float flyingSpeed;

    bool upWing;

    RECT birdRect;
    RECT prevBirdRect;
};
// -----------------------------------------------------------------------------------
