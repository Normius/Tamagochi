#pragma once

#include "Config.h"

// ----------------------------- Класс Кактус (препятствие, противник) ----------------------------------------------
class CCactus
{
public:
    CCactus();

    void Draw(HDC hdc, RECT& paintArea);

    int pos_X;
    int pos_Y;

    //RECT cloudRect{};
    //RECT prevCloudRect{};
};
// -----------------------------------------------------------------------------------
