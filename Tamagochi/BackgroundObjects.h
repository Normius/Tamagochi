#pragma once

#include "Config.h"
//TO DO: �������� �����, ������� ����� ��������� � ���� ��� �������� ������� ���� � �������������� � �������� �������

// ----------------------------- ����� ������ ��� --------------------------------------
class CBackgroundObjects
{
public:
    //virtual void Move();
};


// ----------------------------- ����� ����� (�����������, ���������) ----------------------------------------------
class CBird : public CBackgroundObjects
{
public:
    CBird();

    void Draw(HDC hdc, RECT& paintArea);
    void Redraw();
    void Move(float maxSpeed);

    float pos_X;
    float pos_Y;

private:
    void DrawBird(HDC hdc);

    void DrawUpWing(HDC hdc);

    void DrawDownWing(HDC hdc);

    void MoveWings(HDC hdc);

    const int upWingHeight = 23;
    const int downWingHeight = 27;
    const int width = 46;

    int height;

    float flyingSpeed;

    bool upWing;

    RECT birdRect;
    RECT prevBirdRect;
};
// -----------------------------------------------------------------------------------


// ----------------------------- ����� ������ (�����������, ���������) ----------------------------------------------
class CCactus : public CBackgroundObjects
{
public:
    CCactus();

    void Draw(HDC hdc, RECT& paintArea);

    int pos_X;
    int pos_Y;

    //RECT cloudRect{};
    //RECT prevCloudRect{};
};
// -----------------------------------------------------------------------------------


// ----------------------------- ����� ������ (������� ������ ����) ----------------------------------------------
class CRoadLevel : public CBackgroundObjects
{
public:
    CRoadLevel();

    void Draw(HDC hdc, RECT& paintArea);

    int pos_X;
    int pos_Y;

private:
    void DrawRoad(HDC hdc, RECT& paintArea);
    void DrawPit(HDC hdc, RECT& paintArea, int offset_x);
    void DrawBump(HDC hdc, RECT& paintArea, int offset_x);
    void DrawRocks(HDC hdc, RECT& paintArea, int offset_x, int offset_y);
};
// -----------------------------------------------------------------------------------


// ----------------------------- ����� ������ (������� ������ ����) ----------------------------------------------
class CCloud : public CBackgroundObjects
{
public:
    CCloud();

    void Draw(HDC hdc, RECT& paintArea);

    int pos_X;
    int pos_Y;

    //RECT cloudRect{};
    //RECT prevCloudRect{};
};
// -----------------------------------------------------------------------------------
