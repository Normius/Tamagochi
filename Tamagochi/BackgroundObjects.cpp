#include "BackgroundObjects.h"

// ----------------------------- Класс задний фон ------------------------------------

float CBackgroundObjects::speed = CBackgroundObjects::startSpeed;
// -----------------------------------------------------------------------------------


// ----------------------------- Класс объекты столкновений ------------------------------------

unsigned int CCollisionObjects::CollisionObjectsActiveCount = 0;
// -----------------------------------------------------------------------------------


// ----------------------------- Класс птицы (противник) -----------------------------

//Конструктор
CBird::CBird()
    :pos_X(startPos_X), pos_Y(startPos_Y), rgnPos_X(0), rgnPos_Y(0), height(upWingHeight), birdSpeed(0), upWing(true), active(false),
     currentBirdPoints{ 0 }, prevBirdPoints{ 0 }, currentPolyRgn{ 0 }, prevPolyRgn{ 0 }, currentRectRgn{ 0 }, prevRectRgn{ 0 }
{
}

//Отрисовка птицы полностью
void CBird::Draw(HDC hdc, RECT& paintArea)
{
    if (!RectInRegion(currentPolyRgn, &paintArea))
        return;

    MoveWings(hdc);
}

//Очистка предыдущего положения птицы
void CBird::Clear(HDC hdc, RECT& paintArea)
{
    if (!RectInRegion(prevPolyRgn, &paintArea))
        return;

    CConfig::backgroundColor.SelectColor(hdc);
    Polygon(hdc, prevBirdPoints, birdPointsAmount);
}

//Перерисовка персонажа в новых координатах
void CBird::Redraw()
{
    if (active == false)
        return;

    if (static_cast<int>(CConfig::slowCurrentFrameValue) % 2 == 0)
        ChangeWings(true);
    else
        ChangeWings(false);

    for (int i = 0; i < birdPointsAmount; ++i)
        prevBirdPoints[i] = currentBirdPoints[i];

    rgnPos_X = static_cast<int>(pos_X);
    rgnPos_Y = static_cast<int>(pos_Y);

    prevPolyRgn = currentPolyRgn;

    UpdateDrawRgnPoints();

    currentPolyRgn = CreatePolygonRgn(currentBirdPoints, birdPointsAmount, 2);

    prevRectRgn = currentRectRgn;

    currentRectRgn = CreateRectRgn(rgnPos_X, rgnPos_Y, rgnPos_X + width, rgnPos_Y + height);

    InvalidateRgn(CConfig::Hwnd, prevRectRgn, FALSE);
    InvalidateRgn(CConfig::Hwnd, currentRectRgn, FALSE);
}

//Делаем объект активным и помещаем в заданные координаты
void CBird::Activate()
{
    if (CCollisionObjects::CollisionObjectsActiveCount >= CCollisionObjects::maxCollisionObjectsActive)
        return;

    if (CConfig::currentFrameValue < CConfig::FPS * 10)
        return;

    active = true;
    CCollisionObjects::CollisionObjectsActiveCount++; //Увеличиваем счётчик количества активных объектов

    pos_X = startPos_X - static_cast<float>(width);
    pos_Y = startPos_Y - 50.0f + 10.0f * static_cast<float>(CConfig::GetRandom(0, 5)); //Генерируем диапазон от 100 до 150: (100, 110) - безопасно стоя, (120, 130) - присесть или попробовать перепрыгнуть, (140-150) - только перепрыгивать
}

//Перемещаем объект в позицию за край экрана, где он деактивируется
void CBird::Deactivate()
{
    pos_X = static_cast<float>(CConfig::leftBorder - birdSpeed - width);
}

//Смещение объекта со временем
void CBird::Move(float maxSpeed)
{
    if (active == false)
        return;

    birdSpeed = CBackgroundObjects::speed + 5.0f;
    float nextStep = birdSpeed / maxSpeed * CConfig::minShift;

    pos_X -= nextStep;

    if (static_cast<int>(pos_X) + static_cast<int>(birdSpeed) + width <= CConfig::leftBorder)
    {
        active = false; //Если объект уходит за границу экрана, деактивируем его
        CCollisionObjects::CollisionObjectsActiveCount--;
        return;
    }
}

//Проверка столкновения
bool CBird::CheckHit(RECT* dinosaurCollisionRects, int rectsAmount)
{
    if (active == false)
        return false;

    UpdateCollisionRgnPoints();

    prevPolyRgn = CreatePolygonRgn(prevBirdPoints, birdPointsAmount, 2);

    for (int i = 0; i < rectsAmount; ++i)
    {
        if (RectInRegion(prevPolyRgn, &dinosaurCollisionRects[i]) != 0)
            return true;
    }

    DeleteObject(prevPolyRgn);

    return false;
}

//Проверка активен ли объект (находится на экране)
bool CBird::CheckActive()
{
    return active;
}

//Возврат позиции по Х
float CBird::GetPos_X()
{
    return pos_X;
}

//Возвращает скорость птицы
float CBird::GetBirdSpeed()
{
    return birdSpeed;
}

//Активируем объект для проведения тестов
void CBird::TestActivate(float pos_x, float pos_y)
{
    if (CCollisionObjects::CollisionObjectsActiveCount >= CCollisionObjects::maxCollisionObjectsActive)
        return;

    active = true;
    CCollisionObjects::CollisionObjectsActiveCount++;

    pos_X = pos_x;
    pos_Y = pos_y;
}

//Отрисовка верхнего крыла
void CBird::DrawUpWingBird(HDC hdc)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    Polygon(hdc, currentBirdPoints, birdPointsAmount);

    //Фоновые пропуски
    CConfig::backgroundColor.SelectColor(hdc);

    //Глаз
    Rectangle(hdc, rgnPos_X + 7, rgnPos_Y + 11, rgnPos_X + 9, rgnPos_Y + 12);
}

