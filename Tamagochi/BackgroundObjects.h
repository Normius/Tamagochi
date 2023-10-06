#pragma once

#include "Config.h"

// ----------------------------- Класс задний фон --------------------------------------
class CBackgroundObjects
{
public:
    virtual void Draw(HDC hdc, RECT& paintArea) = 0;
    virtual void Clear(HDC hdc, RECT& paintArea) = 0;
    virtual void Redraw() = 0;
    virtual void Activate() = 0;
    virtual void Deactivate() = 0;
    virtual void Move(float maxSpeed) = 0;
    
    static constexpr float startSpeed = 10.0f;  //Начальная скорость объектов заднего плана
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
    static constexpr float minDistanceBetweenCollisionObjects = 300.0f; //Минимальная дистанция от точки появления объекта, при которой можно выпускать следующий объект(чтобы не шли подряд)
    static unsigned int CollisionObjectsActiveCount; //Текущее количество активных объектов (на экране)
};
// -----------------------------------------------------------------------------------


// ----------------------------- Класс Птица (препятствие, противник) ----------------------------------------------
class CBird : public CCollisionObjects
{
public:
    CBird();

    void Draw(HDC hdc, RECT& paintArea) override;
    void Clear(HDC hdc, RECT& paintArea) override;
    void Redraw() override;
    void Activate() override;
    void Deactivate() override;
    void Move(float maxSpeed) override;
    bool CheckHit(RECT* dinosaurCollisionRects, int rectsAmount) override;
    bool CheckActive() override;
    float GetPos_X() override;
    float GetBirdSpeed();
    void TestActivate(float pos_x, float pos_y);

private:
    void DrawUpWingBird(HDC hdc);
    void DrawDownWingBird(HDC hdc);
    void ChangeWings(bool upwing);
    void MoveWings(HDC hdc);
    void UpdateDrawRgnPoints();
    void UpdateCollisionRgnPoints();

    static constexpr float startPos_X = 800.0f;
    static constexpr float startPos_Y = 350.0f;
    static constexpr int upWingHeight = 23;
    static constexpr int downWingHeight = 27;
    static constexpr int width = 46;
    static constexpr unsigned int birdPointsAmount = 22;

    float pos_X, pos_Y;
    int rgnPos_X, rgnPos_Y;
    int height;
    float birdSpeed;
    bool upWing; //крыло вверх = true, крыло вниз = false
    bool active; //true - отображается на экране и двигается/ false - деактивирован, ушёл за рамку экрана и ждёт активации
    POINT currentBirdPoints[birdPointsAmount];
    POINT prevBirdPoints[birdPointsAmount];
    HRGN currentPolyRgn, prevPolyRgn; //Многоугольные регионы для проверки столкновения
    HRGN currentRectRgn, prevRectRgn; //Прямоугольные регионы для задания области перерисовки
};
// -----------------------------------------------------------------------------------


// ----------------------------- Класс Кактус (препятствие, противник) ----------------------------------------------
class CCactus : public CCollisionObjects
{
public:
    CCactus();

    void Draw(HDC hdc, RECT& paintArea) override;
    void Clear(HDC hdc, RECT& paintArea) override;
    void Redraw() override;
    void Activate() override;
    void Deactivate() override;
    void Move(float maxSpeed) override;
    bool CheckHit(RECT* dinosaurCollisionRects, int rectsAmount) override;
    bool CheckActive() override;
    float GetPos_X() override;
    
    void TestActivate(float pos_x, float pos_y);

private:
    void UpdateDrawRgnPoints();
    void UpdateCollisionRgnPoints();

    static constexpr float startPos_X = 800.0f;
    static constexpr float startPos_Y = 350.0f;
    static constexpr int height = 48;
    static constexpr int width = 22;
    static constexpr unsigned int cactusPointsAmount = 22;

    float pos_X, pos_Y;
    int rgnPos_X, rgnPos_Y;
    bool active; //true - отображается на экране и двигается/ false - деактивирован, ушёл за рамку экрана и ждёт активации
    POINT currentCactusPoints[cactusPointsAmount];
    POINT prevCactusPoints[cactusPointsAmount];
    HRGN currentPolyRgn, prevPolyRgn; //Многоугольные регионы для проверки столкновения
    HRGN prevRectRgn, currentRectRgn; //Прямоугольные регионы для задания области перерисовки
};
// -----------------------------------------------------------------------------------

