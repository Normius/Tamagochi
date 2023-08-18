﻿#pragma once

#include <Windows.h>

#include "BackgroundObjects.h"
#include "Dinosaur.h"
#include "Config.h"

//Перечисление типа клавиш, используемых в игре
enum class EKeyType: unsigned char
{
    LeftKey,
    RightKey,
    DownKey,
    UpKey,
    SpaceKey
};

//Перечисление игровых состояний
enum class EGameState: unsigned char
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

    int lastCloudTimerDisappear;
    int newCloudTimerDelay;

    EGameState GameState;

private:
    CDinosaur Dinosaur;
    CBird Bird;
    CCactus Cactus;
    CRoadLevel RoadLevel;

    CBackgroundObjects* BackgroundObjects[CConfig::MaxBackgroundObjects];

    CCloud Clouds[CConfig::MaxClouds];
};
// -----------------------------------------------------------------------------------