//Отрисовка нижнего крыла
void CBird::DrawDownWingBird(HDC hdc)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    Polygon(hdc, currentBirdPoints, birdPointsAmount);

    //Фоновые пропуски
    CConfig::backgroundColor.SelectColor(hdc);

    //Глаз
    Rectangle(hdc, rgnPos_X + 7, rgnPos_Y + 4, rgnPos_X + 9, rgnPos_Y + 5);
}

//Смена крыльев при для анимации
void CBird::ChangeWings(bool upwing)
{
    if (upWing == upwing)
        return;

    if (upwing == true)
    {
        pos_Y -= 7.0f;
        height = upWingHeight;
    }
    else
    {
        pos_Y += 7.0f;
        height = downWingHeight;
    }

    upWing = upwing;
}

//Анимация крыльев
void CBird::MoveWings(HDC hdc)
{        
    if (upWing == true)
        DrawUpWingBird(hdc);
    else
        DrawDownWingBird(hdc);
}

//Обновление точек для создания регионов и проверки столкновений
void CBird::UpdateCollisionRgnPoints()
{
    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    //Используем набор предыдущих точек и предыдущего региона, чтобы не использовать дополнительный регион.
    //Они обновятся значениями текущего региона и его точек в методе Draw() для вызова перерисовки

    if (upWing == true)
    {
        prevBirdPoints[0] = { pos_x + 12, pos_y + 13 };
        prevBirdPoints[1] = { pos_x + 17, pos_y + 13 };
        prevBirdPoints[2] = { pos_x + 17, pos_y + 3 };
        prevBirdPoints[3] = { pos_x + 15, pos_y + 3 };
        prevBirdPoints[4] = { pos_x + 15, pos_y + 0 };
        prevBirdPoints[5] = { pos_x + 16, pos_y + 0 };
        prevBirdPoints[6] = { pos_x + 29, pos_y + 12 };
        prevBirdPoints[7] = { pos_x + 30, pos_y + 13 };
        prevBirdPoints[8] = { pos_x + 33, pos_y + 17 };
        prevBirdPoints[9] = { pos_x + 45, pos_y + 17 };
        prevBirdPoints[10] = { pos_x + 45, pos_y + 18 };
        prevBirdPoints[11] = { pos_x + 38, pos_y + 18 };
        prevBirdPoints[12] = { pos_x + 38, pos_y + 21 };
        prevBirdPoints[13] = { pos_x + 43, pos_y + 21 };
        prevBirdPoints[14] = { pos_x + 43, pos_y + 22 };
        prevBirdPoints[15] = { pos_x + 17, pos_y + 22 };
        prevBirdPoints[16] = { pos_x + 12, pos_y + 15 };
        prevBirdPoints[17] = { pos_x + 0, pos_y + 15 };
        prevBirdPoints[18] = { pos_x + 0, pos_y + 14 };
        prevBirdPoints[19] = { pos_x + 1, pos_y + 14 };
        prevBirdPoints[20] = { pos_x + 8, pos_y + 7 };
        prevBirdPoints[21] = { pos_x + 10, pos_y + 7 };
    }
    else
    {
        prevBirdPoints[0] = { pos_x + 12, pos_y + 6 };
        prevBirdPoints[1] = { pos_x + 30, pos_y + 6 };
        prevBirdPoints[2] = { pos_x + 33, pos_y + 10 };
        prevBirdPoints[3] = { pos_x + 45, pos_y + 10 };
        prevBirdPoints[4] = { pos_x + 45, pos_y + 11 };
        prevBirdPoints[5] = { pos_x + 38, pos_y + 11 };
        prevBirdPoints[6] = { pos_x + 38, pos_y + 14 };
        prevBirdPoints[7] = { pos_x + 43, pos_y + 14 };
        prevBirdPoints[8] = { pos_x + 43, pos_y + 15 };
        prevBirdPoints[9] = { pos_x + 24, pos_y + 15 };
        prevBirdPoints[10] = { pos_x + 24, pos_y + 17 };
        prevBirdPoints[11] = { pos_x + 19, pos_y + 23 };
        prevBirdPoints[12] = { pos_x + 18, pos_y + 23 };
        prevBirdPoints[13] = { pos_x + 18, pos_y + 26 };
        prevBirdPoints[14] = { pos_x + 17, pos_y + 26 };
        prevBirdPoints[15] = { pos_x + 17, pos_y + 15 };
        prevBirdPoints[16] = { pos_x + 12, pos_y + 8 };
        prevBirdPoints[17] = { pos_x + 0, pos_y + 8 };
        prevBirdPoints[18] = { pos_x + 0, pos_y + 7 };
        prevBirdPoints[19] = { pos_x + 1, pos_y + 7 };
        prevBirdPoints[20] = { pos_x + 8, pos_y + 0 };
        prevBirdPoints[21] = { pos_x + 10, pos_y + 0 };
    }
}

