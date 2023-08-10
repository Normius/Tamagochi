#pragma once

#include <Windows.h>

#include "RoadLevel.h"
#include "Bird.h"
#include "Cactus.h"
#include "Cloud.h"
#include "Dinosaur.h"
#include "Config.h"

//Перечисление типа клавиш, используемых в игре
enum class EKeyType
{
    LeftKey,
    RightKey,
    DownKey,
    UpKey,
    SpaceKey
};

//Перечисление игровых состояний
enum class EGameState
{
    StartRunLevel, //Состояние перед началом забега
    RunLevel, //Забег начался
    LoseRunLevel, //Проигрыш при столкновении с припятствием
    FreeMovingLevel //Свободное передвижение влево и вправо
};

const int TimerId = WM_USER + 1; //ID таймера для работы ф-ции таймера в Main

// ----------------------------- Класс Engine ----------------------------------------------
class CEngine
{
public:
    CEngine();

    void InitEngine(HWND hwnd);
    void DrawFrame(HDC hdc, RECT& paintArea);
    int OnKey(EKeyType keyType, bool keyPress);
    int OnTimer(); 

    EGameState GameState;

private:
    CDinosaur Dinosaur;
    CCloud Cloud;
    CBird Bird;
    CCactus Cactus;
    CRoadLevel RoadLevel;


};
// -----------------------------------------------------------------------------------