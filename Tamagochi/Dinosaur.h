﻿#pragma once

#include "Config.h"
#include <cmath>

//Перечисление состояний тела Дино (стоя или в присяде)
enum class EDinosaurLevelState: unsigned char
{
    StartRunLevel, //Состояние перед началом забега
    RunLevel, //Забег начался
    LoseRunLevel, //Проигрыш при столкновении с припятствием
    FreeMovingLevel //Свободное передвижение влево и вправо
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
    MovingLeft,
};

// ----------------------------- Класс персонажа Dino (главный персонаж)
class CDinosaur
{
public:
    CDinosaur();

    void Draw(HDC hdc, RECT& paintArea);
    void Clear(HDC hdc, RECT& paintArea);
    void Redraw();
    void UpdateRgnPoints();
    void MoveLegsRight(HDC hdc);
    void MoveLegsLeft(HDC hdc);
    void SetBodyState(EDinosaurBodyState newstate);
    void SetLevelState(EDinosaurLevelState newstate);
    void CorrectVerticalEdgePosition();
    void MoveVertical(float maxSpeed);
    void CorrectHorizontalEdgePosition();
    void MoveHorizontal(float maxSpeed);
    void CheckHorizontalDirection(bool leftDirection, bool keyPress);
    void Jump();
    void DrawRightEye(HDC hdc);
    void SetDinoCollisionRects();

    static constexpr int StandingHeight = 44;
    static constexpr int CrawlingHeight = 26;
    static constexpr int StandingWidth = 44;
    static constexpr int CrawlingWidth = 60;
    static constexpr int StandingPos_Y = 150; //(Стартовая позиция по Y)
    static constexpr int CrawlingPos_Y = StandingPos_Y + (StandingHeight - CrawlingHeight); //(Стартовая позиция по Y)
    static constexpr int OnGroundLegsPos_Y = (StandingPos_Y + StandingHeight); //Позиция ног на земле (раньше было 150 - верх)
    static constexpr int MaxJumpHeight = 80; //last 70

    static constexpr float MaxSpeed_X = 10.0f;
    static constexpr float MaxSpeed_Y = 30.0f; //last 18.0f

    int height;
    int width;

    //unsigned int lastLegsChangeTimer;
    //unsigned int newChangeLegsDelay;
    //bool firstStep;

    float pos_X;
    float pos_Y;
    float horizontalSpeed;
    float verticalSpeed;

    int currentRgnPos_X;
    int currentRgnPos_Y;
    int prevRgnPos_X;
    int prevRgnPos_Y;
    
    bool collision;
    bool leftKeyDown, rightKeyDown; //состояния клавиш влево и вправо (== true - нажаты, == false - не нажаты)
        
    EDinosaurDirectionState DinosaurDirectionState;
    EDinosaurMovingState DinosaurMovingState;

    static constexpr unsigned int collisionRectsAmount = 3;
    
    RECT dinoCollisionRects[collisionRectsAmount];

private:
    void ClearRightLegsBackground(HDC hdc);
    void ClearLeftLegsBackground(HDC hdc);
    void DrawRightStandingLegs(HDC hdc);
    void DrawLeftStandingLegs(HDC hdc);
    void DrawRightFirstStep(HDC hdc);
    void DrawLeftFirstStep(HDC hdc);
    void DrawRightSecondStep(HDC hdc);
    void DrawLeftSecondStep(HDC hdc);
    
    void DrawLeftEye(HDC hdc);
    void DrawRightStanding(HDC hdc);
    void DrawLeftStanding(HDC hdc);
    void DrawRightCrawling(HDC hdc);
    void DrawLeftCrawling(HDC hdc);

    static constexpr unsigned int dinosaurBodyPointsAmount = 26; //Количество точек без ног, только тело для отрисовки тела (ноги рисуются прямоугольниками)
    static constexpr unsigned int dinosaurWithLegsPointsAmount = 29; //Количество точек вместе с ногами (последние точки) для установки региона перерисовки

    POINT currentDinosaurPoints[dinosaurWithLegsPointsAmount];
    POINT prevDinosaurPoints[dinosaurWithLegsPointsAmount];

    EDinosaurBodyState DinosaurBodyState;
    EDinosaurLevelState DinosaurLevelState;

    /*HRGN currentPolyRgn;
    HRGN prevPolyRgn;

    HRGN prevRectRgn;
    HRGN currentRectRgn;*/

    RECT currentRect;
    RECT prevRect;

    /*RECT dinoRect, prevDinoRect;*/
};
// -----------------------------------------------------------------------------------