//Обновление точек для отрисовки в новой позиции
void CBird::UpdateDrawRgnPoints()
{
    if (upWing == true)
    {
        currentBirdPoints[0] = { rgnPos_X + 12, rgnPos_Y + 13 };
        currentBirdPoints[1] = { rgnPos_X + 17, rgnPos_Y + 13 };
        currentBirdPoints[2] = { rgnPos_X + 17, rgnPos_Y + 3 };
        currentBirdPoints[3] = { rgnPos_X + 15, rgnPos_Y + 3 };
        currentBirdPoints[4] = { rgnPos_X + 15, rgnPos_Y + 0 };
        currentBirdPoints[5] = { rgnPos_X + 16, rgnPos_Y + 0 };
        currentBirdPoints[6] = { rgnPos_X + 29, rgnPos_Y + 12 };
        currentBirdPoints[7] = { rgnPos_X + 30, rgnPos_Y + 13 };
        currentBirdPoints[8] = { rgnPos_X + 33, rgnPos_Y + 17 };
        currentBirdPoints[9] = { rgnPos_X + 45, rgnPos_Y + 17 };
        currentBirdPoints[10] = { rgnPos_X + 45, rgnPos_Y + 18 };
        currentBirdPoints[11] = { rgnPos_X + 38, rgnPos_Y + 18 };
        currentBirdPoints[12] = { rgnPos_X + 38, rgnPos_Y + 21 };
        currentBirdPoints[13] = { rgnPos_X + 43, rgnPos_Y + 21 };
        currentBirdPoints[14] = { rgnPos_X + 43, rgnPos_Y + 22 };
        currentBirdPoints[15] = { rgnPos_X + 17, rgnPos_Y + 22 };
        currentBirdPoints[16] = { rgnPos_X + 12, rgnPos_Y + 15 };
        currentBirdPoints[17] = { rgnPos_X + 0, rgnPos_Y + 15 };
        currentBirdPoints[18] = { rgnPos_X + 0, rgnPos_Y + 14 };
        currentBirdPoints[19] = { rgnPos_X + 1, rgnPos_Y + 14 };
        currentBirdPoints[20] = { rgnPos_X + 8, rgnPos_Y + 7 };
        currentBirdPoints[21] = { rgnPos_X + 10, rgnPos_Y + 7 };
    }
    else
    {
        currentBirdPoints[0] = { rgnPos_X + 12, rgnPos_Y + 6 };
        currentBirdPoints[1] = { rgnPos_X + 30, rgnPos_Y + 6 };
        currentBirdPoints[2] = { rgnPos_X + 33, rgnPos_Y + 10 };
        currentBirdPoints[3] = { rgnPos_X + 45, rgnPos_Y + 10 };
        currentBirdPoints[4] = { rgnPos_X + 45, rgnPos_Y + 11 };
        currentBirdPoints[5] = { rgnPos_X + 38, rgnPos_Y + 11 };
        currentBirdPoints[6] = { rgnPos_X + 38, rgnPos_Y + 14 };
        currentBirdPoints[7] = { rgnPos_X + 43, rgnPos_Y + 14 };
        currentBirdPoints[8] = { rgnPos_X + 43, rgnPos_Y + 15 };
        currentBirdPoints[9] = { rgnPos_X + 24, rgnPos_Y + 15 };
        currentBirdPoints[10] = { rgnPos_X + 24, rgnPos_Y + 17 };
        currentBirdPoints[11] = { rgnPos_X + 19, rgnPos_Y + 23 };
        currentBirdPoints[12] = { rgnPos_X + 18, rgnPos_Y + 23 };
        currentBirdPoints[13] = { rgnPos_X + 18, rgnPos_Y + 26 };
        currentBirdPoints[14] = { rgnPos_X + 17, rgnPos_Y + 26 };
        currentBirdPoints[15] = { rgnPos_X + 17, rgnPos_Y + 15 };
        currentBirdPoints[16] = { rgnPos_X + 12, rgnPos_Y + 8 };
        currentBirdPoints[17] = { rgnPos_X + 0, rgnPos_Y + 8 };
        currentBirdPoints[18] = { rgnPos_X + 0, rgnPos_Y + 7 };
        currentBirdPoints[19] = { rgnPos_X + 1, rgnPos_Y + 7 };
        currentBirdPoints[20] = { rgnPos_X + 8, rgnPos_Y + 0 };
        currentBirdPoints[21] = { rgnPos_X + 10, rgnPos_Y + 0 };
    }
}
// -----------------------------------------------------------------------------------


// -------------------------------------------------------------- Класс Кактуса (препятствие) ------------------------------------------------------------------------

//Конструктор
CCactus::CCactus()
    :pos_X(startPos_X), pos_Y(startPos_Y), rgnPos_X(0), rgnPos_Y(0), active(false), currentCactusPoints{ 0 }, prevCactusPoints{ 0 },
     currentPolyRgn{ 0 }, prevPolyRgn{ 0 }, prevRectRgn{ 0 }, currentRectRgn{ 0 }
{
}

//Отрисовка
void CCactus::Draw(HDC hdc, RECT& paintArea)
{
    if ( !RectInRegion(currentPolyRgn, &paintArea) )
        return;

    CConfig::mainBrightColor.SelectColor(hdc);

    Polygon(hdc, currentCactusPoints, cactusPointsAmount);
}

//Очистка
void CCactus::Clear(HDC hdc, RECT& paintArea)
{
    if ( !RectInRegion(prevPolyRgn, &paintArea) )
        return;

    CConfig::backgroundColor.SelectColor(hdc);

    Polygon(hdc, prevCactusPoints, cactusPointsAmount);
}

//Перерисовка персонажа в новых координатах
void CCactus::Redraw()
{
    if (active == false)
        return;

    for (int i = 0; i < cactusPointsAmount; ++i)
        prevCactusPoints[i] = currentCactusPoints[i];

    rgnPos_X = static_cast<int>(pos_X);
    rgnPos_Y = static_cast<int>(pos_Y);

    prevPolyRgn = currentPolyRgn;

    UpdateDrawRgnPoints(); //Обновляем точки многоугольника по новым координатам и на основе них создаём регион

    currentPolyRgn = CreatePolygonRgn(currentCactusPoints, cactusPointsAmount, 2);

    //Создаём прямоугольные регионы для запроса на перерисовку этой области (многоугольные полигоны не работают, запрашивается меньшая область перерисовки, остаются "следы")
    prevRectRgn = currentRectRgn;
    currentRectRgn = CreateRectRgn(rgnPos_X, rgnPos_Y, rgnPos_X + width, rgnPos_Y + height);

    InvalidateRgn(CConfig::Hwnd, prevRectRgn, FALSE);
    InvalidateRgn(CConfig::Hwnd, currentRectRgn, FALSE);
}

//Делаем объект активным и помещаем в заданные координаты
void CCactus::Activate()
{
    if (CCollisionObjects::CollisionObjectsActiveCount >= maxCollisionObjectsActive)
        return;

    active = true;
    CCollisionObjects::CollisionObjectsActiveCount++;

    pos_X = startPos_X - width;
    pos_Y = static_cast<float>(startPos_Y);
}