// ----------------------------- Класс дорога (фоновый задний план) ----------------------------------------------
class CRoadLine:public CBackgroundObjects
{
public:
    CRoadLine();
    void Draw(HDC hdc, RECT& paintArea) override;
    void Clear(HDC hdc, RECT& paintArea) override;
    void Redraw() override;
    void Activate() override;
    void Deactivate() override;
    void Move(float maxSpeed) override;
    
private:
    static constexpr float pos_X = 0.0f;
    static constexpr float pos_Y = 386.0f;
    static constexpr int lineHeight = 1; //высота линии дороги
    static constexpr int lineWidth = CConfig::rightBorder; //ширина линии дороги (не домножаем на SizeScale, так как рисуется на ширину всего экрана)
    RECT currentRect, prevRect;
};
// -----------------------------------------------------------------------------------

// ----------------------------- Класс камней (штрихов) на дороге (фоновый задний план) ----------------------------------------------
class CRoadStones:public CBackgroundObjects
{
public:
    CRoadStones();
    void Draw(HDC hdc, RECT& paintArea) override;
    void Clear(HDC hdc, RECT& paintArea) override;
    void Redraw() override;
    void Activate() override;
    void Deactivate() override;
    void Move(float maxSpeed) override;

    bool CheckActive();
    float GetPos_X();
    void FirstActivate();

private:
    static constexpr float startPos_X = 10.0f;
    static constexpr float startPos_Y = 388.0f;
    static constexpr float restartPos_X = 800.0f;
    static constexpr int stonesHeight = 1; //высота камня дороги
    static constexpr int maxStonesHeight = 7;
    static constexpr int stonesWidth = 791; //ширина всех камней на дороге

    float pos_X, pos_Y;
    bool active; //true - отображается на экране и двигается/ false - деактивирован, ушёл за рамку экрана и ждёт активации
    RECT currentRect, prevRect;
};
// -----------------------------------------------------------------------------------


// ----------------------------- Класс ямы на дороге (фоновый задний план) ----------------------------------------------
class CRoadBump : public CBackgroundObjects
{
public:
    CRoadBump();
    void Draw(HDC hdc, RECT& paintArea) override;
    void Clear(HDC hdc, RECT& paintArea) override;
    void Redraw() override;
    void Activate() override;
    void Deactivate() override;
    void Move(float maxSpeed) override;
    
    bool CheckActive();
    float GetPos_X();
    void SetFirstBumpType(bool );
    void TestActivate();

private:
    void DrawPit(HDC hdc, RECT& paintArea, float offset_x);
    void DrawBump(HDC hdc, RECT& paintArea, float offset_x);

    static constexpr float pos_Y = 383.0f;
    static constexpr float restartPos_X = 800.0f;
    static constexpr int height = 7; //высота ямы и глубина кочки
    static constexpr int width = 44; //ширина ямы и кочки

    float pos_X;
    bool active; //true - отображается на экране и двигается/ false - деактивирован, ушёл за рамку экрана и ждёт активации
    bool twoPitsBumpType; //Определяет тип неровности на дороге (true - 2 кочки, false - кочка и яма)
    RECT currentRect, prevRect;
};
// -----------------------------------------------------------------------------------


// ----------------------------- Класс Облако (фоновый задний план) ----------------------------------------------
class CCloud : public CBackgroundObjects
{
public:
    CCloud();
    void Draw(HDC hdc, RECT& paintArea) override;
    void Clear(HDC hdc, RECT& paintArea) override;
    void Redraw() override;
    void Activate() override;
    void Deactivate() override;
    void Move(float maxSpeed) override;

    bool CheckActive();
    void FirstActivate();
    void UpdateDrawRgnPoints();
    
private:
    static constexpr float restartPos_X = 800.0f;
    static constexpr float startPos_Y = 200.0f;
    static constexpr int width = 58;
    static constexpr int height = 16;
    static constexpr int pointsAmount = 22;
    static const float cloudsSpeed; //У облака своя скорость, увеличенная на 5.0f относительно других объектов

    float pos_X, pos_Y;
    bool active; //true - отображается на экране и двигается/ false - деактивирован, ушёл за рамку экрана и ждёт активации
    POINT cloudPoints[pointsAmount];
    RECT currentRect, prevRect;
};
// -----------------------------------------------------------------------------------