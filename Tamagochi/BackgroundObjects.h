#pragma once

#include "Config.h"
//TO DO: �������� �����, ������� ����� ��������� � ���� ��� �������� ������� ���� � �������������� � �������� �������

// ----------------------------- ����� ������ ��� --------------------------------------
class CBackgroundObjects
{
public:
    CBackgroundObjects();

    virtual void Move() = 0; //TO DO: !!!������� ���� ����� � ����������� X, Y � startXpos ��� ��������� ��������� ��������!!!

    float speed;
};
// -----------------------------------------------------------------------------------


// ----------------------------- ����� ����� (�����������, ���������) ----------------------------------------------
class CBird : public CBackgroundObjects
{
public:
    CBird();

    void Draw(HDC hdc, RECT& paintArea);
    void Redraw();
    void Move() override;

    const float startPos_X = 500.0f;

    float pos_X;
    float pos_Y;

    bool visible;
    
private:
    void DrawBird(HDC hdc);

    void DrawUpWing(HDC hdc);

    void DrawDownWing(HDC hdc);

    void MoveWings(HDC hdc);

    const int upWingHeight = 23;
    const int downWingHeight = 27;
    const int width = 46;

    int height;

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
    void Move() override;
    void Draw(HDC hdc, RECT& paintArea);
    void Redraw();

    const float startPos_X = 300.0f;

    float pos_X;
    float pos_Y;

    bool visible;

private:
    const int height = 48;
    const int width = 22;

    RECT cactusRect;
    RECT prevCactusRect;
};
// -----------------------------------------------------------------------------------


// ----------------------------- ����� ������ (������� ������ ����) ----------------------------------------------
class CRoadLevel : public CBackgroundObjects
{
public:
    CRoadLevel();
    void Move() override;
    void Draw(HDC hdc, RECT& paintArea);
    void Redraw();

    const float startPos_X = 0.0f;

    float pos_X;
    float pos_Y;

private:
    void DrawRoad(HDC hdc, RECT& paintArea);
    void DrawPit(HDC hdc, RECT& paintArea, int offset_x);
    void DrawBump(HDC hdc, RECT& paintArea, int offset_x);
    void DrawRocks(HDC hdc, RECT& paintArea, int offset_x, int offset_y);

    const int height = 4; //������ ��� � ������� �����
    const int width = 14; //������ ��� � �����

    RECT roadRect;
    RECT prevRoadRect;
};
// -----------------------------------------------------------------------------------


// ----------------------------- ����� ������ (������� ������ ����) ----------------------------------------------
class CCloud : public CBackgroundObjects
{
public:
    CCloud();

    void Move() override;

    void Draw(HDC hdc, RECT& paintArea);
    void Redraw();
    void Init(int x, int y);

    const int width = 58;

    const float startPos_X = 800.0f;

    float pos_X;
    float pos_Y;

    bool visible;

private:
    const int height = 16;
    

    RECT cloudRect;
    RECT prevCloudRect;
};
// -----------------------------------------------------------------------------------