//Перемещаем объект в позицию за край экрана, где он деактивируется
void CCactus::Deactivate()
{
    pos_X = static_cast<float>(CConfig::leftBorder - CBackgroundObjects::speed - width);
}

//Смещение объекта со временем
void CCactus::Move(float maxSpeed)
{
    if (active == false)
        return;

    if (CBackgroundObjects::speed == 0.0f)
        return;

    float nextStep = CBackgroundObjects::speed / maxSpeed;

    pos_X -= nextStep;

    if (static_cast<int>(pos_X) + static_cast<int>(CBackgroundObjects::speed) + width <= CConfig::leftBorder)
    {
        active = false;
        CCollisionObjects::CollisionObjectsActiveCount--;
        return;
    }
}

//Проверка столкновения
bool CCactus::CheckHit(RECT* dinosaurCollisionRects, int rectsAmount)
{
    if (active == false)
        return false;

    UpdateCollisionRgnPoints();

    prevPolyRgn = CreatePolygonRgn(prevCactusPoints, cactusPointsAmount, 2);

    for (int i = 0; i < rectsAmount; ++i)
    {
        if (RectInRegion(prevPolyRgn, &dinosaurCollisionRects[i]) != 0)
            return true;
    }

    DeleteObject(prevPolyRgn);

    return false;
}

//Проверка активен ли объект (находится на экране)
bool CCactus::CheckActive()
{
    return active;
}

//Возврат позиции по Х
float CCactus::GetPos_X()
{
    return pos_X;
}

//Активируем объект для проведения тестов
void CCactus::TestActivate(float pos_x, float pos_y)
{
    if (CCollisionObjects::CollisionObjectsActiveCount >= CCollisionObjects::maxCollisionObjectsActive)
        return;

    active = true;
    CCollisionObjects::CollisionObjectsActiveCount++;

    pos_X = pos_x;
    pos_Y = pos_y;
}

//Обновление точек для создания регионов и проверки столкновений
void CCactus::UpdateCollisionRgnPoints()
{
    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    //Используем набор предыдущих точек и предыдущего региона, чтобы не использовать дополнительный регион.
    //Они обновятся значениями текущего региона и его точек в методе Draw() для вызова перерисовки
    prevCactusPoints[0] = { pos_x + 10, pos_y + 0 }; 
    prevCactusPoints[1] = { pos_x + 11, pos_y + 0 };
    prevCactusPoints[2] = { pos_x + 13, pos_y + 2 };
    prevCactusPoints[3] = { pos_x + 13, pos_y + 27 };
    prevCactusPoints[4] = { pos_x + 19, pos_y + 27 };
    prevCactusPoints[5] = { pos_x + 19, pos_y + 13 };
    prevCactusPoints[6] = { pos_x + 20, pos_y + 11 };
    prevCactusPoints[7] = { pos_x + 21, pos_y + 13 };
    prevCactusPoints[8] = { pos_x + 21, pos_y + 26 };
    prevCactusPoints[9] = { pos_x + 18, pos_y + 28 };
    prevCactusPoints[10] = { pos_x + 13, pos_y + 28 };
    prevCactusPoints[11] = { pos_x + 13, pos_y + 47 };
    prevCactusPoints[12] = { pos_x + 8, pos_y + 47 };
    prevCactusPoints[13] = { pos_x + 8, pos_y + 30 };
    prevCactusPoints[14] = { pos_x + 3, pos_y + 30 };
    prevCactusPoints[15] = { pos_x + 0, pos_y + 28 };
    prevCactusPoints[16] = { pos_x + 0, pos_y + 15 };
    prevCactusPoints[17] = { pos_x + 1, pos_y + 13 };
    prevCactusPoints[18] = { pos_x + 2, pos_y + 15 };
    prevCactusPoints[19] = { pos_x + 2, pos_y + 29 };
    prevCactusPoints[20] = { pos_x + 8, pos_y + 29 };
    prevCactusPoints[21] = { pos_x + 8, pos_y + 2 };
}

//Обновление точек для отрисовки в новой позиции
void CCactus::UpdateDrawRgnPoints()
{
    currentCactusPoints[0] = { rgnPos_X + 10, rgnPos_Y + 0 };
    currentCactusPoints[1] = { rgnPos_X + 11, rgnPos_Y + 0 };
    currentCactusPoints[2] = { rgnPos_X + 13, rgnPos_Y + 2 };
    currentCactusPoints[3] = { rgnPos_X + 13, rgnPos_Y + 27 };
    currentCactusPoints[4] = { rgnPos_X + 19, rgnPos_Y + 27 };
    currentCactusPoints[5] = { rgnPos_X + 19, rgnPos_Y + 13 };
    currentCactusPoints[6] = { rgnPos_X + 20, rgnPos_Y + 11 };
    currentCactusPoints[7] = { rgnPos_X + 21, rgnPos_Y + 13 };
    currentCactusPoints[8] = { rgnPos_X + 21, rgnPos_Y + 26 };
    currentCactusPoints[9] = { rgnPos_X + 18, rgnPos_Y + 28 };
    currentCactusPoints[10] = { rgnPos_X + 13, rgnPos_Y + 28 };
    currentCactusPoints[11] = { rgnPos_X + 13, rgnPos_Y + 47 };
    currentCactusPoints[12] = { rgnPos_X + 8, rgnPos_Y + 47 };
    currentCactusPoints[13] = { rgnPos_X + 8, rgnPos_Y + 30 };
    currentCactusPoints[14] = { rgnPos_X + 3, rgnPos_Y + 30 };
    currentCactusPoints[15] = { rgnPos_X + 0, rgnPos_Y + 28 };
    currentCactusPoints[16] = { rgnPos_X + 0, rgnPos_Y + 15 };
    currentCactusPoints[17] = { rgnPos_X + 1, rgnPos_Y + 13 };
    currentCactusPoints[18] = { rgnPos_X + 2, rgnPos_Y + 15 };
    currentCactusPoints[19] = { rgnPos_X + 2, rgnPos_Y + 29 };
    currentCactusPoints[20] = { rgnPos_X + 8, rgnPos_Y + 29 };
    currentCactusPoints[21] = { rgnPos_X + 8, rgnPos_Y + 2 };
}
// -----------------------------------------------------------------------------------


