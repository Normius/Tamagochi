#pragma once

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



// ----------------------------- Класс Engine ----------------------------------------------
class CEngine
{
public:
    CEngine();

    void InitEngine(HWND hwnd);
    void DrawFrame(HDC hdc, RECT& paintArea);
    int OnKey(EKeyType keyType, bool keyPress);
    int OnTimer();
    float GetMaxSpeed();
    bool CheckCollisionObjectsDistance();

    const int TimerId; //ID таймера для работы ф-ции таймера в Main

    int lastCloudTimerDisappear;
    int newCloudTimerDelay;

    int lastCollisionObjectTimerDisappear;
    int newCollisionObjectTimerDelay;

    int lastRoadBumpTimerDisappear;
    int newRoadBumpTimerDelay;

    float currentMaxObjectsSpeed;
    float objectRestDistance;

    EGameState GameState;

private:
    CDinosaur Dinosaur;

    CBird Bird;
    CCactus Cactuses[CConfig::MaxCactuses]; //Массив кактусов
    CCollisionObjects* CollisionObjects[CConfig::MaxCollisionObjects]; //Массив указателей на объекты заднего плана с столкновениями(кактусы и птица)

    CRoadLine RoadLine;
    CRoadStones RoadStones[CConfig::MaxRoadStones];
    CRoadBump RoadBumps[CConfig::MaxRoadBumps];
    CCloud Clouds[CConfig::MaxClouds]; //Массив облаков
    
    //CBackgroundObjects* BackgroundObjects[CConfig::MaxBackgroundObjects]; //Массив указателей на объекты заднего плана без столкновений(облака и дорога)
    
};
// -----------------------------------------------------------------------------------