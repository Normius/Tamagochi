#include "Dinosaur.h"

// ---------------------------- Класс персонажа Dino -------------------------------------------------------------
int CDinosaur::count = 0;
// ------------ Конструктор
CDinosaur::CDinosaur()
    :DinosaurLevelState(EDinosaurLevelState::StartRunLevel), DinosaurBodyState(EDinosaurBodyState::Standing), DinosaurDirectionState(EDinosaurDirectionState::Right), DinosaurMovingState(EDinosaurMovingState::Stop),
     leftKeyDown(false), rightKeyDown(false), height(StandingHeight), width(StandingWidth), pos_X(CConfig::DinosaurConstPos_X), pos_Y(static_cast<float>(StandingPos_Y)), dinoCollisionRects{ 0 },
     horizontalSpeed(0.0f), verticalSpeed(0.0f), collision(false), dinoRect{ 0 }, prevDinoRect{ 0 } 
    //lastLegsChangeTimer(0), newChangeLegsDelay(CConfig::FPS / 20), firstStep(true)
{
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка персонажа Dino (основной метод)
void CDinosaur::Draw(HDC hdc, RECT& paintArea)
{
    RECT intersectionRect; //Нужен для ф-ции проверки пересечения прямоугольников, в него сохраняется область пересечения или 0

    if (!IntersectRect(&intersectionRect, &paintArea, &dinoRect))
    {
        return;
    }

    switch (DinosaurBodyState)
    {
    case EDinosaurBodyState::Standing:
    {
        if (DinosaurDirectionState == EDinosaurDirectionState::Right)
        {
            //Драко стоит (вправо)
            DrawRightStanding(hdc);
            DrawRightStandingLegs(hdc);

            if (DinosaurMovingState == EDinosaurMovingState::MovingRight || DinosaurMovingState == EDinosaurMovingState::MovingLeft)
            {
                if (pos_Y + height == OnGroundLegsPos_Y)
                    MoveLegsRight(hdc);
            }

            //Столкновение Драко с препятствием и анимация глаз
            if (collision == true)
            {
                DrawRightEye(hdc);
                Beep(600, 25);
            }
        }
        else
        {
            //Драко стоит (влево)
            DrawLeftStanding(hdc);
            DrawLeftStandingLegs(hdc);

            if (DinosaurMovingState == EDinosaurMovingState::MovingRight || DinosaurMovingState == EDinosaurMovingState::MovingLeft)
            {
                {
                    if (pos_Y + height == OnGroundLegsPos_Y)
                        MoveLegsLeft(hdc);
                }
            }

            //Столкновение Драко с препятствием и анимация глаз
            if (collision == true)
            {
                DrawLeftEye(hdc);
                Beep(600, 25);
            }
        }
    }
    break;
    case EDinosaurBodyState::Crawling:
    {
        if (DinosaurDirectionState == EDinosaurDirectionState::Right)
        {
            //Драко в присяде (вправо)
            DrawRightCrawling(hdc);
            DrawRightStandingLegs(hdc);

            if (DinosaurMovingState == EDinosaurMovingState::MovingRight || DinosaurMovingState == EDinosaurMovingState::MovingLeft)
            {
                if (pos_Y + height == OnGroundLegsPos_Y)
                    MoveLegsRight(hdc);
            }

            //Столкновение Драко с препятствием и анимация глаз
            if (collision == true)
            {
                DrawRightEye(hdc);
                Beep(600, 25);
            }
        }
        else
        {
            //Драко в присяде (влево)
            DrawLeftCrawling(hdc);
            DrawLeftStandingLegs(hdc);

            if (DinosaurMovingState == EDinosaurMovingState::MovingRight || DinosaurMovingState == EDinosaurMovingState::MovingLeft)
            {
                if (pos_Y + height == OnGroundLegsPos_Y)
                    MoveLegsLeft(hdc);
            }

            //Столкновение Драко с препятствием и анимация глаз
            if (collision == true)
            {
                DrawLeftEye(hdc);
                Beep(600, 25);
            }
        }
    }
    break;

    default:
        break;
    }
    CDinosaur::count++;
}
// -----------------------------------------------------------------------------------

void CDinosaur::Clear(HDC hdc, RECT& paintArea)
{
    RECT intersectionRect; //Нужен для ф-ции проверки пересечения прямоугольников, в него сохраняется область пересечения или 0

    if (!IntersectRect(&intersectionRect, &paintArea, &prevDinoRect))
    {
        return;
    }

    CConfig::backgroundColor.SelectColor(hdc);
    Rectangle(hdc, prevDinoRect.left, prevDinoRect.top, prevDinoRect.right, prevDinoRect.bottom);
}

// ------------ Перерисовка персонажа в новых координатах
void CDinosaur::Redraw()
{
    prevDinoRect = dinoRect;

    dinoRect.left = static_cast<int>(pos_X);
    dinoRect.top = static_cast<int>(pos_Y);
    dinoRect.right = dinoRect.left + width * CConfig::SizeScale;
    dinoRect.bottom = dinoRect.top + height * CConfig::SizeScale;

    InvalidateRect(CConfig::Hwnd, &prevDinoRect, FALSE);
    InvalidateRect(CConfig::Hwnd, &dinoRect, FALSE);
}
// -----------------------------------------------------------------------------------

// ------------ Очистка фона для перерисовки
void CDinosaur::ClearRightLegsBackground(HDC hdc)
{
    //Очищаем фон ног
    CConfig::backgroundColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    if (DinosaurBodyState == EDinosaurBodyState::Crawling)
        pos_y -= (StandingHeight - CrawlingHeight) * CConfig::SizeScale;


    ////Левая нога поднятая
    //Rectangle(hdc, pos_x + 12 * CConfig::SizeScale, pos_y + (36 - 4) * CConfig::SizeScale, pos_x + 15 * CConfig::SizeScale, pos_y + (44 - 4) * CConfig::SizeScale);
    //Rectangle(hdc, pos_x + 15 * CConfig::SizeScale, pos_y + (42 - 4) * CConfig::SizeScale, pos_x + 18 * CConfig::SizeScale, pos_y + (44 - 4) * CConfig::SizeScale);

    ////Правая нога поднятая
    //Rectangle(hdc, pos_x + 22 * CConfig::SizeScale, pos_y + (36 - 4) * CConfig::SizeScale, pos_x + 25 * CConfig::SizeScale, pos_y + (44 - 4) * CConfig::SizeScale);
    //Rectangle(hdc, pos_x + 25 * CConfig::SizeScale, pos_y + (42 - 4) * CConfig::SizeScale, pos_x + 28 * CConfig::SizeScale, pos_y + (44 - 4) * CConfig::SizeScale);

    ////Левая нога
    //Rectangle(hdc, pos_x + 12 * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale, pos_x + 15 * CConfig::SizeScale, pos_y + 44 * CConfig::SizeScale);
    //Rectangle(hdc, pos_x + 15 * CConfig::SizeScale, pos_y + 42 * CConfig::SizeScale, pos_x + 18 * CConfig::SizeScale, pos_y + 44 * CConfig::SizeScale);

    ////Правая нога
    //Rectangle(hdc, pos_x + 22 * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale, pos_x + 25 * CConfig::SizeScale, pos_y + 44 * CConfig::SizeScale);
    //Rectangle(hdc, pos_x + 25 * CConfig::SizeScale, pos_y + 42 * CConfig::SizeScale, pos_x + 28 * CConfig::SizeScale, pos_y + 44 * CConfig::SizeScale);

    //Левая нога
    Rectangle(hdc, pos_x + 12 * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale, pos_x + 22 * CConfig::SizeScale, pos_y + 44 * CConfig::SizeScale);

    //Правая нога
    Rectangle(hdc, pos_x + 22 * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale, pos_x + 28 * CConfig::SizeScale, pos_y + 44 * CConfig::SizeScale);

    //if (firstStep == true)
    //{
    //    //Правая нога
    //    Rectangle(hdc, pos_x + 22 * CConfig::SizeScale, pos_y + 40 * CConfig::SizeScale, pos_x + 28 * CConfig::SizeScale, pos_y + 44 * CConfig::SizeScale);
    //}
    //else
    //{
    //    //Левая нога
    //    Rectangle(hdc, pos_x + 12 * CConfig::SizeScale, pos_y + 40 * CConfig::SizeScale, pos_x + 22 * CConfig::SizeScale, pos_y + 44 * CConfig::SizeScale);
    //}
}
// -----------------------------------------------------------------------------------

// ------------ Очистка фона для перерисовки влево
void CDinosaur::ClearLeftLegsBackground(HDC hdc)
{
    //Очищаем фон ног
    CConfig::backgroundColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    if (DinosaurBodyState == EDinosaurBodyState::Crawling)
        pos_y -= (StandingHeight - CrawlingHeight) * CConfig::SizeScale;

    //Левая нога
    Rectangle(hdc, pos_x + (width - 12) * CConfig::SizeScale, pos_y + (36 * CConfig::SizeScale), pos_x + (width - 18) * CConfig::SizeScale, pos_y + (44 * CConfig::SizeScale));

    //Правая нога
    Rectangle(hdc, pos_x + (width - 22) * CConfig::SizeScale, pos_y + (36 * CConfig::SizeScale), pos_x + (width - 28) * CConfig::SizeScale, pos_y + (44 * CConfig::SizeScale));
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка ног стоя
void CDinosaur::DrawRightStandingLegs(HDC hdc)
{
    //Рисуем ноги
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    if (DinosaurBodyState == EDinosaurBodyState::Crawling)
        pos_y -= (StandingHeight - CrawlingHeight) * CConfig::SizeScale;

    //Левая нога
    Rectangle(hdc, pos_x + 12 * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale, pos_x + 15 * CConfig::SizeScale, pos_y + 44 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 15 * CConfig::SizeScale, pos_y + 42 * CConfig::SizeScale, pos_x + 18 * CConfig::SizeScale, pos_y + 44 * CConfig::SizeScale);

    //Правая нога
    Rectangle(hdc, pos_x + 22 * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale, pos_x + 25 * CConfig::SizeScale, pos_y + 44 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 25 * CConfig::SizeScale, pos_y + 42 * CConfig::SizeScale, pos_x + 28 * CConfig::SizeScale, pos_y + 44 * CConfig::SizeScale);
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка ног стоя влево 
void CDinosaur::DrawLeftStandingLegs(HDC hdc)
{
    //Рисуем ноги
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    if (DinosaurBodyState == EDinosaurBodyState::Crawling)
        pos_y -= (StandingHeight - CrawlingHeight) * CConfig::SizeScale;

    //Левая нога
    Rectangle(hdc, pos_x + (width - 12) * CConfig::SizeScale, pos_y + (36 * CConfig::SizeScale), pos_x + (width - 15) * CConfig::SizeScale, pos_y + (44 * CConfig::SizeScale));
    Rectangle(hdc, pos_x + (width - 15) * CConfig::SizeScale, pos_y + (42 * CConfig::SizeScale), pos_x + (width - 18) * CConfig::SizeScale, pos_y + (44 * CConfig::SizeScale));

    //Правая нога
    Rectangle(hdc, pos_x + (width - 22) * CConfig::SizeScale, pos_y + (36 * CConfig::SizeScale), pos_x + (width - 25) * CConfig::SizeScale, pos_y + (44 * CConfig::SizeScale));
    Rectangle(hdc, pos_x + (width - 25) * CConfig::SizeScale, pos_y + (42 * CConfig::SizeScale), pos_x + (width - 28) * CConfig::SizeScale, pos_y + (44 * CConfig::SizeScale));
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка ног при первом шаге
void CDinosaur::DrawRightFirstStep(HDC hdc)
{
    ClearRightLegsBackground(hdc);

    //Рисуем ноги
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    if (DinosaurBodyState == EDinosaurBodyState::Crawling)
        pos_y -= (StandingHeight - CrawlingHeight) * CConfig::SizeScale;

    //Левая нога обычно
    Rectangle(hdc, pos_x + 12 * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale, pos_x + 15 * CConfig::SizeScale, pos_y + 44 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 15 * CConfig::SizeScale, pos_y + 42 * CConfig::SizeScale, pos_x + 18 * CConfig::SizeScale, pos_y + 44 * CConfig::SizeScale);

    //Правая нога поднятая
    Rectangle(hdc, pos_x + 22 * CConfig::SizeScale, pos_y + (36 - 4) * CConfig::SizeScale, pos_x + 25 * CConfig::SizeScale, pos_y + (44 - 4) * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 25 * CConfig::SizeScale, pos_y + (42 - 4) * CConfig::SizeScale, pos_x + 28 * CConfig::SizeScale, pos_y + (44 - 4) * CConfig::SizeScale);
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка ног при втором шаге
void CDinosaur::DrawRightSecondStep(HDC hdc)
{
    ClearRightLegsBackground(hdc);

    //Рисуем ноги
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    if (DinosaurBodyState == EDinosaurBodyState::Crawling)
        pos_y -= (StandingHeight - CrawlingHeight) * CConfig::SizeScale;

    //Левая нога поднятая
    Rectangle(hdc, pos_x + 12 * CConfig::SizeScale, pos_y + (36 - 4) * CConfig::SizeScale, pos_x + 15 * CConfig::SizeScale, pos_y + (44 - 4) * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 15 * CConfig::SizeScale, pos_y + (42 - 4) * CConfig::SizeScale, pos_x + 18 * CConfig::SizeScale, pos_y + (44 - 4) * CConfig::SizeScale);

    //Правая нога обычно
    Rectangle(hdc, pos_x + 22 * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale, pos_x + 25 * CConfig::SizeScale, pos_y + 44 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 25 * CConfig::SizeScale, pos_y + 42 * CConfig::SizeScale, pos_x + 28 * CConfig::SizeScale, pos_y + 44 * CConfig::SizeScale);
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка ног при первом шаге влево
void CDinosaur::DrawLeftFirstStep(HDC hdc)
{
    ClearLeftLegsBackground(hdc);

    //Рисуем ноги
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    if (DinosaurBodyState == EDinosaurBodyState::Crawling)
        pos_y -= (StandingHeight - CrawlingHeight) * CConfig::SizeScale;

    //Левая нога обычно
    Rectangle(hdc, pos_x + (width - 12) * CConfig::SizeScale, pos_y + (36 * CConfig::SizeScale), pos_x + (width - 15) * CConfig::SizeScale, pos_y + (44 * CConfig::SizeScale));
    Rectangle(hdc, pos_x + (width - 15) * CConfig::SizeScale, pos_y + (42 * CConfig::SizeScale), pos_x + (width - 18) * CConfig::SizeScale, pos_y + (44 * CConfig::SizeScale));

    //Правая нога поднятая
    Rectangle(hdc, pos_x + (width - 22) * CConfig::SizeScale, pos_y + (36 - 4) * CConfig::SizeScale, pos_x + (width - 25) * CConfig::SizeScale, pos_y + (44 - 4) * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (width - 25) * CConfig::SizeScale, pos_y + (42 - 4) * CConfig::SizeScale, pos_x + (width - 28) * CConfig::SizeScale, pos_y + (44 - 4) * CConfig::SizeScale);
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка ног при втором шаге влево
void CDinosaur::DrawLeftSecondStep(HDC hdc)
{
    ClearLeftLegsBackground(hdc);

    //Рисуем ноги
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    if (DinosaurBodyState == EDinosaurBodyState::Crawling)
        pos_y -= (StandingHeight - CrawlingHeight) * CConfig::SizeScale;

    //Левая нога поднятая
    Rectangle(hdc, pos_x + (width - 12) * CConfig::SizeScale, pos_y + (36 - 4) * CConfig::SizeScale, pos_x + (width - 15) * CConfig::SizeScale, pos_y + (44 - 4) * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (width - 15) * CConfig::SizeScale, pos_y + (42 - 4) * CConfig::SizeScale, pos_x + (width - 18) * CConfig::SizeScale, pos_y + (44 - 4) * CConfig::SizeScale);

    //Правая нога обычно
    Rectangle(hdc, pos_x + (width - 22) * CConfig::SizeScale, pos_y + (36 * CConfig::SizeScale), pos_x + (width - 25) * CConfig::SizeScale, pos_y + (44 * CConfig::SizeScale));
    Rectangle(hdc, pos_x + (width - 25) * CConfig::SizeScale, pos_y + (42 * CConfig::SizeScale), pos_x + (width - 28) * CConfig::SizeScale, pos_y + (44 * CConfig::SizeScale));
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка зрачка при стоклновении
void CDinosaur::DrawRightEye(HDC hdc)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    if (DinosaurBodyState == EDinosaurBodyState::Crawling)
        pos_x += (CrawlingWidth - StandingWidth) * CConfig::SizeScale;

    //Зрачок при столкновении
    Rectangle(hdc, pos_x + 28 * CConfig::SizeScale, pos_y + 3 * CConfig::SizeScale, pos_x + 30 * CConfig::SizeScale, pos_y + 5 * CConfig::SizeScale);
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка зрачка при стоклновении влево
void CDinosaur::DrawLeftEye(HDC hdc)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    if (DinosaurBodyState == EDinosaurBodyState::Crawling)
        pos_x -= (CrawlingWidth - StandingWidth) * CConfig::SizeScale;

    //Зрачок при столкновении
    Rectangle(hdc, pos_x + (width - 28) * CConfig::SizeScale, pos_y + 3 * CConfig::SizeScale, pos_x + (width - 30) * CConfig::SizeScale, pos_y + 5 * CConfig::SizeScale);
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка тела в обычном состоянии
void CDinosaur::DrawRightStanding(HDC hdc)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    const int dinosaurBodyPointAmount = 26;

    const POINT dinosaurBodyPoints[dinosaurBodyPointAmount]{ {pos_x + 20, pos_y + 15}, {pos_x + 23, pos_y + 15}, {pos_x + 23, pos_y + 1}, {pos_x + 25, pos_y + 0}, {pos_x + 41, pos_y + 0}, {pos_x + 43, pos_y + 1}, 
                                                             {pos_x + 43, pos_y + 9}, {pos_x + 33, pos_y + 9}, {pos_x + 33, pos_y + 12}, {pos_x + 40, pos_y + 12}, {pos_x + 40, pos_y + 14}, {pos_x + 30, pos_y + 14}, 
                                                             {pos_x + 30, pos_y + 20}, {pos_x + 35, pos_y + 20}, {pos_x + 35, pos_y + 23}, {pos_x + 34, pos_y + 23}, {pos_x + 34, pos_y + 21}, {pos_x + 30, pos_y + 21},
                                                             {pos_x + 30, pos_y + 30}, {pos_x + 25, pos_y + 35}, {pos_x + 10, pos_y + 35}, {pos_x + 1, pos_y + 27}, {pos_x + 1, pos_y + 16}, {pos_x + 3, pos_y + 13},
                                                             {pos_x + 7, pos_y + 23}, {pos_x + 11, pos_y + 23} };

    Polygon(hdc, dinosaurBodyPoints, dinosaurBodyPointAmount);

    //Фоновые пропуски
    CConfig::backgroundColor.SelectColor(hdc);

    //Глаз
    Rectangle(hdc, pos_x + 27 * CConfig::SizeScale, pos_y + 2 * CConfig::SizeScale, pos_x + 31 * CConfig::SizeScale, pos_y + 6 * CConfig::SizeScale);
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка тела в обычном состоянии влево
void CDinosaur::DrawLeftStanding(HDC hdc)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    const int dinosaurBodyPointAmount = 26;

    const POINT dinosaurBodyPoints[dinosaurBodyPointAmount]{ {pos_x + width - 20, pos_y + 15}, {pos_x + width - 23, pos_y + 15}, {pos_x + width - 23, pos_y + 1}, {pos_x + width - 25, pos_y + 0}, {pos_x + width - 41, pos_y + 0}, 
                                                             {pos_x + width - 43, pos_y + 1}, {pos_x + width - 43, pos_y + 9}, {pos_x + width - 33, pos_y + 9}, {pos_x + width - 33, pos_y + 12}, {pos_x + width - 40, pos_y + 12}, 
                                                             {pos_x + width - 40, pos_y + 14}, {pos_x + width - 30, pos_y + 14}, {pos_x + width - 30, pos_y + 20}, {pos_x + width - 35, pos_y + 20}, {pos_x + width - 35, pos_y + 23},
                                                             {pos_x + width - 34, pos_y + 23}, {pos_x + width - 34, pos_y + 21}, {pos_x + width - 30, pos_y + 21}, {pos_x + width - 30, pos_y + 30}, {pos_x + width - 25, pos_y + 35}, 
                                                             {pos_x + width - 10, pos_y + 35}, {pos_x + width - 1, pos_y + 27}, {pos_x + width - 1, pos_y + 16}, {pos_x + width - 3, pos_y + 13}, {pos_x + width - 7, pos_y + 23},
                                                             {pos_x + width - 11, pos_y + 23} };


    Polygon(hdc, dinosaurBodyPoints, dinosaurBodyPointAmount);

    CConfig::backgroundColor.SelectColor(hdc);

    //Глаз
    Rectangle(hdc, pos_x + (width - 27) * CConfig::SizeScale, pos_y + (2 * CConfig::SizeScale), pos_x + (width - 31) * CConfig::SizeScale, pos_y + (6 * CConfig::SizeScale));
}
// -----------------------------------------------------------------------------------

// ----------- Отрисовка тела в присяде
void CDinosaur::DrawRightCrawling(HDC hdc)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    const int dinosaurBodyPointAmount = 26;

    const POINT dinosaurBodyPoints[dinosaurBodyPointAmount]{ {pos_x + 1, pos_y + 0}, {pos_x + 5, pos_y + 3}, {pos_x + 13, pos_y + 3}, {pos_x + 16, pos_y + 1}, {pos_x + 33, pos_y + 1}, {pos_x + 36, pos_y + 3}, 
                                                             {pos_x + 39, pos_y + 3}, {pos_x + 41, pos_y + 0}, {pos_x + 57, pos_y + 0}, {pos_x + 59, pos_y + 1}, {pos_x + 59, pos_y + 9}, {pos_x + 49, pos_y + 9}, 
                                                             {pos_x + 49, pos_y + 12}, {pos_x + 56, pos_y + 12}, {pos_x + 56, pos_y + 14}, {pos_x + 42, pos_y + 14}, {pos_x + 39, pos_y + 13}, {pos_x + 36, pos_y + 13}, 
                                                             {pos_x + 33, pos_y + 16}, {pos_x + 33, pos_y + 20}, {pos_x + 35, pos_y + 20}, {pos_x + 35, pos_y + 21}, {pos_x + 32, pos_y + 21}, {pos_x + 32, pos_y + 17}, 
                                                             {pos_x + 10, pos_y + 17}, {pos_x + 1, pos_y + 5} };
                                      

    Polygon(hdc, dinosaurBodyPoints, dinosaurBodyPointAmount);

    //Фоновые пропуски
    CConfig::backgroundColor.SelectColor(hdc);

    //Глаз
    Rectangle(hdc, pos_x + 43 * CConfig::SizeScale, pos_y + 2 * CConfig::SizeScale, pos_x + 47 * CConfig::SizeScale, pos_y + 6 * CConfig::SizeScale);
}
// -----------------------------------------------------------------------------------

// ----------- Отрисовка тела в присяде влево ----------------------------------------
void CDinosaur::DrawLeftCrawling(HDC hdc)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    const int dinosaurBodyPointAmount = 26;

    const POINT dinosaurBodyPoints[]{ {pos_x + width - 1, pos_y + 0}, {pos_x + width - 5, pos_y + 3}, {pos_x + width - 13, pos_y + 3}, {pos_x + width - 16, pos_y + 1}, {pos_x + width - 33, pos_y + 1}, 
                                      {pos_x + width - 36, pos_y + 3}, {pos_x + width - 39, pos_y + 3}, {pos_x + width - 41, pos_y + 0}, {pos_x + width - 57, pos_y + 0}, {pos_x + width - 59, pos_y + 1},
                                      {pos_x + width - 59, pos_y + 9}, {pos_x + width - 49, pos_y + 9}, {pos_x + width - 49, pos_y + 12}, {pos_x + width - 56, pos_y + 12}, {pos_x + width - 56, pos_y + 14},
                                      {pos_x + width - 42, pos_y + 14}, {pos_x + width - 39, pos_y + 13}, {pos_x + width - 36, pos_y + 13}, {pos_x + width - 33, pos_y + 16}, {pos_x + width - 33, pos_y + 20},
                                      {pos_x + width - 35, pos_y + 20}, {pos_x + width - 35, pos_y + 21}, {pos_x + width - 32, pos_y + 21}, {pos_x + width - 32, pos_y + 17}, {pos_x + width - 10, pos_y + 17},
                                      {pos_x + width - 1, pos_y + 5} };

    Polygon(hdc, dinosaurBodyPoints, dinosaurBodyPointAmount);

    //Фоновые пропуски
    CConfig::backgroundColor.SelectColor(hdc);

    //Глаз
    Rectangle(hdc, pos_x + width - 43 * CConfig::SizeScale, pos_y + 2 * CConfig::SizeScale, pos_x + width - 47 * CConfig::SizeScale, pos_y + 6 * CConfig::SizeScale);
}
// -----------------------------------------------------------------------------------

// ------------ Анимация ног при движении вправо
void CDinosaur::MoveLegsRight(HDC hdc)
{
   
    if (static_cast<int>(CConfig::slowCurrentFrameValue) % 2 == 0)
    {
        DrawRightFirstStep(hdc);

    }
    else
    {
        DrawRightSecondStep(hdc);
    }
}
// -----------------------------------------------------------------------------------

// ------------ Анимация ног при движении вправо
void CDinosaur::MoveLegsLeft(HDC hdc)
{

    if (static_cast<int>(CConfig::slowCurrentFrameValue) % 2 == 0)
    {
        DrawLeftFirstStep(hdc);

    }
    else
    {
        DrawLeftSecondStep(hdc);
    }
}
// -----------------------------------------------------------------------------------

// ------------ Установка состояния положения Дино (стоя/присед)
void CDinosaur::SetBodyState(EDinosaurBodyState newState)
{
    if (DinosaurBodyState == newState)
        return;

    if (newState == EDinosaurBodyState::Crawling)
    {
        if (height != CrawlingHeight)
            pos_Y += static_cast<float>(StandingHeight - CrawlingHeight);

        DinosaurBodyState = EDinosaurBodyState::Crawling;
        height = CrawlingHeight;
        width = CrawlingWidth;
        
        CorrectHorizontalEdgePosition();
        CorrectVerticalEdgePosition();
    }
    else
    {
        if (height != StandingHeight)
            pos_Y -= static_cast<float>(StandingHeight - CrawlingHeight);

        DinosaurBodyState = EDinosaurBodyState::Standing;
        height = StandingHeight;
        width = StandingWidth;
    }
}
// -----------------------------------------------------------------------------------

void CDinosaur::SetLevelState(EDinosaurLevelState newstate)
{
    if (DinosaurLevelState == newstate)
        return;

    DinosaurLevelState = newstate;
    DinosaurMovingState = EDinosaurMovingState::MovingRight;
}

void CDinosaur::CorrectVerticalEdgePosition()
{
    if (static_cast<int>(pos_Y) + height >= OnGroundLegsPos_Y) //Двигаемся вниз до тех пор, пока Дино не достигнет земли
    {
        pos_Y = static_cast<float>(OnGroundLegsPos_Y - height);
    }

    if (static_cast<int>(pos_Y) <= StandingPos_Y - MaxJumpHeight * CConfig::SizeScale) //Когда Дино достигает максимальной высоты прыжка (или чуть больше), меняем знак шага перемещения на положительный для движения вниз (падения)
        verticalSpeed = 0.0f; //При достижении максимальной высоты перемещение приравниваем к 0 
}

// ------------ Перемещение по вертикали (падение вниз или движение вверх при прыжке) (работает по таймеру)
void CDinosaur::MoveVertical(float maxSpeed)
{
    if (static_cast<int>(pos_Y) + height == OnGroundLegsPos_Y) //Если Дино на земле, ничего не делаем
        return;

    float nextStep = verticalSpeed / maxSpeed * CConfig::minShift;

    pos_Y += nextStep;

    CorrectVerticalEdgePosition();
}
// -----------------------------------------------------------------------------------

// ------------  Горизонтальное движение по таймеру 
void CDinosaur::CorrectHorizontalEdgePosition()
{
    if (static_cast<int>(pos_X) + width * CConfig::SizeScale >= CConfig::rightBorder)
        pos_X = static_cast<float>(CConfig::rightBorder - width * CConfig::SizeScale);

    if (static_cast<int>(pos_X) < CConfig::leftBorder)
        pos_X = static_cast<float>(CConfig::leftBorder);
}

// ------------  Горизонтальное движение по таймеру 
void CDinosaur::MoveHorizontal(float maxSpeed)
{
    if (horizontalSpeed == 0.0f) //Если скорость = 0, ничего не делаем
        return;

    //Смещение на небольшие шажки 
    float nextStep = horizontalSpeed / maxSpeed * CConfig::minShift;

    pos_X += nextStep;

    CorrectHorizontalEdgePosition();
}

// ------------ Выбор направления движения по горизонтали (обрабатывает нажатия и отжатие клавиш влево-вправо)
void CDinosaur::CheckHorizontalDirection(bool leftDirection, bool keyPressed) //leftDirection == true(нажата клавиша влево), ==false (нажата клавиша вправо); //keyPressed == true (нажатие), == false (отжатие)
{
    if (leftDirection == true) //если нажата или отжата клавиша влево
        leftKeyDown = keyPressed; //записываем в состояние левой клавиши её нажатие(true) или отжатие (false)
    else
        rightKeyDown = keyPressed; //иначе нажата или отжата правая

    if (leftKeyDown == true && rightKeyDown == true) //Если нажаты обе клавиши одновременно
        return; //Игнорируем одновременное нажатие 2 клавиш

    if (leftKeyDown == false && rightKeyDown == false) //Если обе отжаты, останавливаемся
    {
        if (DinosaurLevelState == EDinosaurLevelState::FreeMovingLevel)
        {
            DinosaurMovingState = EDinosaurMovingState::Stop;
            horizontalSpeed = 0.0f;
            return;
        }
    }

    if (leftKeyDown == true) //Обработка нажатия левой клавиши
    {
        DinosaurDirectionState = EDinosaurDirectionState::Left;
        if (pos_Y + height == OnGroundLegsPos_Y)
        {
            DinosaurMovingState = EDinosaurMovingState::MovingLeft;
            horizontalSpeed = -MaxSpeed_X * CConfig::FSizeScale;
        }
    }

    if (rightKeyDown == true) //Обработка нажатия левой клавиши
    {
        DinosaurDirectionState = EDinosaurDirectionState::Right;
        if (pos_Y + height == OnGroundLegsPos_Y)
        {
            DinosaurMovingState = EDinosaurMovingState::MovingRight;
            horizontalSpeed = MaxSpeed_X * CConfig::FSizeScale;
        }
    }
}
// -----------------------------------------------------------------------------------

// ------------ Прыжок (начало прыжка, подъём Дино от земли, дальше работает метод MoveHorizontal)  (обрабатывает нажатие пробела)
void CDinosaur::Jump()
{
    if (pos_Y + height == OnGroundLegsPos_Y)
    {
        pos_Y -= 1.0f;
        verticalSpeed = -MaxSpeed_Y;
        //DinosaurMovingState = EDinosaurMovingState::Jumping;

        //Beep(300, 50); //TO DO: Перенести обработку звука в отдельный поток, чтобы не вызывало задержку
    }
}
// -----------------------------------------------------------------------------------

// ------------ Модель Динозавра поделена на 3 прямоугольника, с которыми проверяем столкновения других объектов
void CDinosaur::SetDinoCollisionRects()
{
    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    if (DinosaurBodyState == EDinosaurBodyState::Standing)
    {
        if (DinosaurDirectionState == EDinosaurDirectionState::Right)
        {
            SetRect(&dinoCollisionRects[0], pos_x + 23 * CConfig::SizeScale, pos_y, pos_x + 43 * CConfig::SizeScale, pos_y + 14 * CConfig::SizeScale);
            SetRect(&dinoCollisionRects[1], pos_x + 9 * CConfig::SizeScale, pos_y + 19 * CConfig::SizeScale, pos_x + 27 * CConfig::SizeScale, pos_y + 43 * CConfig::SizeScale);
            SetRect(&dinoCollisionRects[2], pos_x, pos_y + 13 * CConfig::SizeScale, pos_x + 6 * CConfig::SizeScale, pos_y + 31 * CConfig::SizeScale);
        }
        else
        {
            SetRect(&dinoCollisionRects[0], pos_x + width - 23 * CConfig::SizeScale, pos_y, pos_x + width - 43 * CConfig::SizeScale, pos_y + 14 * CConfig::SizeScale);
            SetRect(&dinoCollisionRects[1], pos_x + width - 9 * CConfig::SizeScale, pos_y + 19 * CConfig::SizeScale, pos_x + width - 27 * CConfig::SizeScale, pos_y + 43 * CConfig::SizeScale);
            SetRect(&dinoCollisionRects[2], pos_x + width - 0, pos_y + 13 * CConfig::SizeScale, pos_x + width - 6 * CConfig::SizeScale, pos_y + 31 * CConfig::SizeScale);
        }
    }
    else
    {
        if (DinosaurDirectionState == EDinosaurDirectionState::Right)
        {
            SetRect(&dinoCollisionRects[0], pos_x + 6 * CConfig::SizeScale, pos_y, pos_x + 59 * CConfig::SizeScale, pos_y + 14 * CConfig::SizeScale);
            SetRect(&dinoCollisionRects[1], pos_x + 11 * CConfig::SizeScale, pos_y + 15 * CConfig::SizeScale, pos_x + 35 * CConfig::SizeScale, pos_y + 25 * CConfig::SizeScale);
            SetRect(&dinoCollisionRects[2], pos_x, pos_y, pos_x + 5 * CConfig::SizeScale, pos_y + 9 * CConfig::SizeScale);
        }
        else 
        {
            SetRect(&dinoCollisionRects[0], pos_x + width - 6 * CConfig::SizeScale, pos_y, pos_x + width - 59 * CConfig::SizeScale, pos_y + 14 * CConfig::SizeScale);
            SetRect(&dinoCollisionRects[1], pos_x + width - 11 * CConfig::SizeScale, pos_y + 15 * CConfig::SizeScale, pos_x + width - 35 * CConfig::SizeScale, pos_y + 25 * CConfig::SizeScale);
            SetRect(&dinoCollisionRects[2], pos_x + width - 0, pos_y, pos_x + width - 5 * CConfig::SizeScale, pos_y + 9 * CConfig::SizeScale);
        }
    }
}
// -----------------------------------------------------------------------------------