// ----------------------------- Класс линия дороги (фоновый задний план) ------------------

//Конструктор
CRoadLine::CRoadLine()
    :currentRect{}, prevRect{}
{
}

//Отрисовка всего
void CRoadLine::Draw(HDC hdc, RECT& paintArea)
{
    RECT intersectionRect; //Нужен для ф-ции проверки пересечения прямоугольников, в него сохраняется область пересечения или 0

    if (!IntersectRect(&intersectionRect, &paintArea, &currentRect))
        return;
    
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    //Контур дороги
    Rectangle(hdc, pos_x, pos_y, pos_x + lineWidth, pos_y + lineHeight);
}

//Очистка
void CRoadLine::Clear(HDC hdc, RECT& paintArea)
{
    return;
}

//Перерисовка в новых координатах
void CRoadLine::Redraw()
{
    prevRect = currentRect;

    currentRect.left = static_cast<int>(pos_X);
    currentRect.top = static_cast<int>(pos_Y);
    currentRect.right = currentRect.left + lineWidth; //Не домножаем на SizeScale, так как рисуем на весь экран
    currentRect.bottom = currentRect.top + lineHeight ;

    InvalidateRect(CConfig::Hwnd, &prevRect, FALSE);
    InvalidateRect(CConfig::Hwnd, &currentRect, FALSE);
}

//Делаем объект активным и помещаем в заданные координаты
void CRoadLine::Activate()
{
    return; //Не нужно ничего делать, объект не движется
}

//Перемещаем объект в позицию за край экрана, где он деактивируется
void CRoadLine::Deactivate()
{
    return; //Не нужно ничего делать, объект не движется
}

//Смещение объекта со временем
void CRoadLine::Move(float maxSpeed) //В отличие от других объектов, не смещаем линию дороги, а только перерисовываем на том же месте
{
    if (CBackgroundObjects::speed == 0.0f)
        return;

    Redraw(); 
}
// -----------------------------------------------------------------------------------


// ----------------------------- Класс камней (штрихов) на дороге (фоновый задний план) ------------------

//Конструктор
CRoadStones::CRoadStones()
    :pos_X(startPos_X), pos_Y(startPos_Y), active(false), currentRect{}, prevRect{}
{
}

