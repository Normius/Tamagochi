#pragma once

#include "Config.h"

enum EDinosaurBodyState
{
    Standing,
    Crawling
};

enum EDinosaurDirectionState
{
    RightDirection,
    LeftDirection,
};

// ----------------------------- Класс персонажа Dino (главный персонаж) ----------------------------------------------
class CDinosaur
{
public:
    CDinosaur();

    void Init();
    void Draw(HDC hdc, RECT& paintArea);
    void RedrawDino();
    void MoveLegsRight(HDC hdc);
    void MoveLegsLeft(HDC hdc);

    static const int standingDinoHeight = 44;
    static const int crawlingDinoHeight = 44; //по факту 26

    static const int standingDinoWidth = 44;
    static const int crawlingDinoWidth = 60;

    EDinosaurBodyState DinosaurBodyState;
    EDinosaurDirectionState DinosaurDirectionState;

    int DinoHeight;
    int DinoWidth;
    int DinoPos_X;
    int DinoPos_Y;
    int DinoStep_X;
    int DinoSpeed;

private:
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
    void DrawRightStandingDino(HDC hdc);
    void DrawLeftStandingDino(HDC hdc);
    void DrawRightHead(HDC hdc, int pos_x, int pos_y);
    void DrawLeftHead(HDC hdc, int pos_x, int pos_y, int reverseOffset);
    void DrawRightCrawlingDino(HDC hdc, int pos_x, int pos_y);
    void DrawLeftCrawlingDino(HDC hdc, int pos_x, int pos_y, int reverseOffset);

    RECT dinoRect{};
    RECT prevDinoRect{};


    HPEN characterPen;
    HBRUSH characterBrush;
};
///////////////////////////////////////////////////////////////////////////////////////////////