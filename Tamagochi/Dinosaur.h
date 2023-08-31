﻿#pragma once

#include "Config.h"
#include <cmath>

//TO DO: Возможно объединить эти состояния в одно перечисление
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
    void Redraw();
    void MoveLegsRight(HDC hdc);
    void MoveLegsLeft(HDC hdc);
    void SetBodyState(EDinosaurBodyState state);
    void CorrectVerticalEdgePosition();
    void MoveVertical(float maxSpeed);
    void CorrectHorizontalEdgePosition();
    void MoveHorizontal(float maxSpeed);
    void CheckHorizontalDirection(bool leftDirection, bool keyPress);
    void Jump();
    void DrawRightEye(HDC hdc);
    static int count;
    static const int StandingHeight = 44;
    static const int CrawlingHeight = 26;
    static const int StandingWidth = 44;
    static const int CrawlingWidth = 60;
    static const int StandingPos_Y = 150 * CConfig::SizeScale; //(Стартовая позиция по Y)
    static const int CrawlingPos_Y = StandingPos_Y + (StandingHeight - CrawlingHeight); //(Стартовая позиция по Y)
    static const int OnGroundLegsPos_Y = (StandingPos_Y + StandingHeight) * CConfig::SizeScale; //Позиция ног на земле (раньше было 150 - верх)

    const int MaxJumpHeight = 80; //last 70

    int height;
    int width;
    const float MaxSpeed_X = 10.0f;
    const float MaxSpeed_Y = 20.0f; //last 18.0f

    float pos_X;
    float pos_Y;
    float horizontalSpeed;
    float verticalSpeed;

    bool collision;
    bool leftKeyDown, rightKeyDown; //состояния клавиш влево и вправо (== true - нажаты, == false - не нажаты)

    EDinosaurDirectionState DinosaurDirectionState;
    EDinosaurMovingState DinosaurMovingState;

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
    void DrawRightHead(HDC hdc);
    void DrawLeftHead(HDC hdc);
    void DrawRightCrawling(HDC hdc);
    void DrawLeftCrawling(HDC hdc);

    EDinosaurBodyState DinosaurBodyState;
    EDinosaurLevelState DinosaurLevelState;

    RECT dinoRect;
    RECT prevDinoRect;
};
// -----------------------------------------------------------------------------------