//Отрисовка всего
void CRoadStones::Draw(HDC hdc, RECT& paintArea)
{
    RECT intersectionRect; //Нужен для ф-ции проверки пересечения прямоугольников, в него сохраняется область пересечения или 0

    if (!IntersectRect(&intersectionRect, &paintArea, &currentRect))
        return;

    
    CConfig::secondPaleColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    //Контур дороги
    Rectangle(hdc, pos_x, pos_y + 6, pos_x + 4, pos_y + 6 + stonesHeight);
    Rectangle(hdc, pos_x + 7, pos_y + 3, pos_x + 7 + 5, pos_y + 3 + stonesHeight);
    Rectangle(hdc, pos_x + 15, pos_y + 6, pos_x + 15 + 2, pos_y + 6 + stonesHeight);
    
    Rectangle(hdc, pos_x + 40, pos_y + 4, pos_x + 40 + 1, pos_y + 5 + stonesHeight);
    Rectangle(hdc, pos_x + 48, pos_y + 5, pos_x + 48 + 5, pos_y + 5 + stonesHeight);
    Rectangle(hdc, pos_x + 55, pos_y + 2, pos_x + 55 + 4, pos_y + 2 + stonesHeight);
    Rectangle(hdc, pos_x + 68, pos_y + 4, pos_x + 68 + 3, pos_y + 4 + stonesHeight);
    Rectangle(hdc, pos_x + 80, pos_y + 2, pos_x + 80 + 1, pos_y + 3 + stonesHeight);
    Rectangle(hdc, pos_x + 84, pos_y + 4, pos_x + 84 + 5, pos_y + 4 + stonesHeight);
    Rectangle(hdc, pos_x + 94, pos_y + 2, pos_x + 94 + 3, pos_y + 2 + stonesHeight);
    
    Rectangle(hdc, pos_x + 112, pos_y + 4, pos_x + 112 + 1, pos_y + 5 + stonesHeight);
    Rectangle(hdc, pos_x + 122, pos_y + 4, pos_x + 122 + 3, pos_y + 4 + stonesHeight);
    Rectangle(hdc, pos_x + 134, pos_y + 1, pos_x + 134 + 5, pos_y + 1 + stonesHeight);
    
    Rectangle(hdc, pos_x + 156, pos_y + 3, pos_x + 156 + 1, pos_y + 4 + stonesHeight);
    Rectangle(hdc, pos_x + 160, pos_y + 2, pos_x + 160 + 2, pos_y + 2 + stonesHeight);
    Rectangle(hdc, pos_x + 166, pos_y + 3, pos_x + 166 + 4, pos_y + 3 + stonesHeight);
    
    Rectangle(hdc, pos_x + 186, pos_y + 2, pos_x + 186 + 1, pos_y + 3 + stonesHeight);
    Rectangle(hdc, pos_x + 200, pos_y + 2, pos_x + 200 + 3, pos_y + 2 + stonesHeight);
    Rectangle(hdc, pos_x + 206, pos_y + 3, pos_x + 206 + 1, pos_y + 4 + stonesHeight);
    
    Rectangle(hdc, pos_x + 220, pos_y + 3, pos_x + 220 + 2, pos_y + 3 + stonesHeight);

    Rectangle(hdc, pos_x + 238, pos_y + 4, pos_x + 238 + 3, pos_y + 4 + stonesHeight);
    Rectangle(hdc, pos_x + 244, pos_y + 4, pos_x + 244 + 2, pos_y + 4 + stonesHeight);

    Rectangle(hdc, pos_x + 260, pos_y + 4, pos_x + 260 + 4, pos_y + 4 + stonesHeight);
    Rectangle(hdc, pos_x + 280, pos_y + 3, pos_x + 280 + 3, pos_y + 3 + stonesHeight);
    Rectangle(hdc, pos_x + 304, pos_y + 2, pos_x + 304 + 1, pos_y + 3 + stonesHeight);
    Rectangle(hdc, pos_x + 320, pos_y + 4, pos_x + 320 + 3, pos_y + 4 + stonesHeight);
    Rectangle(hdc, pos_x + 340, pos_y + 1, pos_x + 340 + 3, pos_y + 1 + stonesHeight);
    Rectangle(hdc, pos_x + 350, pos_y + 2, pos_x + 350 + 1, pos_y + 3 + stonesHeight);
    Rectangle(hdc, pos_x + 370, pos_y + 2, pos_x + 370 + 3, pos_y + 2 + stonesHeight);
    
    Rectangle(hdc, pos_x + 390, pos_y + 3, pos_x + 390 + 2, pos_y + 3 + stonesHeight);
    Rectangle(hdc, pos_x + 398, pos_y + 4, pos_x + 398 + 3, pos_y + 4 + stonesHeight);
    Rectangle(hdc, pos_x + 410, pos_y + 3, pos_x + 410 + 1, pos_y + 4 + stonesHeight);
    Rectangle(hdc, pos_x + 424, pos_y + 2, pos_x + 424 + 2, pos_y + 2 + stonesHeight);
    
    Rectangle(hdc, pos_x + 450, pos_y + 3, pos_x + 450 + 3, pos_y + 3 + stonesHeight);
    
    Rectangle(hdc, pos_x + 480, pos_y + 2, pos_x + 480 + 1, pos_y + 3 + stonesHeight);
    Rectangle(hdc, pos_x + 488, pos_y + 2, pos_x + 488 + 3, pos_y + 2 + stonesHeight);
    Rectangle(hdc, pos_x + 506, pos_y + 3, pos_x + 506 + 4, pos_y + 3 + stonesHeight);
    Rectangle(hdc, pos_x + 518, pos_y + 5, pos_x + 518 + 2, pos_y + 5 + stonesHeight);
    
    Rectangle(hdc, pos_x + 540, pos_y + 1, pos_x + 540 + 1, pos_y + 2 + stonesHeight);
    Rectangle(hdc, pos_x + 548, pos_y + 2, pos_x + 548 + 3, pos_y + 2 + stonesHeight);
    
    Rectangle(hdc, pos_x + 564, pos_y + 2, pos_x + 564 + 3, pos_y + 2 + stonesHeight);
    Rectangle(hdc, pos_x + 580, pos_y + 3, pos_x + 580 + 1, pos_y + 4 + stonesHeight);
    Rectangle(hdc, pos_x + 586, pos_y + 1, pos_x + 586 + 5, pos_y + 1 + stonesHeight);
    Rectangle(hdc, pos_x + 604, pos_y + 4, pos_x + 604 + 1, pos_y + 5 + stonesHeight);
    
    Rectangle(hdc, pos_x + 618, pos_y + 4, pos_x + 618 + 3, pos_y + 4 + stonesHeight);
    Rectangle(hdc, pos_x + 626, pos_y + 2, pos_x + 626 + 4, pos_y + 2 + stonesHeight);
    Rectangle(hdc, pos_x + 632, pos_y + 4, pos_x + 632 + 2, pos_y + 4 + stonesHeight);
    
    Rectangle(hdc, pos_x + 646, pos_y + 2, pos_x + 646 + 4, pos_y + 2 + stonesHeight);
    Rectangle(hdc, pos_x + 652, pos_y + 4, pos_x + 652 + 2, pos_y + 4 + stonesHeight);
    Rectangle(hdc, pos_x + 658, pos_y + 1, pos_x + 658 + 1, pos_y + 2 + stonesHeight);
    
    Rectangle(hdc, pos_x + 678, pos_y + 2, pos_x + 678 + 3, pos_y + 2 + stonesHeight);
    Rectangle(hdc, pos_x + 686, pos_y + 4, pos_x + 686 + 3, pos_y + 4 + stonesHeight);
    
    Rectangle(hdc, pos_x + 700, pos_y + 1, pos_x + 700 + 4, pos_y + 1 + stonesHeight);
    Rectangle(hdc, pos_x + 710, pos_y + 2, pos_x + 710 + 2, pos_y + 2 + stonesHeight);
    Rectangle(hdc, pos_x + 720, pos_y + 3, pos_x + 720 + 1, pos_y + 4 + stonesHeight);
    
    Rectangle(hdc, pos_x + 740, pos_y + 3, pos_x + 740 + 3, pos_y + 3 + stonesHeight);
    Rectangle(hdc, pos_x + 754, pos_y + 1, pos_x + 754 + 2, pos_y + 1 + stonesHeight);
    Rectangle(hdc, pos_x + 764, pos_y + 3, pos_x + 764 + 3, pos_y + 3 + stonesHeight);
    
    Rectangle(hdc, pos_x + 782, pos_y + 4, pos_x + 782 + 4, pos_y + 4 + stonesHeight);
    Rectangle(hdc, pos_x + 790, pos_y + 2, pos_x + 790 + 1, pos_y + 3 + stonesHeight);
}

//Очистка
void CRoadStones::Clear(HDC hdc, RECT& paintArea)
{
    RECT intersectionRect; //Нужен для ф-ции проверки пересечения прямоугольников, в него сохраняется область пересечения или 0

    if (!IntersectRect(&intersectionRect, &paintArea, &prevRect))
        return;

    CConfig::backgroundColor.SelectColor(hdc);
    Rectangle(hdc, prevRect.left, prevRect.top, prevRect.right, prevRect.bottom);
}

