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
    //virtual bool CheckHit(float dinoPos_x, float dinopos_Y, int dinoHeight, int dinoWidth) = 0;
    virtual bool CheckHit(RECT* dinosaurCollisionRects, int rectsAmount) = 0;
    virtual bool CheckActive() = 0;

    static constexpr unsigned int maxCollisionObjectsActive = 2; //������������ ���������� �������� �������� (�� ������)
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

    bool CheckHit(RECT* dinosaurCollisionRects, int rectsAmount) override;
    bool CheckActive() override;

    void Activate() override;

    void TestActivate(float pos_x, float pos_y);

    static constexpr float startPos_X = 800.0f;
    static constexpr float startPos_Y = 130.0f;

    float pos_X;
    float pos_Y;

    bool active; //true - ������������ �� ������ � ���������/ false - �������������, ���� �� ����� ������ � ��� ���������
    
private:
    void DrawBird(HDC hdc);
    void DrawUpWing(HDC hdc);
    void DrawDownWing(HDC hdc);
    void MoveWings(HDC hdc);

    static constexpr int upWingHeight = 23;
    static constexpr int downWingHeight = 27;
    static constexpr int width = 46;

    static constexpr unsigned int upWingPointsAmount = 22;
    static constexpr unsigned int downWingPointsAmount = 22;

    HRGN currentBirdRgn;

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

    bool CheckHit(RECT* dinosaurCollisionRects, int rectsAmount) override;
    bool CheckActive() override;

    void TestActivate(float pos_x, float pos_y);

    static constexpr float startPos_X = 800.0f;
    static constexpr float startPos_Y = 150.0f;

    float pos_X;
    float pos_Y;

    bool active; //true - ������������ �� ������ � ���������/ false - �������������, ���� �� ����� ������ � ��� ���������

private:
    static constexpr int height = 48;
    static constexpr int width = 22;
    static constexpr unsigned int cactusPointsAmount = 22;

    HRGN currentCactusRgn;

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

    static constexpr float pos_X = 0.0f;
    static constexpr float pos_Y = 186.0f;

    static constexpr int lineHeight = 1; //������ ����� ������
    static constexpr int lineWidth = CConfig::rightBorder; //������ ����� ������ (�� ��������� �� SizeScale, ��� ��� �������� �� ������ ����� ������)

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

    static constexpr float startPos_X = 10.0f;
    static constexpr float startPos_Y = 188.0f;
    static constexpr float restartPos_X = 800.0f;
    
    static constexpr int stonesHeight = 1; //������ ����� ������
    static constexpr int maxStonesHeight = 7;
    static constexpr int stonesWidth = 10; //������ ����� ������

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

    static constexpr float pos_Y = 183.0f;
    static constexpr float restartPos_X = 800.0f;

    float pos_X;

    bool active; //true - ������������ �� ������ � ���������/ false - �������������, ���� �� ����� ������ � ��� ���������
    bool firstBumpType; //���������� ��� ���������� �� ������ (true - 2 �����, false - ����� � ���)
    
private:
    void DrawPit(HDC hdc, RECT& paintArea, float offset_x);
    void DrawBump(HDC hdc, RECT& paintArea, float offset_x);

    static constexpr int height = 7; //������ ��� � ������� �����
    static constexpr int width = 44; //������ ��� � �����

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

    static constexpr float restartPos_X = 800.0f;
    static constexpr float startPos_Y = 0.0f;

    static constexpr int width = 58;
    static constexpr int height = 16;

    float pos_X;
    float pos_Y;

    bool active; //true - ������������ �� ������ � ���������/ false - �������������, ���� �� ����� ������ � ��� ���������

    static const float cloudsSpeed;
private:
    RECT cloudRect;
    RECT prevCloudRect;
};
// -----------------------------------------------------------------------------------
