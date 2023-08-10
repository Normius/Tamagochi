#pragma once

#include <Windows.h>

#include "BackgroundObjects.h"
#include "Dinosaur.h"
#include "Config.h"


enum EKeyType
{
    LeftKey,
    RightKey,
    DownKey,
    UpKey,
    SpaceKey
};

enum EGameState
{
    Starting,
    Playing,
    Pause,
    Gameover,
    Free
};

const int TimerId = WM_USER + 1;

// ----------------------------- Класс Engine ----------------------------------------------
class CEngine
{
public:
    CEngine();

    void InitEngine(HWND hwnd);
    void DrawFrame(HDC hdc, RECT& paintArea);
    int OnKeyDown(EKeyType keyType);
    int OnTimer();

private:
    static const int leftBorder = 0; //Границы с учётом отрисовки
    static const int rightBorder = 800;
    static const int topBorder = 0;
    static const int downBorder = 600;

    EGameState GameState;

    CDinosaur Dinosaur;
    CCloud Cloud;
    CBird Bird;
    CCactus Cactus;
    CRoadLevel RoadLevel;
};
///////////////////////////////////////////////////////////////////////////////////////////////