//Перерисовка в новых координатах
void CRoadStones::Redraw()
{
    if (active == false)
        return;

    prevRect = currentRect;

    currentRect.left = static_cast<int>(pos_X);
    currentRect.top = static_cast<int>(pos_Y);
    currentRect.right = currentRect.left + CConfig::rightBorder;
    currentRect.bottom = currentRect.top + maxStonesHeight;

    InvalidateRect(CConfig::Hwnd, &prevRect, FALSE);
    InvalidateRect(CConfig::Hwnd, &currentRect, FALSE);
}

//Делаем объект активным и помещаем в заданные координаты
void CRoadStones::Activate()
{
    active = true;

    pos_X = restartPos_X;
}

//Перемещаем объект в позицию за край экрана, где он деактивируется
void CRoadStones::Deactivate()
{
    pos_X = static_cast<float>(CConfig::leftBorder - stonesWidth - CBackgroundObjects::speed);
}

//Смещение объекта со временем
void CRoadStones::Move(float maxSpeed)
{
    if (active == false)
        return;

    if (speed == 0.0f)
        return;

    pos_X -= CBackgroundObjects::speed;

    if (static_cast<int>(pos_X) + stonesWidth + CBackgroundObjects::speed <= CConfig::leftBorder)
        active = false;

    Redraw();
}

//Проверка активен ли объект (находится на экране)
bool CRoadStones::CheckActive()
{
    return active;
}

//Возврат позиции по Х
float CRoadStones::GetPos_X()
{
    return pos_X;
}

//Первая активация в самом начале игры
void CRoadStones::FirstActivate()
{
    active = true;

    pos_X = 0.0f;
}
// -----------------------------------------------------------------------------------


// ----------------------------- Класс ямы на дороге (фоновый задний план) ------------------

//Конструктор
CRoadBump::CRoadBump()
    :pos_X(restartPos_X), active(false), twoPitsBumpType(true),  currentRect{}, prevRect{}
{
}

//Отрисовка всего
void CRoadBump::Draw(HDC hdc, RECT& paintArea)
{
    RECT intersectionRect; //Нужен для ф-ции проверки пересечения прямоугольников, в него сохраняется область пересечения или 0

    if (!IntersectRect(&intersectionRect, &paintArea, &currentRect))
        return;

    if (twoPitsBumpType == true)
    {
        DrawPit(hdc, paintArea, 0.0f);
        DrawPit(hdc, paintArea, 30.0f);
    }
    else
    {
        DrawBump(hdc, paintArea, 0.0f);
        DrawPit(hdc, paintArea, 30.0f);
    }
}

//Очистка
void CRoadBump::Clear(HDC hdc, RECT& paintArea)
{
    RECT intersectionRect; //Нужен для ф-ции проверки пересечения прямоугольников, в него сохраняется область пересечения или 0

    if (!IntersectRect(&intersectionRect, &paintArea, &prevRect))
        return;

    CConfig::backgroundColor.SelectColor(hdc);
    Rectangle(hdc, prevRect.left, prevRect.top, prevRect.right, prevRect.bottom);
}

//Перерисовка в новых координатах
void CRoadBump::Redraw()
{
    if (active == false)
        return;

    prevRect = currentRect;

    currentRect.left = static_cast<int>(pos_X);
    currentRect.top = static_cast<int>(pos_Y);
    currentRect.right = currentRect.left + width;
    currentRect.bottom = currentRect.top + height;

    InvalidateRect(CConfig::Hwnd, &prevRect, FALSE);
    InvalidateRect(CConfig::Hwnd, &currentRect, FALSE);
}

//Делаем объект активным и помещаем в заданные координаты
void CRoadBump::Activate()
{
    active = true;

    pos_X = restartPos_X - width;
}

//Перемещаем объект в позицию за край экрана, где он деактивируется
void CRoadBump::Deactivate()
{
    pos_X = static_cast<float>(CConfig::leftBorder - CBackgroundObjects::speed - width);
}

//Смещение объекта со временем
void CRoadBump::Move(float maxSpeed)
{
    if (active == false)
        return;

    if (CBackgroundObjects::speed == 0.0f)
        return;

    pos_X -= CBackgroundObjects::speed;

    if (static_cast<int>(pos_X) + CBackgroundObjects::speed + width <= CConfig::leftBorder)
        active = false;

    Redraw();
}

//Проверка активен ли объект (находится на экране)
bool CRoadBump::CheckActive()
{
    return active;
}

//Возврат позиции по Х
float CRoadBump::GetPos_X()
{
    return pos_X;
}

//Устанавливаем начальный тип неровности (true - 2 кочки, false - кочка и яма)
void CRoadBump::SetFirstBumpType(bool twoPitsBumpType)
{
    this->twoPitsBumpType = twoPitsBumpType;
}

//Активируем объект для проведения тестов
void CRoadBump::TestActivate()
{
    active = true;

    pos_X = restartPos_X / 2.0f;
}

//Отрисовка ямы
void CRoadBump::DrawPit(HDC hdc, RECT& paintArea, float offset_x)
{
    int pos_x = static_cast<int>(pos_X  + offset_x);
    int pos_y = static_cast<int>(pos_Y);

    //Яма
    //Рисуем пропуски фоновые
    CConfig::backgroundColor.SelectColor(hdc);

    Rectangle(hdc, pos_x + 1, pos_y + 3, pos_x + 13, pos_y + 4);

    CConfig::mainBrightColor.SelectColor(hdc);

    Rectangle(hdc, pos_x, pos_y + 4, pos_x + 2, pos_y + 5);
    Rectangle(hdc, pos_x + 1, pos_y + 5, pos_x + 3, pos_y + 6);
    Rectangle(hdc, pos_x + 2, pos_y + 6, pos_x + 12, pos_y + 7);
    Rectangle(hdc, pos_x + 11, pos_y + 5, pos_x + 13, pos_y + 6);
    Rectangle(hdc, pos_x + 12, pos_y + 4, pos_x + 14, pos_y + 5);
}

