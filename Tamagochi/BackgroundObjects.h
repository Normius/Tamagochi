#pragma once

#include "Config.h"
//TO DO: �������� �����, ������� ����� ��������� � ���� ��� �������� ������� ���� � �������������� � �������� �������

// ----------------------------- ����� ������ ��� --------------------------------------
class CBackgroundObjects
{
public:
    virtual void Move(float maxSpeed) = 0; //TO DO: !!!������� ���� ����� � ����������� X, Y � startXpos ��� ��������� ��������� ��������!!!
    virtual void Activate() = 0; //���������� ������ ��� ����������� �� ������ � �������� ����� ����, ��� �� ��� ���������
    virtual void Draw(HDC hdc, RECT& paintArea) = 0;
    virtual void Redraw() = 0;

    static float speed; //�������� ��������� �������� ������� �����
};
// -----------------------------------------------------------------------------------


// ----------------------------- ����� �������� ������������ --------------------------------------
class CCollisionObjects : public CBackgroundObjects
{
public:
    virtual bool CheckHit(float dinoPos_x, float dinopos_Y, int dinoHeight, int dinoWidth) = 0;
    virtual bool CheckActive() = 0;

    static const unsigned int maxCollisionObjectsActive = 2; //������������ ���������� �������� �������� (�� ������)
    static unsigned int CollisionObjectsActiveCount; //������� ���������� �������� �������� (�� ������)
};
// -----------------------------------------------------------------------------------

// ----------------------------- ����� ����� (�����������, ���������) ----------------------------------------------
class CBird : public CCollisionObjects
{
public:
    CBird();

    void Draw(HDC hdc, RECT& paintArea) override;
    void Redraw() override;
    void Move(float maxSpeed) override;

    bool CheckHit(float dinoPos_x, float dinopos_y, int dinoHeight, int dinoWidth) override;
    bool CheckActive() override;

    void Activate() override;

    void TestActivate(float pos_x, float pos_y);

    const float startPos_X = 800.0f;
    const float startPos_Y = 130.0f;

    float pos_X;
    float pos_Y;

    float restDistance;

    bool active; //true - ������������ �� ������ � ���������/ false - �������������, ���� �� ����� ������ � ��� ���������
    
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
class CCactus : public CCollisionObjects
{
public:
    CCactus();

    void Move(float maxSpeed) override;
    void Draw(HDC hdc, RECT& paintArea) override;
    void Activate() override;
    void Redraw() override;

    bool CheckHit(float dinoPos_x, float dinopos_y, int dinoHeight, int dinoWidth) override;
    bool CheckActive() override;

    void TestActivate(float pos_x, float pos_y);

    const float startPos_X = 800.0f;
    const float startPos_Y = 150.0f;

    float pos_X;
    float pos_Y;

    float restDistance;
    bool active; //true - ������������ �� ������ � ���������/ false - �������������, ���� �� ����� ������ � ��� ���������

private:
    const int height = 48;
    const int width = 22;

    RECT cactusRect;
    RECT prevCactusRect;
};
// -----------------------------------------------------------------------------------

// ----------------------------- ����� ������ (������� ������ ����) ----------------------------------------------
class CRoadLine:public CBackgroundObjects
{
public:
    CRoadLine();
    void Move(float maxSpeed) override;
    void Draw(HDC hdc, RECT& paintArea) override;
    void Redraw() override;
    void Activate() override;

    const float pos_X = 0.0f;
    const float pos_Y = 186.0f;

    const int lineHeight = 1; //������ ����� ������
    const int lineWidth = CConfig::rightBorder; //������ ����� ������ (�� ��������� �� SizeScale, ��� ��� �������� �� ������ ����� ������)

    bool active; //true - ������������ �� ������ � ���������/ false - �������������, ���� �� ����� ������ � ��� ���������

private:

    RECT roadLineRect;
    RECT prevRoadLineRect;
};
// -----------------------------------------------------------------------------------

// ----------------------------- ����� ������ (�������) �� ������ (������� ������ ����) ----------------------------------------------
class CRoadStones:public CBackgroundObjects
{
public:
    CRoadStones();
    void Move(float maxSpeed) override;
    void Draw(HDC hdc, RECT& paintArea) override;
    void Redraw() override;
    void Activate() override;

    void FirstActivate();

    const float startPos_X = 10.0f;
    const float startPos_Y = 188.0f;
    const float restartPos_X = 800.0f;

    const int stonesHeight = 1; //������ ����� ������
    const int maxStonesHeight = 7;
    const int stonesWidth = 10; //������ ����� ������

    float pos_X;
    float pos_Y;

    bool active; //true - ������������ �� ������ � ���������/ false - �������������, ���� �� ����� ������ � ��� ���������

private:
    RECT roadStonesRect;
    RECT prevRoadStonesRect;
};
// -----------------------------------------------------------------------------------


// ----------------------------- ����� ��� �� ������ (������� ������ ����) ----------------------------------------------
class CRoadBump : public CBackgroundObjects
{
public:
    CRoadBump();
    void Move(float maxSpeed) override;
    void Draw(HDC hdc, RECT& paintArea) override;
    void Redraw() override;
    void Activate() override;

    void TestActivate();

    const float pos_Y = 183.0f;
    const float restartPos_X = 800.0f;

    float pos_X;

    bool active; //true - ������������ �� ������ � ���������/ false - �������������, ���� �� ����� ������ � ��� ���������
    bool firstBumpType; //���������� ��� ���������� �� ������ (true - 2 �����, false - ����� � ���)
    
private:
    void DrawPit(HDC hdc, RECT& paintArea, float offset_x);
    void DrawBump(HDC hdc, RECT& paintArea, float offset_x);

    const int height = 7; //������ ��� � ������� �����
    const int width = 44; //������ ��� � �����

    RECT bumpRect;
    RECT prevBumpRect;
};
// -----------------------------------------------------------------------------------


// ----------------------------- ����� ������ (������� ������ ����) ----------------------------------------------
class CCloud : public CBackgroundObjects
{
public:
    CCloud();

    void Move(float maxSpeed) override;
    void Activate() override;

    void Draw(HDC hdc, RECT& paintArea) override;
    void Redraw() override;
    
    void FirstActivate();

    const float restartPos_X = 800.0f;
    const float startPos_Y = 0.0f;

    const int width = 58;
    const int height = 16;

    float pos_X;
    float pos_Y;

    bool active; //true - ������������ �� ������ � ���������/ false - �������������, ���� �� ����� ������ � ��� ���������

    static const float cloudsSpeed;
private:
    RECT cloudRect;
    RECT prevCloudRect;
};
// -----------------------------------------------------------------------------------
