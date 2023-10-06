#pragma once

#include <Windows.h>
#include <cmath>
#include <vector>

#include "BackgroundObjects.h"
#include "Dinosaur.h"
#include "GameInterface.h"


//Перечисление типа клавиш, используемых в игре
enum class EKeyType: unsigned char
{
    LeftKey,
    RightKey,
    DownKey,
    UpKey,
    SpaceKey,
    ActionKey_E
};

//Перечисление игровых состояний
enum class EGameState: unsigned char
{
    StartLevel, //Начальный уровень для обучения, свободное передвижение и подсказки
    RestartRunLevel, //Состояние перед началом забега
    RunLevel, //Забег начался
    LoseRunLevel, //Проигрыш при столкновении с припятствием
    TestLevel, //Свободное передвижение влево и вправо
    TeleportingDinosaur //Телепортация со стартовой платформы в начале игры
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

    const int TimerId; //ID таймера для работы ф-ции таймера в Main

private:
    float GetMaxSpeed();
    void CheckCollisions();
    bool CheckCollisionObjectsDistance();
    bool CheckRoadBumpsDistance();
    void ActivateCollisionObjects();
    void ActivateRoadBumps();
    void ActivateClouds();
    void ActivateRoadStones();
    void FirstStartLevel();
    void RestartLevel();
    void MoveDinosaurWithCollisionObjects();
    
    unsigned int lastCloudTimerDisappear;
    unsigned int newCloudTimerDelay;
    unsigned int lastCollisionObjectTimerDisappear;
    unsigned int newCollisionObjectTimerDelay;
    unsigned int lastRoadBumpTimerDisappear;
    unsigned int newRoadBumpTimerDelay;
    float currentMaxObjectsSpeed;
    float objectRestDistance;
    bool clearStartObjects;

    EGameState GameState;

    CDinosaur Dinosaur;
    CBird Bird;
    std::vector<CCactus> Cactuses;
    std::vector<CCollisionObjects*> CollisionObjects; //Массив указателей на базовые классы для вызова виртуальных ф-ций у объектов столкновений
    std::vector<CRoadStones> RoadStones;
    std::vector<CRoadBump> RoadBumps;
    std::vector<CCloud> Clouds; //Массив облаков
    CRoadLine RoadLine;
    std::vector<CBackgroundObjects*> BackgroundObjects; //Массив указателей на базовые классы для вызова виртуальных ф-ций у объектов заднего плана

    CScoreboard Scoreboard;
    CPopupTip PopupTip;
    CStartPlatform* StartPlatform; //Выделяем памят в куче динамически
    СControlTip* ControlTip; //Выделяем памят в куче динамически
};
// -----------------------------------------------------------------------------------