//Отрисовка кочки
void CRoadBump::DrawBump(HDC hdc, RECT& paintArea, float offset_x)
{
    int pos_x = static_cast<int>(pos_X + offset_x);
    int pos_y = static_cast<int>(pos_Y);

    //Рисуем пропуски фоновые
    CConfig::backgroundColor.SelectColor(hdc);

    Rectangle(hdc, pos_x + 2, pos_y + 3, pos_x + 14, pos_y + 4);

    //Кочка
    CConfig::mainBrightColor.SelectColor(hdc);

    Rectangle(hdc, pos_x + 1, pos_y + 2, pos_x + 3, pos_y + 3);
    Rectangle(hdc, pos_x + 2, pos_y + 1, pos_x + 4, pos_y + 2);
    Rectangle(hdc, pos_x + 3, pos_y, pos_x + 13, pos_y + 1);
    Rectangle(hdc, pos_x + 12, pos_y + 1, pos_x + 14, pos_y + 2);
    Rectangle(hdc, pos_x + 13, pos_y + 2, pos_x + 15, pos_y + 3);
}
// -----------------------------------------------------------------------------------


// ----------------------------- Класс Облако на заднем плане ------------------------
const float CCloud::cloudsSpeed = CBackgroundObjects::startSpeed;

//Конструктор
CCloud::CCloud()
    :pos_X(restartPos_X), pos_Y(startPos_Y), active(false), cloudPoints{ 0 }, currentRect{}, prevRect{}
{
}

//Отрисовка основная
void CCloud::Draw(HDC hdc, RECT& paintArea)
{
    RECT intersectionRect; //Нужен для ф-ции проверки пересечения прямоугольников, в него сохраняется область пересечения или 0

    if (!IntersectRect(&intersectionRect, &paintArea, &currentRect))
        return;

    CConfig::paleCloudColor.SelectColor(hdc);
    
    Polyline(hdc, cloudPoints, pointsAmount);
}

//Очистка
void CCloud::Clear(HDC hdc, RECT& paintArea)
{
    RECT intersectionRect; //Нужен для ф-ции проверки пересечения прямоугольников, в него сохраняется область пересечения или 0

    if (!IntersectRect(&intersectionRect, &paintArea, &prevRect))
        return;

    CConfig::backgroundColor.SelectColor(hdc);
    Rectangle(hdc, prevRect.left, prevRect.top, prevRect.right, prevRect.bottom);
}

//Перерисовка персонажа в новых координатах
void CCloud::Redraw()
{
    if (active == false)
        return;

    prevRect = currentRect;

    currentRect.left = static_cast<int>(pos_X);
    currentRect.top = static_cast<int>(pos_Y);
    currentRect.right = currentRect.left + width;
    currentRect.bottom = currentRect.top + height;

    UpdateDrawRgnPoints();

    InvalidateRect(CConfig::Hwnd, &prevRect, FALSE);
    InvalidateRect(CConfig::Hwnd, &currentRect, FALSE);
}

//Делаем объект активным и помещаем в заданные координаты
void CCloud::Activate()
{
    active = true;

    pos_X = restartPos_X;
    pos_Y = startPos_Y + static_cast<float>(CConfig::GetRandom(20, 120));
}

//Перемещаем объект в позицию за край экрана, где он деактивируется
void CCloud::Deactivate()
{
    pos_X = static_cast<float>(CConfig::leftBorder - cloudsSpeed - width);
}

//Смещение объекта со временем
void CCloud::Move(float maxSpeed)
{
    if (active == false)
        return;

    if (cloudsSpeed == 0.0f)
        return;

    pos_X -= cloudsSpeed;

    if (static_cast<int>(pos_X) + cloudsSpeed + width <= CConfig::leftBorder)
        active = false;

    Redraw();
}

//Проверка активен ли объект (находится на экране)
bool CCloud::CheckActive()
{
    return active;
}

//Первая активация в самом начале игры
void CCloud::FirstActivate()
{
    active = true;

    pos_X = static_cast<float>(CConfig::GetRandom(50, 730));
    pos_Y = startPos_Y + static_cast<float>(CConfig::GetRandom(20, 120));
}

//Обновление точек для отрисовки в новой позиции
void CCloud::UpdateDrawRgnPoints()
{

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    cloudPoints[0] = { pos_x + 40, pos_y + 5 };
    cloudPoints[1] = { pos_x + 50, pos_y + 8 };
    cloudPoints[2] = { pos_x + 50, pos_y + 11 };
    cloudPoints[3] = { pos_x + 54, pos_y + 11 };
    cloudPoints[4] = { pos_x + 54, pos_y + 13 };
    cloudPoints[5] = { pos_x + 57, pos_y + 14 };
    cloudPoints[6] = { pos_x + 1, pos_y + 14 };
    cloudPoints[7] = { pos_x + 1, pos_y + 11 };
    cloudPoints[8] = { pos_x + 6, pos_y + 11 };
    cloudPoints[9] = { pos_x + 6, pos_y + 7 };
    cloudPoints[10] = { pos_x + 16, pos_y + 7 };
    cloudPoints[11] = { pos_x + 16, pos_y + 6 };
    cloudPoints[12] = { pos_x + 20, pos_y + 6 };
    cloudPoints[13] = { pos_x + 20, pos_y + 4 };
    cloudPoints[14] = { pos_x + 23, pos_y + 4 };
    cloudPoints[15] = { pos_x + 23, pos_y + 3 };
    cloudPoints[16] = { pos_x + 25, pos_y + 3 };
    cloudPoints[17] = { pos_x + 25, pos_y + 1 };
    cloudPoints[18] = { pos_x + 37, pos_y + 1 };
    cloudPoints[19] = { pos_x + 39, pos_y + 2 };
    cloudPoints[20] = { pos_x + 39, pos_y + 6 };
    cloudPoints[21] = { pos_x + 35, pos_y + 6 };
}
// -----------------------------------------------------------------------------------
