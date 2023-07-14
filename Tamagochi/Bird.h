#pragma once

#include "Config.h"

// ----------------------------- Класс Птица (препятствие, противник) ----------------------------------------------
class CBird
{
public:
    CBird();

    void Init();
    void Draw(HDC hdc, RECT& paintArea);


    int pos_X;
    int pos_Y;


    //RECT cloudRect{};
    //RECT prevCloudRect{};


    HPEN BirdPen;
    HBRUSH BirdBrush;

private:
    void DrawBird(HDC hdc, RECT& paintArea);

    void DrawUpWing(HDC hdc, RECT& paintArea);

    void DrawDownWing(HDC hdc, RECT& paintArea);
};
////////////////////////////////////////////////////////////////////////////////////
