#include "Dinosaur.h"

// ---------------------------- Класс персонажа Dino -------------------------------------------------------------

// ------------ Конструктор
CDinosaur::CDinosaur()
    :DinosaurLevelState(EDinosaurLevelState::StartLevel), DinosaurBodyState(EDinosaurBodyState::Standing), DinosaurDirectionState(EDinosaurDirectionState::Right), DinosaurMovingState(EDinosaurMovingState::Stop),
     leftKeyDown(false), rightKeyDown(false), height(StandingHeight), width(StandingWidth), pos_X(startPos_X), pos_Y(static_cast<float>(StandingPos_Y)), dinoCollisionRects{ 0 },
     horizontalSpeed(0.0f), verticalSpeed(0.0f), collision(false), currentDinosaurPoints{ 0 }, prevDinosaurPoints{ 0 }, currentRect{ 0 }, prevRect{ 0 }, onStartPlatform(false), OnGroundLegsPos_Y(StandingPos_Y + StandingHeight),
     falling(false)
    //currentPolyRgn{ 0 }, prevPolyRgn { 0 }, prevRectRgn{ 0 }, currentRectRgn{ 0 }
{
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка персонажа Dino (основной метод)
void CDinosaur::Draw(HDC hdc, RECT& paintArea)
{
    RECT intersectionRect; //Нужен для ф-ции проверки пересечения прямоугольников, в него сохраняется область пересечения или 0

    if (!IntersectRect(&intersectionRect, &paintArea, &currentRect))
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
}
// -----------------------------------------------------------------------------------

void CDinosaur::Clear(HDC hdc, RECT& paintArea)
{
    RECT intersectionRect; //Нужен для ф-ции проверки пересечения прямоугольников, в него сохраняется область пересечения или 0

    if (!IntersectRect(&intersectionRect, &paintArea, &prevRect))
    {
        return;
    }

    CConfig::backgroundColor.SelectColor(hdc);

    Polygon(hdc, prevDinosaurPoints, dinosaurWithLegsPointsAmount);
}

void CDinosaur::UpdateRgnPoints()
{
    switch (DinosaurBodyState)
    {
    case EDinosaurBodyState::Standing:
    {
        if (DinosaurDirectionState == EDinosaurDirectionState::Right)
        {
            currentDinosaurPoints[0] = { currentRgnPos_X + 11, currentRgnPos_Y + 36 };
            currentDinosaurPoints[1] = { currentRgnPos_X + 1, currentRgnPos_Y + 27 }; 
            currentDinosaurPoints[2] = { currentRgnPos_X + 1, currentRgnPos_Y + 16 }; 
            currentDinosaurPoints[3] = { currentRgnPos_X + 3, currentRgnPos_Y + 13 }; 
            currentDinosaurPoints[4] = { currentRgnPos_X + 7, currentRgnPos_Y + 23 }; 
            currentDinosaurPoints[5] = { currentRgnPos_X + 11, currentRgnPos_Y + 23 };
            currentDinosaurPoints[6] = { currentRgnPos_X + 20, currentRgnPos_Y + 15 };
            currentDinosaurPoints[7] = { currentRgnPos_X + 23, currentRgnPos_Y + 15 };
            currentDinosaurPoints[8] = { currentRgnPos_X + 23, currentRgnPos_Y + 1 }; 
            currentDinosaurPoints[9] = { currentRgnPos_X + 25, currentRgnPos_Y + 0 }; 
            currentDinosaurPoints[10] = { currentRgnPos_X + 41, currentRgnPos_Y + 0 };
            currentDinosaurPoints[11] = { currentRgnPos_X + 43, currentRgnPos_Y + 1 };
            currentDinosaurPoints[12] = { currentRgnPos_X + 43, currentRgnPos_Y + 9 };
            currentDinosaurPoints[13] = { currentRgnPos_X + 33, currentRgnPos_Y + 9 };
            currentDinosaurPoints[14] = { currentRgnPos_X + 33, currentRgnPos_Y + 12 };
            currentDinosaurPoints[15] = { currentRgnPos_X + 40, currentRgnPos_Y + 12 };
            currentDinosaurPoints[16] = { currentRgnPos_X + 40, currentRgnPos_Y + 14 };
            currentDinosaurPoints[17] = { currentRgnPos_X + 30, currentRgnPos_Y + 14 };
            currentDinosaurPoints[18] = { currentRgnPos_X + 30, currentRgnPos_Y + 20 };
            currentDinosaurPoints[19] = { currentRgnPos_X + 35, currentRgnPos_Y + 20 };
            currentDinosaurPoints[20] = { currentRgnPos_X + 35, currentRgnPos_Y + 23 };
            currentDinosaurPoints[21] = { currentRgnPos_X + 34, currentRgnPos_Y + 23 };
            currentDinosaurPoints[22] = { currentRgnPos_X + 34, currentRgnPos_Y + 21 };
            currentDinosaurPoints[23] = { currentRgnPos_X + 30, currentRgnPos_Y + 21 };
            currentDinosaurPoints[24] = { currentRgnPos_X + 30, currentRgnPos_Y + 30 };
            currentDinosaurPoints[25] = { currentRgnPos_X + 24, currentRgnPos_Y + 36 };

            currentDinosaurPoints[26] = { currentRgnPos_X + 28, currentRgnPos_Y + 36 };
            currentDinosaurPoints[27] = { currentRgnPos_X + 28, currentRgnPos_Y + 43 };
            currentDinosaurPoints[28] = { currentRgnPos_X + 11, currentRgnPos_Y + 43 };
        }
        else
        {
            currentDinosaurPoints[0] = { currentRgnPos_X + width - 11, currentRgnPos_Y + 36 };
            currentDinosaurPoints[1] = { currentRgnPos_X + width - 1, currentRgnPos_Y + 27 };
            currentDinosaurPoints[2] = { currentRgnPos_X + width - 1, currentRgnPos_Y + 16 };
            currentDinosaurPoints[3] = { currentRgnPos_X + width - 3, currentRgnPos_Y + 13 };
            currentDinosaurPoints[4] = { currentRgnPos_X + width - 7, currentRgnPos_Y + 23 };
            currentDinosaurPoints[5] = { currentRgnPos_X + width - 11, currentRgnPos_Y + 23 };
            currentDinosaurPoints[6] = { currentRgnPos_X + width - 20, currentRgnPos_Y + 15 };
            currentDinosaurPoints[7] = { currentRgnPos_X + width - 23, currentRgnPos_Y + 15 };
            currentDinosaurPoints[8] = { currentRgnPos_X + width - 23, currentRgnPos_Y + 1 };
            currentDinosaurPoints[9] = { currentRgnPos_X + width - 25, currentRgnPos_Y + 0 };
            currentDinosaurPoints[10] = { currentRgnPos_X + width - 41, currentRgnPos_Y + 0 };
            currentDinosaurPoints[11] = { currentRgnPos_X + width - 43, currentRgnPos_Y + 1 };
            currentDinosaurPoints[12] = { currentRgnPos_X + width - 43, currentRgnPos_Y + 9 };
            currentDinosaurPoints[13] = { currentRgnPos_X + width - 33, currentRgnPos_Y + 9 };
            currentDinosaurPoints[14] = { currentRgnPos_X + width - 33, currentRgnPos_Y + 12 };
            currentDinosaurPoints[15] = { currentRgnPos_X + width - 40, currentRgnPos_Y + 12 };
            currentDinosaurPoints[16] = { currentRgnPos_X + width - 40, currentRgnPos_Y + 14 };
            currentDinosaurPoints[17] = { currentRgnPos_X + width - 30, currentRgnPos_Y + 14 };
            currentDinosaurPoints[18] = { currentRgnPos_X + width - 30, currentRgnPos_Y + 20 };
            currentDinosaurPoints[19] = { currentRgnPos_X + width - 35, currentRgnPos_Y + 20 };
            currentDinosaurPoints[20] = { currentRgnPos_X + width - 35, currentRgnPos_Y + 23 };
            currentDinosaurPoints[21] = { currentRgnPos_X + width - 34, currentRgnPos_Y + 23 };
            currentDinosaurPoints[22] = { currentRgnPos_X + width - 34, currentRgnPos_Y + 21 };
            currentDinosaurPoints[23] = { currentRgnPos_X + width - 30, currentRgnPos_Y + 21 };
            currentDinosaurPoints[24] = { currentRgnPos_X + width - 30, currentRgnPos_Y + 30 };
            currentDinosaurPoints[25] = { currentRgnPos_X + width - 24, currentRgnPos_Y + 36 };

            currentDinosaurPoints[26] = { currentRgnPos_X + width - 28, currentRgnPos_Y + 36 };
            currentDinosaurPoints[27] = { currentRgnPos_X + width - 28, currentRgnPos_Y + 43 };
            currentDinosaurPoints[28] = { currentRgnPos_X + width - 11, currentRgnPos_Y + 43 };
        }
    }
    break;

    case EDinosaurBodyState::Crawling:
    {
        if (DinosaurDirectionState == EDinosaurDirectionState::Right)
        {
            currentDinosaurPoints[0] = { currentRgnPos_X + 11, currentRgnPos_Y + 17 };
            currentDinosaurPoints[1] = { currentRgnPos_X + 1, currentRgnPos_Y + 5 };
            currentDinosaurPoints[2] = { currentRgnPos_X + 1, currentRgnPos_Y + 0 };
            currentDinosaurPoints[3] = { currentRgnPos_X + 5, currentRgnPos_Y + 3 };
            currentDinosaurPoints[4] = { currentRgnPos_X + 13, currentRgnPos_Y + 3 };
            currentDinosaurPoints[5] = { currentRgnPos_X + 16, currentRgnPos_Y + 1 };
            currentDinosaurPoints[6] = { currentRgnPos_X + 33, currentRgnPos_Y + 1 };
            currentDinosaurPoints[7] = { currentRgnPos_X + 36, currentRgnPos_Y + 3 };
            currentDinosaurPoints[8] = { currentRgnPos_X + 39, currentRgnPos_Y + 3 };
            currentDinosaurPoints[9] = { currentRgnPos_X + 41, currentRgnPos_Y + 0 };
            currentDinosaurPoints[10] = { currentRgnPos_X + 57, currentRgnPos_Y + 0 };
            currentDinosaurPoints[11] = { currentRgnPos_X + 59, currentRgnPos_Y + 1 };
            currentDinosaurPoints[12] = { currentRgnPos_X + 59, currentRgnPos_Y + 9 };
            currentDinosaurPoints[13] = { currentRgnPos_X + 49, currentRgnPos_Y + 9 };
            currentDinosaurPoints[14] = { currentRgnPos_X + 49, currentRgnPos_Y + 12 };
            currentDinosaurPoints[15] = { currentRgnPos_X + 56, currentRgnPos_Y + 12 };
            currentDinosaurPoints[16] = { currentRgnPos_X + 56, currentRgnPos_Y + 14 };
            currentDinosaurPoints[17] = { currentRgnPos_X + 42, currentRgnPos_Y + 14 };
            currentDinosaurPoints[18] = { currentRgnPos_X + 39, currentRgnPos_Y + 13 };
            currentDinosaurPoints[19] = { currentRgnPos_X + 36, currentRgnPos_Y + 13 };
            currentDinosaurPoints[20] = { currentRgnPos_X + 33, currentRgnPos_Y + 16 };
            currentDinosaurPoints[21] = { currentRgnPos_X + 33, currentRgnPos_Y + 20 };
            currentDinosaurPoints[22] = { currentRgnPos_X + 35, currentRgnPos_Y + 20 };
            currentDinosaurPoints[23] = { currentRgnPos_X + 35, currentRgnPos_Y + 21 };
            currentDinosaurPoints[24] = { currentRgnPos_X + 32, currentRgnPos_Y + 21 };
            currentDinosaurPoints[25] = { currentRgnPos_X + 32, currentRgnPos_Y + 17 };

            currentDinosaurPoints[26] = { currentRgnPos_X + 28, currentRgnPos_Y + 17 };
            currentDinosaurPoints[27] = { currentRgnPos_X + 28, currentRgnPos_Y + 25 };
            currentDinosaurPoints[28] = { currentRgnPos_X + 11, currentRgnPos_Y + 25 };
        }
        else
        {
            currentDinosaurPoints[0] = { currentRgnPos_X + width - 11, currentRgnPos_Y + 17 };
            currentDinosaurPoints[1] = { currentRgnPos_X + width - 1, currentRgnPos_Y + 5 };
            currentDinosaurPoints[2] = { currentRgnPos_X + width - 1, currentRgnPos_Y + 0 };
            currentDinosaurPoints[3] = { currentRgnPos_X + width - 5, currentRgnPos_Y + 3 };
            currentDinosaurPoints[4] = { currentRgnPos_X + width - 13, currentRgnPos_Y + 3 };
            currentDinosaurPoints[5] = { currentRgnPos_X + width - 16, currentRgnPos_Y + 1 };
            currentDinosaurPoints[6] = { currentRgnPos_X + width - 33, currentRgnPos_Y + 1 };
            currentDinosaurPoints[7] = { currentRgnPos_X + width - 36, currentRgnPos_Y + 3 };
            currentDinosaurPoints[8] = { currentRgnPos_X + width - 39, currentRgnPos_Y + 3 };
            currentDinosaurPoints[9] = { currentRgnPos_X + width - 41, currentRgnPos_Y + 0 };
            currentDinosaurPoints[10] = { currentRgnPos_X + width - 57, currentRgnPos_Y + 0 };
            currentDinosaurPoints[11] = { currentRgnPos_X + width - 59, currentRgnPos_Y + 1 };
            currentDinosaurPoints[12] = { currentRgnPos_X + width - 59, currentRgnPos_Y + 9 };
            currentDinosaurPoints[13] = { currentRgnPos_X + width - 49, currentRgnPos_Y + 9 };
            currentDinosaurPoints[14] = { currentRgnPos_X + width - 49, currentRgnPos_Y + 12 };
            currentDinosaurPoints[15] = { currentRgnPos_X + width - 56, currentRgnPos_Y + 12 };
            currentDinosaurPoints[16] = { currentRgnPos_X + width - 56, currentRgnPos_Y + 14 };
            currentDinosaurPoints[17] = { currentRgnPos_X + width - 42, currentRgnPos_Y + 14 };
            currentDinosaurPoints[18] = { currentRgnPos_X + width - 39, currentRgnPos_Y + 13 };
            currentDinosaurPoints[19] = { currentRgnPos_X + width - 36, currentRgnPos_Y + 13 };
            currentDinosaurPoints[20] = { currentRgnPos_X + width - 33, currentRgnPos_Y + 16 };
            currentDinosaurPoints[21] = { currentRgnPos_X + width - 33, currentRgnPos_Y + 20 };
            currentDinosaurPoints[22] = { currentRgnPos_X + width - 35, currentRgnPos_Y + 20 };
            currentDinosaurPoints[23] = { currentRgnPos_X + width - 35, currentRgnPos_Y + 21 };
            currentDinosaurPoints[24] = { currentRgnPos_X + width - 32, currentRgnPos_Y + 21 };
            currentDinosaurPoints[25] = { currentRgnPos_X + width - 32, currentRgnPos_Y + 17 };

            currentDinosaurPoints[26] = { currentRgnPos_X + width - 28, currentRgnPos_Y + 17 };
            currentDinosaurPoints[27] = { currentRgnPos_X + width - 28, currentRgnPos_Y + 25 };
            currentDinosaurPoints[28] = { currentRgnPos_X + width - 11, currentRgnPos_Y + 25 };
        }
    }
    break;

    default:
        break;
    }
}

// ------------ Перерисовка персонажа в новых координатах
void CDinosaur::Redraw()
{
    for (int i = 0; i < dinosaurWithLegsPointsAmount; ++i)
    {
        prevDinosaurPoints[i] = currentDinosaurPoints[i];
    }

    prevRgnPos_X = currentRgnPos_X;
    prevRgnPos_Y = currentRgnPos_Y;

    currentRgnPos_X = static_cast<int>(pos_X);
    currentRgnPos_Y = static_cast<int>(pos_Y);

    UpdateRgnPoints();

    prevRect = currentRect;

    currentRect.left = currentRgnPos_X;
    currentRect.top = currentRgnPos_Y;
    currentRect.right = currentRect.left + width * CConfig::SizeScale;
    currentRect.bottom = currentRect.top + height * CConfig::SizeScale;

    InvalidateRect(CConfig::Hwnd, &prevRect, FALSE);
    InvalidateRect(CConfig::Hwnd, &currentRect, FALSE);
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

    //Левая нога
    Rectangle(hdc, pos_x + 12 * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale, pos_x + 22 * CConfig::SizeScale, pos_y + 44 * CConfig::SizeScale);

    //Правая нога
    Rectangle(hdc, pos_x + 22 * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale, pos_x + 28 * CConfig::SizeScale, pos_y + 44 * CConfig::SizeScale);
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

    Polygon(hdc, currentDinosaurPoints, dinosaurBodyPointsAmount);

    //Фоновые пропуски
    CConfig::backgroundColor.SelectColor(hdc);

    //Глаз
    Rectangle(hdc, currentRgnPos_X + 27 * CConfig::SizeScale, currentRgnPos_Y + 2 * CConfig::SizeScale, currentRgnPos_X + 31 * CConfig::SizeScale, currentRgnPos_Y + 6 * CConfig::SizeScale);
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка тела в обычном состоянии влево
void CDinosaur::DrawLeftStanding(HDC hdc)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    Polygon(hdc, currentDinosaurPoints, dinosaurBodyPointsAmount);

    CConfig::backgroundColor.SelectColor(hdc);

    //Глаз
    Rectangle(hdc, currentRgnPos_X + (width - 27) * CConfig::SizeScale, currentRgnPos_Y + (2 * CConfig::SizeScale), currentRgnPos_X + (width - 31) * CConfig::SizeScale, currentRgnPos_Y + (6 * CConfig::SizeScale));
}
// -----------------------------------------------------------------------------------

// ----------- Отрисовка тела в присяде
void CDinosaur::DrawRightCrawling(HDC hdc)
{
    CConfig::mainBrightColor.SelectColor(hdc);
                                  
    Polygon(hdc, currentDinosaurPoints, dinosaurBodyPointsAmount);

    //Фоновые пропуски
    CConfig::backgroundColor.SelectColor(hdc);

    //Глаз
    Rectangle(hdc, currentRgnPos_X + 43 * CConfig::SizeScale, currentRgnPos_Y + 2 * CConfig::SizeScale, currentRgnPos_X + 47 * CConfig::SizeScale, currentRgnPos_Y + 6 * CConfig::SizeScale);
}
// -----------------------------------------------------------------------------------

// ----------- Отрисовка тела в присяде влево ----------------------------------------
void CDinosaur::DrawLeftCrawling(HDC hdc)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    Polygon(hdc, currentDinosaurPoints, dinosaurBodyPointsAmount);

    //Фоновые пропуски
    CConfig::backgroundColor.SelectColor(hdc);

    //Глаз
    Rectangle(hdc, currentRgnPos_X + width - 43 * CConfig::SizeScale, currentRgnPos_Y + 2 * CConfig::SizeScale, currentRgnPos_X + width - 47 * CConfig::SizeScale, currentRgnPos_Y + 6 * CConfig::SizeScale);
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
    //DinosaurMovingState = EDinosaurMovingState::MovingRight;
}

