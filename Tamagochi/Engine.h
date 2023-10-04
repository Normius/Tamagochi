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
    StartLevel,
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
    float GetMaxSpeed();
    bool CheckCollisionObjectsDistance();
    bool CheckRoadBumpsDistance();
    void CheckCollisions();
    void FirstStartLevel();
    void RestartLevel();

    void MoveCollisionObjects();
    void ActivateCollisionObjects();
    void ActivateRoadBumps();
    void ActivateClouds();
    void ActivateRoadStones();

    const int TimerId; //ID таймера для работы ф-ции таймера в Main

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

private:
    CDinosaur Dinosaur;

    CBird Bird;

    //CCactus Cactuses[CConfig::MaxCactuses]; //Массив кактусов
    std::vector<CCactus> Cactuses; //Массив кактусов

    //CCollisionObjects* CollisionObjects[CConfig::MaxCollisionObjects]; //Массив указателей на объекты заднего плана с столкновениями(кактусы и птица)
    std::vector<CCollisionObjects*> CollisionObjects;
    std::vector<CBackgroundObjects*> BackgroundObjects;

    //CRoadStones RoadStones[CConfig::MaxRoadStones];
    //CRoadBump RoadBumps[CConfig::MaxRoadBumps];
    //CCloud Clouds[CConfig::MaxClouds]; //Массив облаков
    std::vector<CRoadStones> RoadStones;
    std::vector<CRoadBump> RoadBumps;
    std::vector<CCloud> Clouds; //Массив облаков
    
    CRoadLine RoadLine;

    CStartPlatform StartPlatform; //TO DO:!!! Динамически создавать в куче, чтобы удалить раньше, так как нужна только в начале
    CScoreboard Scoreboard;
    СControlTip ControlTip; //TO DO:!!! Динамически создавать в куче, чтобы удалить раньше, так как нужна только в начале
    CPopupTip PopupTip; //TO DO:!!! Динамически создавать в куче, чтобы удалить раньше, так как нужна только в начале
};
// -----------------------------------------------------------------------------------