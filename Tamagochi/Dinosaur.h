#pragma once

#include "Config.h"
#include "StartPlatform.h"

//Перечисление состояний тела Дино (стоя или в присяде)
enum class EDinosaurLevelState: unsigned char
{
    StartLevel, //Начальный уровень для обучения, свободное передвижение и подсказки
    RestartRunLevel, //Состояние перед началом забега
    RunLevel, //Забег начался
    LoseRunLevel, //Проигрыш при столкновении с припятствием
    TestLevel, //Свободное передвижение влево и вправо
    Teleporting //Телепортация со стартовой платформы
};

enum class EDinosaurBodyState: unsigned char
{
    Standing,
    Crawling
};

//Перечисление состояний направления Дино (влево или вправо)
enum class EDinosaurDirectionState: unsigned char
{
    Right,
    Left,
};

//Перечисление состояний движения Дино (влево или вправо)
enum class EDinosaurMovingState: unsigned char
{
    Stop,
    MovingRight,
    MovingLeft
};

// ----------------------------- Класс персонажа Dino (главный персонаж)
class CDinosaur
{
public:
    CDinosaur();

    void Draw(HDC hdc, RECT& paintArea);
    void Clear(HDC hdc, RECT& paintArea);
    void Redraw();
    void SetBodyState(EDinosaurBodyState newstate);
    void SetLevelState(EDinosaurLevelState newstate);
    void MoveVertical(float maxSpeed);
    void CorrectVerticalEdgePosition();
    void MoveHorizontal(float maxSpeed);
    void CorrectHorizontalEdgePosition();
    void CheckHorizontalDirection(bool leftDirection, bool keyPress);
    void Jump();
    void SetDinoCollisionRects();
    void GravityFalling();
    void CorrectPositionWithStartPlatform(const CStartPlatform* startPlatform);
    void RestartLevel();
    bool ReadyForStartPlatfrom(const CStartPlatform* startPlatform);
    void SetVerticalSpeedForTeleporting();
    bool CheckDinosaurOnGround();

    static constexpr float maxSpeed_Y = 30.0f;
    static constexpr unsigned int collisionRectsAmount = 3;

    EDinosaurDirectionState DinosaurDirectionState;
    EDinosaurMovingState DinosaurMovingState;
    bool collision;
    bool onStartPlatform;
    RECT dinoCollisionRects[collisionRectsAmount];
    
private:
    void UpdateRgnPoints();
    void MoveLegsRight(HDC hdc);
    void MoveLegsLeft(HDC hdc);
    void ClearRightLegsBackground(HDC hdc);
    void ClearLeftLegsBackground(HDC hdc);
    void DrawRightStandingLegs(HDC hdc);
    void DrawLeftStandingLegs(HDC hdc);
    void DrawRightFirstStep(HDC hdc);
    void DrawLeftFirstStep(HDC hdc);
    void DrawRightSecondStep(HDC hdc);
    void DrawLeftSecondStep(HDC hdc);
    void DrawRightEye(HDC hdc);
    void DrawLeftEye(HDC hdc);
    void DrawRightStanding(HDC hdc);
    void DrawLeftStanding(HDC hdc);
    void DrawRightCrawling(HDC hdc);
    void DrawLeftCrawling(HDC hdc);

    static constexpr int standingHeight = 44;
    static constexpr int crawlingHeight = 26;
    static constexpr int standingWidth = 44;
    static constexpr int crawlingWidth = 60;
    static constexpr float startPos_X = 100.0f; //Стартовая позиция по X
    static constexpr int standingPos_Y = 350; //(Стартовая позиция по Y
    static constexpr int crawlingPos_Y = standingPos_Y + (standingHeight - crawlingHeight); //(Стартовая позиция по Y)
    static constexpr int maxJumpHeight = 80;
    static constexpr float maxSpeed_X = 10.0f;
    
    float pos_X, pos_Y;
    int rgnPos_X, rgnPos_Y;
    int height;
    int width;
    int onGroundLegsPos_Y; //Позиция ног на земле
    bool falling; //Нужна для того, чтобы персонаж падал на землю при прыжке с платформы
    float horizontalSpeed, verticalSpeed;   
    bool leftKeyDown, rightKeyDown; //состояния клавиш влево и вправо (== true - нажаты, == false - не нажаты)

    EDinosaurBodyState DinosaurBodyState;
    EDinosaurLevelState DinosaurLevelState;

    static constexpr unsigned int dinosaurBodyPointsAmount = 26; //Количество точек без ног, только тело для отрисовки тела (ноги рисуются прямоугольниками)
    static constexpr unsigned int dinosaurWithLegsPointsAmount = 29; //Количество точек вместе с ногами (последние точки) для установки региона перерисовки
    POINT currentDinosaurPoints[dinosaurWithLegsPointsAmount];
    POINT prevDinosaurPoints[dinosaurWithLegsPointsAmount];
    RECT currentRect, prevRect;
};
// -----------------------------------------------------------------------------------