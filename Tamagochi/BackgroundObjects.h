#pragma once

#include "Config.h"

// ----------------------------- Класс задний фон --------------------------------------
class CBackgroundObjects
{
public:
    virtual void Move(float maxSpeed) = 0;
    virtual void Activate() = 0; //Активирует объект для отображения на экране и анимации после того, как он был неактивен
    virtual void Draw(HDC hdc, RECT& paintArea) = 0;
    virtual void Redraw() = 0;
    virtual void Clear(HDC hdc, RECT& paintArea) = 0;

    static float speed; //Скорость прокрутки объектов заднего плана
};
// -----------------------------------------------------------------------------------


// ----------------------------- Класс проверки столкновений --------------------------------------
class CCollisionObjects : public CBackgroundObjects
{
public:
    virtual bool CheckHit(RECT* dinosaurCollisionRects, int rectsAmount) = 0;
    virtual bool CheckActive() = 0;
    virtual float GetPos_X() = 0;

    static constexpr unsigned int maxCollisionObjectsActive = 2; //Максимальное количество активных объектов (на экране)
    static constexpr float minDistanceBetweenCollisionObjects = 200.0f;
    static unsigned int CollisionObjectsActiveCount; //Текущее количество активных объектов (на экране)
};
// -----------------------------------------------------------------------------------

// ----------------------------- Класс Птица (препятствие, противник) ----------------------------------------------
class CBird : public CCollisionObjects
{
public:
    CBird();

    void Draw(HDC hdc, RECT& paintArea) override;
    void Redraw() override;
    void Move(float maxSpeed) override;
    void Clear(HDC hdc, RECT& paintArea) override;

    bool CheckHit(RECT* dinosaurCollisionRects, int rectsAmount) override;
    bool CheckActive() override;
    float GetPos_X() override;

    void Activate() override;

    void TestActivate(float pos_x, float pos_y);

    static constexpr float startPos_X = 800.0f;
    static constexpr float startPos_Y = 150.0f;

    float pos_X;
    float pos_Y;

    //unsigned int lastWingChangeTimer;
    //unsigned int newChangeWingDelay;

    bool active; //true - отображается на экране и двигается/ false - деактивирован, ушёл за рамку экрана и ждёт активации
    
private:
    void DrawBodyBird(HDC hdc);
    void ClearUpWing(HDC hdc);
    void ClearDownWing(HDC hdc);
    void DrawUpWingBird(HDC hdc);
    void DrawDownWingBird(HDC hdc);
    void MoveWings(HDC hdc);

    static constexpr int upWingHeight = 23 + 12;
    static constexpr int downWingHeight = 27;
    static constexpr int width = 46;

    static constexpr unsigned int bodyBirdPointsAmount = 16;
    static constexpr unsigned int wingsPointsAmount = 7;
    static constexpr unsigned int birdWithWingsPointsAmount = bodyBirdPointsAmount + wingsPointsAmount - 1;

    POINT bodyBirdPoints[bodyBirdPointsAmount];
    POINT wingsPoints[wingsPointsAmount];
    POINT birdWithWingsPoints[birdWithWingsPointsAmount];

    HRGN currentBirdRgn;
    HRGN prevBirdRgn;

    int height;

    bool upWing;

    RECT birdRect;
    RECT prevBirdRect;
};
// -----------------------------------------------------------------------------------


// ----------------------------- Класс Кактус (препятствие, противник) ----------------------------------------------
class CCactus : public CCollisionObjects
{
public:
    CCactus();

    void Move(float maxSpeed) override;
    void Draw(HDC hdc, RECT& paintArea) override;
    void Activate() override;
    void Redraw() override;
    void Clear(HDC hdc, RECT& paintArea) override;

    bool CheckHit(RECT* dinosaurCollisionRects, int rectsAmount) override;
    bool CheckActive() override;
    float GetPos_X() override;

    void TestActivate(float pos_x, float pos_y);

    static constexpr float startPos_X = 800.0f;
    static constexpr float startPos_Y = 150.0f;

    float pos_X;
    float pos_Y;

    bool active; //true - отображается на экране и двигается/ false - деактивирован, ушёл за рамку экрана и ждёт активации

private:
    static constexpr int height = 48;
    static constexpr int width = 22;

    
    static constexpr unsigned int cactusPointsAmount = 22;
    static POINT cactusPoints[cactusPointsAmount];