void CDinosaur::CorrectVerticalEdgePosition()
{
    if (onStartPlatform == true)  //Прекращаем падать, если находимся на платформе
        OnGroundLegsPos_Y = static_cast<int>(CStartPlatform::pos_Y); //Нормальная позиция ног Дино на платформе
    else 
        OnGroundLegsPos_Y = (StandingPos_Y + StandingHeight); //Нормальная позиция ног Дино на земле

    if (static_cast<int>(pos_Y) + height >= OnGroundLegsPos_Y) //Двигаемся вниз до тех пор, пока Дино не достигнет земли (или платформы)
    {
        pos_Y = static_cast<float>(OnGroundLegsPos_Y - height);
        falling = false;
    }

    if (static_cast<int>(pos_Y) <= OnGroundLegsPos_Y - height - MaxJumpHeight * CConfig::SizeScale && falling == false) //Когда Дино достигает максимальной высоты прыжка (или чуть больше), меняем знак шага перемещения на положительный для движения вниз (падения)
    {
        falling = true;
        verticalSpeed = 0.0f; //При достижении максимальной высоты перемещение приравниваем к 0 
    }
}

// ------------ Перемещение по вертикали (падение вниз или движение вверх при прыжке) (работает по таймеру)
void CDinosaur::MoveVertical(float maxSpeed)
{
    if (static_cast<int>(pos_Y) + height == OnGroundLegsPos_Y) //Если Дино на земле, ничего не делаем
        return;

    float nextStep = verticalSpeed / maxSpeed * CConfig::minShift;

    pos_Y += nextStep;
}
// -----------------------------------------------------------------------------------

