#pragma once

#include "Config.h"

// ----------------------------- Класс Облако (фоновый задний план) ----------------------------------------------
class CCloud
{
public:
    CCloud();

    void Draw(HDC hdc, RECT& paintArea);

    int pos_X;
    int pos_Y;

    //RECT cloudRect{};
    //RECT prevCloudRect{};
};
// -----------------------------------------------------------------------------------