    HRGN currentCactusRgn;

    RECT cactusRect;
    RECT prevCactusRect;
};
// -----------------------------------------------------------------------------------

// ----------------------------- Класс дорога (фоновый задний план) ----------------------------------------------
class CRoadLine:public CBackgroundObjects
{
public:
    CRoadLine();
    void Move(float maxSpeed) override;
    void Draw(HDC hdc, RECT& paintArea) override;
    void Redraw() override;
    void Activate() override;
    void Clear(HDC hdc, RECT& paintArea) override;

    static constexpr float pos_X = 0.0f;
    static constexpr float pos_Y = 186.0f; //186

    static constexpr int lineHeight = 1; //высота линии дороги
    static constexpr int lineWidth = CConfig::rightBorder; //ширина линии дороги (не домножаем на SizeScale, так как рисуется на ширину всего экрана)

    bool active; //true - отображается на экране и двигается/ false - деактивирован, ушёл за рамку экрана и ждёт активации

private:
    RECT roadLineRect;
    RECT prevRoadLineRect;
};
// -----------------------------------------------------------------------------------

// ----------------------------- Класс камней (штрихов) на дороге (фоновый задний план) ----------------------------------------------
class CRoadStones:public CBackgroundObjects
{
public:
    CRoadStones();
    void Move(float maxSpeed) override;
    void Draw(HDC hdc, RECT& paintArea) override;
    void Redraw() override;
    void Activate() override;
    void Clear(HDC hdc, RECT& paintArea) override;

    void FirstActivate();

    static constexpr float startPos_X = 10.0f;
    static constexpr float startPos_Y = 188.0f;
    static constexpr float restartPos_X = 800.0f;
    
    static constexpr int stonesHeight = 1; //высота камня дороги
    static constexpr int maxStonesHeight = 7;
    static constexpr int stonesWidth = 10; //ширина камня дороги

    float pos_X;
    float pos_Y;

    bool active; //true - отображается на экране и двигается/ false - деактивирован, ушёл за рамку экрана и ждёт активации

private:
    RECT roadStonesRect;
    RECT prevRoadStonesRect;
};
// -----------------------------------------------------------------------------------


// ----------------------------- Класс ямы на дороге (фоновый задний план) ----------------------------------------------
class CRoadBump : public CBackgroundObjects
{
public:
    CRoadBump();
    void Move(float maxSpeed) override;
    void Draw(HDC hdc, RECT& paintArea) override;
    void Redraw() override;
    void Activate() override;
    void Clear(HDC hdc, RECT& paintArea) override;

    void TestActivate();

    static constexpr float pos_Y = 183.0f;
    static constexpr float restartPos_X = 800.0f;

    float pos_X;

    bool active; //true - отображается на экране и двигается/ false - деактивирован, ушёл за рамку экрана и ждёт активации
    bool firstBumpType; //Определяет тип неровности на дороге (true - 2 кочки, false - кочка и яма)
    
private:
    void DrawPit(HDC hdc, RECT& paintArea, float offset_x);
    void DrawBump(HDC hdc, RECT& paintArea, float offset_x);

    static constexpr int height = 7; //высота ямы и глубина кочки
    static constexpr int width = 44; //ширина ямы и кочки

    RECT bumpRect;
    RECT prevBumpRect;
};
// -----------------------------------------------------------------------------------


// ----------------------------- Класс Облако (фоновый задний план) ----------------------------------------------
class CCloud : public CBackgroundObjects
{
public:
    CCloud();

    void Move(float maxSpeed) override;
    void Activate() override;

    void Draw(HDC hdc, RECT& paintArea) override;
    void Redraw() override;
    void Clear(HDC hdc, RECT& paintArea) override;
    
    void FirstActivate();

    static constexpr float restartPos_X = 800.0f;
    static constexpr float startPos_Y = 0.0f;

    static constexpr int width = 58;
    static constexpr int height = 16;

    float pos_X;
    float pos_Y;

    bool active; //true - отображается на экране и двигается/ false - деактивирован, ушёл за рамку экрана и ждёт активации

    static const float cloudsSpeed;
private:
    RECT cloudRect;
    RECT prevCloudRect;
};
// -----------------------------------------------------------------------------------