// ------------  Горизонтальное движение по таймеру 
void CDinosaur::CorrectHorizontalEdgePosition()
{
    if (static_cast<int>(pos_X) + width * CConfig::SizeScale >= CConfig::rightBorder) //Правая граница
        pos_X = static_cast<float>(CConfig::rightBorder - width * CConfig::SizeScale);

    if (static_cast<int>(pos_X) < CConfig::leftBorder) //Левая граница
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
        if (DinosaurLevelState == EDinosaurLevelState::StartLevel || DinosaurLevelState == EDinosaurLevelState::TestLevel) //Останавка при отжатии нужуна только в состояниях, где мы можем двигаться клавишами. При RunLevel просто шевеляться ноги
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
    if (static_cast<int>(pos_Y) + height == OnGroundLegsPos_Y)
    {
        pos_Y -= 1.0f;
        verticalSpeed = -MaxSpeed_Y;

        //Beep(300, 50); //TO DO: Перенести обработку звука в отдельный поток, чтобы не вызывало задержку
    }
}
// -----------------------------------------------------------------------------------

// ------------ Модель Динозавра поделена на 3 прямоугольника, с которыми проверяем столкновения других объектов
void CDinosaur::SetDinoCollisionRects()
{
    //Если координаты не поменялись, ничего не делаем
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

// ------------ Падение под действием "гравитации" (корректируем вертикальную позицию Дино каждый кадр (опускаем вниз))
void CDinosaur::GravityFalling()
{
    if (DinosaurLevelState == EDinosaurLevelState::Teleporting)
        return;
        
    verticalSpeed += 7.15f;
}
// -----------------------------------------------------------------------------------

// ------------ Учитываем положение стартовой платформы
void CDinosaur::CorrectPositionWithStartPlatform(const CStartPlatform& startPlatform)
{
    if (static_cast<int>(pos_X) + width > static_cast<int>(startPlatform.pos_X) && static_cast<int>(pos_X) < static_cast<int>(startPlatform.pos_X) + startPlatform.topWidth) //Проверка по Х координате для столкновения
    {
        if (onStartPlatform == false)
        {
            if (horizontalSpeed > 0) //Если движемся вправо (подходим слева), то упираемся в платформу
                pos_X = startPlatform.pos_X - width;
            else if (horizontalSpeed < 0) //Если движемся влево (подходим справа), то упираемся в платформу
                pos_X = startPlatform.pos_X + static_cast<float>(startPlatform.topWidth);
    
            if (static_cast<int>(pos_Y) + height <= static_cast<int>(startPlatform.pos_Y)) //Проверка по Y координате (для возможности запрыгнуть/перепрыгнуть)
                onStartPlatform = true;
        }
    }
    else
        onStartPlatform = false;
}
// -----------------------------------------------------------------------------------

void CDinosaur::TeleportingFromStartPlatfrom() //TO DO:!!!
{
    

    //if (DinosaurLevelState == EDinosaurLevelState::Teleporting)


}

// ------------ Рестарт уровня при проигрыше или со стартовой платформы
void CDinosaur::RestartLevel()
{
    DinosaurLevelState = EDinosaurLevelState::RestartRunLevel;
    horizontalSpeed = 0.0f;
    verticalSpeed = 0.0f;
    SetBodyState(EDinosaurBodyState::Standing);
    DinosaurMovingState = EDinosaurMovingState::Stop;
    DinosaurDirectionState = EDinosaurDirectionState::Right;
    pos_X = startPos_X;
    pos_Y = (static_cast<float>(StandingPos_Y));
    collision = false;
    
    onStartPlatform = false;
}
// -----------------------------------------------------------------------------------

// ------------ Проверка условий для возможности начать игру со стартовой платформы (нажать клавишу Е)
bool CDinosaur::ReadyForStartPlatfrom(const CStartPlatform& startPlatform)
{
    bool ready = true;
    ready = ready && ( static_cast<int>(pos_Y) + height == static_cast<int>(startPlatform.pos_Y) );
    ready = ready && ( static_cast<int>(pos_X) > static_cast<int>(startPlatform.pos_X) + (startPlatform.topWidth - startPlatform.downWidth) / 2 );
    ready = ready && ( static_cast<int>(pos_X) + width < static_cast<int>(startPlatform.pos_X) + startPlatform.downWidth );
    ready = ready && DinosaurBodyState == EDinosaurBodyState::Standing;

    return ready;
}