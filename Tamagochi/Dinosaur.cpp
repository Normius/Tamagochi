#include "Dinosaur.h"

// ---------------------------- Класс персонажа Dino -------------------------------------------------------------

// ------------ Конструктор
CDinosaur::CDinosaur()
    : DinosaurBodyState(EDinosaurBodyState::Standing), DinosaurDirectionState(EDinosaurDirectionState::Right), DinosaurMovingState(EDinosaurMovingState::Stop),
    DinosaurLevelState(EDinosaurLevelState::FreeMovingLevel), leftKeyDown(false), rightKeyDown(false), height(StandingHeight), width(StandingWidth),
    pos_X(0.0f), pos_Y(static_cast<float>(OnGroundPos_Y)), horizontalSpeed(0.0f), verticalSpeed(0.0f), dinoRect{}, prevDinoRect{}
{
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка персонажа Dino (основной метод)
void CDinosaur::Draw(HDC hdc, RECT& paintArea)
{
    RECT intersectionRect; //Нужен для ф-ции проверки пересечения прямоугольников, в него сохраняется область пересечения или 0

    //TO DO: Возможно придётся добавить очистку фона вручную, а не значению TRUE в InvalidateRect(CConfig::Hwnd, &prevDinoRect, TRUE);

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
            DrawRightHead(hdc);
            DrawRightStandingLegs(hdc);

            if (pos_Y == OnGroundPos_Y)
                MoveLegsRight(hdc);
        }
        else
        {
            //Драко стоит (влево)
            DrawLeftStanding(hdc);
            DrawLeftHead(hdc);
            DrawLeftStandingLegs(hdc);

            if (pos_Y == OnGroundPos_Y)
                MoveLegsLeft(hdc);
        }
    }
    break;
    case EDinosaurBodyState::Crawling:
    {
        if (DinosaurDirectionState == EDinosaurDirectionState::Right)
        {
            //Драко в присяде (вправо)
            DrawRightCrawling(hdc);
            DrawRightHead(hdc);     //Смещаем отрисовку головы для приседа
            DrawRightStandingLegs(hdc);

            if (pos_Y == OnGroundPos_Y)
                MoveLegsRight(hdc);
        }
        else
        {
            //Драко в присяде (влево)
            DrawLeftCrawling(hdc);
            DrawLeftHead(hdc); //Смещаем отрисовку головы для приседа
            DrawLeftStandingLegs(hdc);

            if (pos_Y == OnGroundPos_Y)
                MoveLegsLeft(hdc);
        }
    }
    break;

    default:
        break;
    }

    //Столкновение Драко с препятствием и анимация глаз
    bool collision = false;
    if (collision == true)
    {
        DrawRightEye(hdc);
    }
}
// -----------------------------------------------------------------------------------

// ------------ Перерисовка персонажа в новых координатах
void CDinosaur::Redraw()
{
    prevDinoRect = dinoRect;

    if (DinosaurBodyState == EDinosaurBodyState::Standing) //Прямоугольник для Дино в положении стоя
    {
        dinoRect.left = static_cast<int>(pos_X);
        dinoRect.top = static_cast<int>(pos_Y);
        dinoRect.right = dinoRect.left + width * CConfig::SizeScale;
        dinoRect.bottom = dinoRect.top + height * CConfig::SizeScale;
    }
    else //Прямоугольник для Дино в положении присяда
    {
        dinoRect.left = static_cast<int>(pos_X);
        dinoRect.top = static_cast<int>(pos_Y) + (StandingHeight - CrawlingHeight) * CConfig::SizeScale;
        dinoRect.right = dinoRect.left + width * CConfig::SizeScale;
        dinoRect.bottom = dinoRect.top + height * CConfig::SizeScale;
    }

    InvalidateRect(CConfig::Hwnd, &prevDinoRect, TRUE);
    InvalidateRect(CConfig::Hwnd, &dinoRect, TRUE);
}
// -----------------------------------------------------------------------------------

// ------------ Очистка фона для перерисовки
void CDinosaur::ClearRightLegsBackground(HDC hdc)
{
    //Очищаем фон ног
    CConfig::backgroundColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

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

    //Левая нога
    Rectangle(hdc, pos_x + (width - 12) * CConfig::SizeScale, pos_y + (36 * CConfig::SizeScale), pos_x + (width - 18) * CConfig::SizeScale, pos_y + (44 * CConfig::SizeScale));

    //Правая нога
    Rectangle(hdc, pos_x + (width - 22) * CConfig::SizeScale, pos_y + (36 * CConfig::SizeScale), pos_x + (width - 28) * CConfig::SizeScale, pos_y + (44 * CConfig::SizeScale));
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка ног стоя
void CDinosaur::DrawRightStandingLegs(HDC hdc)
{
    //ClearRightLegsBackground(hdc);

    //Рисуем ноги
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

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
    //ClearLeftLegsBackground(hdc);

    //Рисуем ноги
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

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

    //Левая нога обычно
    Rectangle(hdc, pos_x + 12 * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale, pos_x + 15 * CConfig::SizeScale, pos_y + 44 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 15 * CConfig::SizeScale, pos_y + 42 * CConfig::SizeScale, pos_x + 18 * CConfig::SizeScale, pos_y + 44 * CConfig::SizeScale);

    //Правая нога поднятая
    Rectangle(hdc, pos_x + 22 * CConfig::SizeScale, pos_y + (36 - 4) * CConfig::SizeScale, pos_x + 25 * CConfig::SizeScale, pos_y + (44 - 4) * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 25 * CConfig::SizeScale, pos_y + (42 - 4) * CConfig::SizeScale, pos_x + 28 * CConfig::SizeScale, pos_y + (44 - 4) * CConfig::SizeScale);
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

    //Левая нога обычно
    Rectangle(hdc, pos_x + (width - 12) * CConfig::SizeScale, pos_y + (36 * CConfig::SizeScale), pos_x + (width - 15) * CConfig::SizeScale, pos_y + (44 * CConfig::SizeScale));
    Rectangle(hdc, pos_x + (width - 15) * CConfig::SizeScale, pos_y + (42 * CConfig::SizeScale), pos_x + (width - 18) * CConfig::SizeScale, pos_y + (44 * CConfig::SizeScale));

    //Правая нога поднятая
    Rectangle(hdc, pos_x + (width - 22) * CConfig::SizeScale, pos_y + (36 - 4) * CConfig::SizeScale, pos_x + (width - 25) * CConfig::SizeScale, pos_y + (44 - 4) * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (width - 25) * CConfig::SizeScale, pos_y + (42 - 4) * CConfig::SizeScale, pos_x + (width - 28) * CConfig::SizeScale, pos_y + (44 - 4) * CConfig::SizeScale);
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

    //Левая нога поднятая
    Rectangle(hdc, pos_x + 12 * CConfig::SizeScale, pos_y + (36 - 4) * CConfig::SizeScale, pos_x + 15 * CConfig::SizeScale, pos_y + (44 - 4) * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 15 * CConfig::SizeScale, pos_y + (42 - 4) * CConfig::SizeScale, pos_x + 18 * CConfig::SizeScale, pos_y + (44 - 4) * CConfig::SizeScale);

    //Правая нога обычно
    Rectangle(hdc, pos_x + 22 * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale, pos_x + 25 * CConfig::SizeScale, pos_y + 44 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 25 * CConfig::SizeScale, pos_y + 42 * CConfig::SizeScale, pos_x + 28 * CConfig::SizeScale, pos_y + 44 * CConfig::SizeScale);
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

    //Зрачок при столкновении
    Rectangle(hdc, pos_x + 28 * CConfig::SizeScale, pos_y + 2 * CConfig::SizeScale, pos_x + 29 * CConfig::SizeScale, pos_y + 5 * CConfig::SizeScale);
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка зрачка при стоклновении влево
void CDinosaur::DrawLeftEye(HDC hdc)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    //Зрачок при столкновении
    Rectangle(hdc, pos_x + (width - 28) * CConfig::SizeScale, pos_y + 2 * CConfig::SizeScale, pos_x + (width - 29) * CConfig::SizeScale, pos_y + 5 * CConfig::SizeScale);
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка тела в обычном состоянии
void CDinosaur::DrawRightStanding(HDC hdc)
{
    //DinoHeight = standingDinoHeight;
    //DinoWidth = standingDinoWidth;

    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    //Тело
    Rectangle(hdc, pos_x + 11 * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale, pos_x + 31 * CConfig::SizeScale, pos_y + 15 * CConfig::SizeScale);

    //Лапки
    Rectangle(hdc, pos_x + 31 * CConfig::SizeScale, pos_y + 20 * CConfig::SizeScale, pos_x + 36 * CConfig::SizeScale, pos_y + 24 * CConfig::SizeScale);

    //Хвост
    Rectangle(hdc, pos_x, pos_y + 13 * CConfig::SizeScale, pos_x + 11 * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale);

    //Фоновые пропуски
    CConfig::backgroundColor.SelectColor(hdc);

    //Лапки
    Rectangle(hdc, pos_x + 31 * CConfig::SizeScale, pos_y + 22 * CConfig::SizeScale, pos_x + 34 * CConfig::SizeScale, pos_y + 24 * CConfig::SizeScale);

    //Хвост
    Rectangle(hdc, pos_x + 4 * CConfig::SizeScale, pos_y + 12 * CConfig::SizeScale, pos_x + 6 * CConfig::SizeScale, pos_y + 16 * CConfig::SizeScale);
    Rectangle(hdc, pos_x, pos_y + 12 * CConfig::SizeScale, pos_x + 1 * CConfig::SizeScale, pos_y + 16 * CConfig::SizeScale);

    //Тело спереди
    Rectangle(hdc, pos_x + 30 * CConfig::SizeScale, pos_y + 31 * CConfig::SizeScale, pos_x + 33 * CConfig::SizeScale, pos_y + 34 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 28 * CConfig::SizeScale, pos_y + 33 * CConfig::SizeScale, pos_x + 33 * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 26 * CConfig::SizeScale, pos_y + 35 * CConfig::SizeScale, pos_x + 33 * CConfig::SizeScale, pos_y + 39 * CConfig::SizeScale);

    //Тело сзади
    Rectangle(hdc, pos_x, pos_y + 30 * CConfig::SizeScale, pos_x + 4 * CConfig::SizeScale, pos_y + 32 * CConfig::SizeScale);
    Rectangle(hdc, pos_x, pos_y + 32 * CConfig::SizeScale, pos_x + 6 * CConfig::SizeScale, pos_y + 34 * CConfig::SizeScale);
    Rectangle(hdc, pos_x, pos_y + 28 * CConfig::SizeScale, pos_x + 2 * CConfig::SizeScale, pos_y + 30 * CConfig::SizeScale);
    Rectangle(hdc, pos_x, pos_y + 34 * CConfig::SizeScale, pos_x + 9 * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale);


    //На спине
    Rectangle(hdc, pos_x + 6 * CConfig::SizeScale, pos_y + 13 * CConfig::SizeScale, pos_x + 18 * CConfig::SizeScale, pos_y + 17 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 6 * CConfig::SizeScale, pos_y + 17 * CConfig::SizeScale, pos_x + 16 * CConfig::SizeScale, pos_y + 19 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 6 * CConfig::SizeScale, pos_y + 19 * CConfig::SizeScale, pos_x + 14 * CConfig::SizeScale, pos_y + 21 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 7 * CConfig::SizeScale, pos_y + 21 * CConfig::SizeScale, pos_x + 12 * CConfig::SizeScale, pos_y + 23 * CConfig::SizeScale);
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка тела в обычном состоянии влево
void CDinosaur::DrawLeftStanding(HDC hdc)
{
    //DinoHeight = standingDinoHeight;
    //DinoWidth = standingDinoWidth;

    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    //Тело
    Rectangle(hdc, pos_x + (width - 11) * CConfig::SizeScale, pos_y + (36 * CConfig::SizeScale), pos_x + (width - 31) * CConfig::SizeScale, pos_y + (15 * CConfig::SizeScale));

    //Лапки
    Rectangle(hdc, pos_x + (width - 31) * CConfig::SizeScale, pos_y + (20 * CConfig::SizeScale), pos_x + (width - 36) * CConfig::SizeScale, pos_y + (24 * CConfig::SizeScale));

    //Хвост
    Rectangle(hdc, pos_x + (width * CConfig::SizeScale), pos_y + (13 * CConfig::SizeScale), pos_x + (width - 11) * CConfig::SizeScale, pos_y + (36 * CConfig::SizeScale));

    //Фоновые пропуски (контур динозавра)
    CConfig::backgroundColor.SelectColor(hdc);

    //Лапки
    Rectangle(hdc, pos_x + (width - 31) * CConfig::SizeScale, pos_y + (22 * CConfig::SizeScale), pos_x + (width - 34) * CConfig::SizeScale, pos_y + (24 * CConfig::SizeScale));

    //Хвост
    Rectangle(hdc, pos_x + (width - 4) * CConfig::SizeScale, pos_y + (12 * CConfig::SizeScale), pos_x + (width - 6) * CConfig::SizeScale, pos_y + (16 * CConfig::SizeScale));
    Rectangle(hdc, pos_x + (width * CConfig::SizeScale), pos_y + (12 * CConfig::SizeScale), pos_x + (width - 1) * CConfig::SizeScale, pos_y + (16 * CConfig::SizeScale));

    //Тело спереди
    Rectangle(hdc, pos_x + (width - 30) * CConfig::SizeScale, pos_y + (31 * CConfig::SizeScale), pos_x + (width - 33) * CConfig::SizeScale, pos_y + (34 * CConfig::SizeScale));
    Rectangle(hdc, pos_x + (width - 28) * CConfig::SizeScale, pos_y + (33 * CConfig::SizeScale), pos_x + (width - 33) * CConfig::SizeScale, pos_y + (36 * CConfig::SizeScale));
    Rectangle(hdc, pos_x + (width - 26) * CConfig::SizeScale, pos_y + (35 * CConfig::SizeScale), pos_x + (width - 33) * CConfig::SizeScale, pos_y + (39 * CConfig::SizeScale));

    //Тело сзади
    Rectangle(hdc, pos_x + (width * CConfig::SizeScale), pos_y + (30 * CConfig::SizeScale), pos_x + (width - 4) * CConfig::SizeScale, pos_y + (32 * CConfig::SizeScale));
    Rectangle(hdc, pos_x + (width * CConfig::SizeScale), pos_y + (32 * CConfig::SizeScale), pos_x + (width - 6) * CConfig::SizeScale, pos_y + (34 * CConfig::SizeScale));
    Rectangle(hdc, pos_x + (width * CConfig::SizeScale), pos_y + (28 * CConfig::SizeScale), pos_x + (width - 2) * CConfig::SizeScale, pos_y + (30 * CConfig::SizeScale));
    Rectangle(hdc, pos_x + (width * CConfig::SizeScale), pos_y + (34 * CConfig::SizeScale), pos_x + (width - 9) * CConfig::SizeScale, pos_y + (36 * CConfig::SizeScale));

    //На спине
    Rectangle(hdc, pos_x + (width - 6) * CConfig::SizeScale, pos_y + (13 * CConfig::SizeScale), pos_x + (width - 18) * CConfig::SizeScale, pos_y + (17 * CConfig::SizeScale));
    Rectangle(hdc, pos_x + (width - 6) * CConfig::SizeScale, pos_y + (17 * CConfig::SizeScale), pos_x + (width - 16) * CConfig::SizeScale, pos_y + (19 * CConfig::SizeScale));
    Rectangle(hdc, pos_x + (width - 6) * CConfig::SizeScale, pos_y + (19 * CConfig::SizeScale), pos_x + (width - 14) * CConfig::SizeScale, pos_y + (21 * CConfig::SizeScale));
    Rectangle(hdc, pos_x + (width - 7) * CConfig::SizeScale, pos_y + (21 * CConfig::SizeScale), pos_x + (width - 12) * CConfig::SizeScale, pos_y + (23 * CConfig::SizeScale));
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка головы влево
void CDinosaur::DrawRightHead(HDC hdc)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    if (DinosaurBodyState == EDinosaurBodyState::Crawling)
    {
        pos_y += (StandingHeight - CrawlingHeight) * CConfig::SizeScale;
        pos_x += (CrawlingWidth - StandingWidth) * CConfig::SizeScale;
    }

    //Голова
    Rectangle(hdc, pos_x + 23 * CConfig::SizeScale, pos_y, pos_x + 44 * CConfig::SizeScale, pos_y + 15 * CConfig::SizeScale);

    CConfig::backgroundColor.SelectColor(hdc);

    //Голова
    Rectangle(hdc, pos_x + 34 * CConfig::SizeScale, pos_y + 10 * CConfig::SizeScale, pos_x + 44 * CConfig::SizeScale, pos_y + 12 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 41 * CConfig::SizeScale, pos_y + 12 * CConfig::SizeScale, pos_x + 44 * CConfig::SizeScale, pos_y + 15 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 23 * CConfig::SizeScale, pos_y, pos_x + 25 * CConfig::SizeScale, pos_y + 1 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 42 * CConfig::SizeScale, pos_y, pos_x + 44 * CConfig::SizeScale, pos_y + 1 * CConfig::SizeScale);

    //Глаз
    Rectangle(hdc, pos_x + 27 * CConfig::SizeScale, pos_y + 2 * CConfig::SizeScale, pos_x + 30 * CConfig::SizeScale, pos_y + 5 * CConfig::SizeScale);
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка головы
void CDinosaur::DrawLeftHead(HDC hdc)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    if (DinosaurBodyState == EDinosaurBodyState::Crawling)
    {
        pos_y += (StandingHeight - CrawlingHeight) * CConfig::SizeScale;
        pos_x += (StandingWidth - CrawlingWidth) * CConfig::SizeScale;
    }

    //Голова
    Rectangle(hdc, pos_x + (width - 23) * CConfig::SizeScale, pos_y, pos_x + (width - 44) * CConfig::SizeScale, pos_y + 15 * CConfig::SizeScale);

    CConfig::backgroundColor.SelectColor(hdc);

    //Голова
    Rectangle(hdc, pos_x + (width - 34) * CConfig::SizeScale, pos_y + 10 * CConfig::SizeScale, pos_x + (width - 44) * CConfig::SizeScale, pos_y + 12 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (width - 41) * CConfig::SizeScale, pos_y + 12 * CConfig::SizeScale, pos_x + (width - 44) * CConfig::SizeScale, pos_y + 15 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (width - 23) * CConfig::SizeScale, pos_y, pos_x + (width - 25) * CConfig::SizeScale, pos_y + 1 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (width - 42) * CConfig::SizeScale, pos_y, pos_x + (width - 44) * CConfig::SizeScale, pos_y + 1 * CConfig::SizeScale);

    //Глаз
    Rectangle(hdc, pos_x + (width - 27) * CConfig::SizeScale, pos_y + (2 * CConfig::SizeScale), pos_x + (width - 30) * CConfig::SizeScale, pos_y + (5 * CConfig::SizeScale));
}
// -----------------------------------------------------------------------------------

// ----------- Отрисовка тела в присяде
void CDinosaur::DrawRightCrawling(HDC hdc)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    //Тело
    Rectangle(hdc, pos_x, pos_y + 18 * CConfig::SizeScale, pos_x + 39 * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale);

    //Лапы
    Rectangle(hdc, pos_x + 32 * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale, pos_x + 34 * CConfig::SizeScale, pos_y + 40 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 33 * CConfig::SizeScale, pos_y + 38 * CConfig::SizeScale, pos_x + 36 * CConfig::SizeScale, pos_y + 40 * CConfig::SizeScale);

    //Рисуем пропуски фоновые(контур динозавра)
    CConfig::backgroundColor.SelectColor(hdc);

    //Тело спереди
    Rectangle(hdc, pos_x + 36 * CConfig::SizeScale, pos_y + 32 * CConfig::SizeScale, pos_x + 39 * CConfig::SizeScale, pos_y + 34 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 34 * CConfig::SizeScale, pos_y + 34 * CConfig::SizeScale, pos_x + 39 * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale);

    //Тело сзади
    Rectangle(hdc, pos_x, pos_y + 24 * CConfig::SizeScale, pos_x + 1 * CConfig::SizeScale, pos_y + 26 * CConfig::SizeScale);
    Rectangle(hdc, pos_x, pos_y + 26 * CConfig::SizeScale, pos_x + 2 * CConfig::SizeScale, pos_y + 28 * CConfig::SizeScale);
    Rectangle(hdc, pos_x, pos_y + 28 * CConfig::SizeScale, pos_x + 4 * CConfig::SizeScale, pos_y + 30 * CConfig::SizeScale);
    Rectangle(hdc, pos_x, pos_y + 30 * CConfig::SizeScale, pos_x + 6 * CConfig::SizeScale, pos_y + 32 * CConfig::SizeScale);
    Rectangle(hdc, pos_x, pos_y + 32 * CConfig::SizeScale, pos_x + 8 * CConfig::SizeScale, pos_y + 34 * CConfig::SizeScale);
    Rectangle(hdc, pos_x, pos_y + 34 * CConfig::SizeScale, pos_x + 10 * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale);

    //На спине
    Rectangle(hdc, pos_x + 2 * CConfig::SizeScale, pos_y + 18 * CConfig::SizeScale, pos_x + 39 * CConfig::SizeScale, pos_y + 19 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 3 * CConfig::SizeScale, pos_y + 18 * CConfig::SizeScale, pos_x + 16 * CConfig::SizeScale, pos_y + 20 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 5 * CConfig::SizeScale, pos_y + 20 * CConfig::SizeScale, pos_x + 14 * CConfig::SizeScale, pos_y + 21 * CConfig::SizeScale);

    Rectangle(hdc, pos_x + 34 * CConfig::SizeScale, pos_y + 18 * CConfig::SizeScale, pos_x + 39 * CConfig::SizeScale, pos_y + 20 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 36 * CConfig::SizeScale, pos_y + 20 * CConfig::SizeScale, pos_x + 39 * CConfig::SizeScale, pos_y + 21 * CConfig::SizeScale);
}
// -----------------------------------------------------------------------------------

// ----------- Отрисовка тела в присяде влево ----------------------------------------
void CDinosaur::DrawLeftCrawling(HDC hdc)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    //Тело
    Rectangle(hdc, pos_x + (CrawlingWidth * CConfig::SizeScale), pos_y + 18 * CConfig::SizeScale, pos_x + (CrawlingWidth - 39) * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale);

    //Лапы
    Rectangle(hdc, pos_x + (CrawlingWidth - 32) * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale, pos_x + (CrawlingWidth - 34) * CConfig::SizeScale, pos_y + 40 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (CrawlingWidth - 33) * CConfig::SizeScale, pos_y + 38 * CConfig::SizeScale, pos_x + (CrawlingWidth - 36) * CConfig::SizeScale, pos_y + 40 * CConfig::SizeScale);

    //Рисуем пропуски фоновые
    CConfig::backgroundColor.SelectColor(hdc);

    //Тело спереди
    Rectangle(hdc, pos_x + (CrawlingWidth - 36) * CConfig::SizeScale, pos_y + 32 * CConfig::SizeScale, pos_x + (CrawlingWidth - 39) * CConfig::SizeScale, pos_y + 34 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (CrawlingWidth - 34) * CConfig::SizeScale, pos_y + 34 * CConfig::SizeScale, pos_x + (CrawlingWidth - 39) * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale);

    //Тело сзади
    Rectangle(hdc, pos_x + (CrawlingWidth * CConfig::SizeScale), pos_y + 24 * CConfig::SizeScale, pos_x + (CrawlingWidth - 1) * CConfig::SizeScale, pos_y + 26 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (CrawlingWidth * CConfig::SizeScale), pos_y + 26 * CConfig::SizeScale, pos_x + (CrawlingWidth - 2) * CConfig::SizeScale, pos_y + 28 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (CrawlingWidth * CConfig::SizeScale), pos_y + 28 * CConfig::SizeScale, pos_x + (CrawlingWidth - 4) * CConfig::SizeScale, pos_y + 30 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (CrawlingWidth * CConfig::SizeScale), pos_y + 30 * CConfig::SizeScale, pos_x + (CrawlingWidth - 6) * CConfig::SizeScale, pos_y + 32 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (CrawlingWidth * CConfig::SizeScale), pos_y + 32 * CConfig::SizeScale, pos_x + (CrawlingWidth - 8) * CConfig::SizeScale, pos_y + 34 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (CrawlingWidth * CConfig::SizeScale), pos_y + 34 * CConfig::SizeScale, pos_x + (CrawlingWidth - 10) * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale);

    //На спине
    Rectangle(hdc, pos_x + (CrawlingWidth - 2) * CConfig::SizeScale, pos_y + 18 * CConfig::SizeScale, pos_x + (CrawlingWidth - 39) * CConfig::SizeScale, pos_y + 19 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (CrawlingWidth - 3) * CConfig::SizeScale, pos_y + 18 * CConfig::SizeScale, pos_x + (CrawlingWidth - 16) * CConfig::SizeScale, pos_y + 20 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (CrawlingWidth - 5) * CConfig::SizeScale, pos_y + 20 * CConfig::SizeScale, pos_x + (CrawlingWidth - 14) * CConfig::SizeScale, pos_y + 21 * CConfig::SizeScale);

    Rectangle(hdc, pos_x + (CrawlingWidth - 34) * CConfig::SizeScale, pos_y + 18 * CConfig::SizeScale, pos_x + (CrawlingWidth - 39) * CConfig::SizeScale, pos_y + 20 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (CrawlingWidth - 36) * CConfig::SizeScale, pos_y + 20 * CConfig::SizeScale, pos_x + (CrawlingWidth - 39) * CConfig::SizeScale, pos_y + 21 * CConfig::SizeScale);
}
// -----------------------------------------------------------------------------------

// ------------ Анимация ног при движении вправо
void CDinosaur::MoveLegsRight(HDC hdc)
{
    if (static_cast<int>(CConfig::MovingLegsSpeed) % 2 == 0) //TO DO: Исправить скорость движения левой и правой ногой. Это условие подходит только для 10 фпс
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
    if (static_cast<int>(CConfig::MovingLegsSpeed) % 2 == 0) //TO DO: Исправить скорость движения левой и правой ногой
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
        DinosaurBodyState = EDinosaurBodyState::Crawling;
        height = CrawlingHeight;
        width = CrawlingWidth;
    }
    else
    {
        DinosaurBodyState = EDinosaurBodyState::Standing;
        height = StandingHeight;
        width = StandingWidth;
    }

    Redraw();
}
// -----------------------------------------------------------------------------------

// ------------ Перемещение по вертикали (падение вниз или движение вверх при прыжке) (работает по таймеру)
void CDinosaur::MoveVertical(float maxSpeed)
{
    if (static_cast<int>(pos_Y) == OnGroundPos_Y) //Если Дино на земле, ничего не делаем
        return;

    verticalSpeed += 2.07f; //Увеличиваем сдвиг при падении, то есть ускоряемся при движении вниз (значение подобрано вручную)
    //pos_Y += verticalSpeed * CConfig::FSizeScale;

    //TO DO добавить логику маленьких смещений
    float restDistance = maxSpeed;

    while (restDistance > 0.0f)
    {
        //Сдвиг на небольшой шаг
        float nextStep = verticalSpeed / maxSpeed * CConfig::minShift; //Вычисляем минимальный шаг для перемещения Дино (Делим скорость Дино на максимальную скорость в игреЕсли они равны, то смещаем на минимальный шаг. Если есть большая скорость, то будем смещать на меньший шаг. Но в итоге количество сдвигов будет тем же. (Синхронизация объектов)
        pos_Y += nextStep;

        restDistance -= CConfig::minShift;
    }

    if (static_cast<int>(pos_Y) >= OnGroundPos_Y) //Двигаемся вниз до тех пор, пока Дино не достигнет земли
        pos_Y = OnGroundPos_Y;

    //TO DO: В зависимости от масштаба scale обнуление происходит по-разному, нужно будет исправить
    if (static_cast<int>(pos_Y) <= OnGroundPos_Y - MaxJumpHeight * CConfig::SizeScale) //Когда Дино достигает максимальной высоты прыжка (или чуть больше), меняем знак шага перемещения на положительный для движения вниз (падения)
        verticalSpeed = 0.0f; //При достижении максимальной высоты перемещение приравниваем к 0 
}
// -----------------------------------------------------------------------------------

// ------------  Горизонтальное движение по таймеру 
void CDinosaur::MoveHorizontal(float maxSpeed)
{
    if (horizontalSpeed == 0.0f) //Если скорость = 0, ничего не делаем
        return;

    //Смещение на небольшие шажки 
    float restDistance = maxSpeed;

    while (restDistance > 0.0f)
    {
        //Сдвиг на небольшой шаг
        float nextStep = horizontalSpeed / maxSpeed * CConfig::minShift; //Вычисляем минимальный шаг для перемещения Дино (Делим скорость Дино на максимальную скорость в игреЕсли они равны, то смещаем на минимальный шаг. Если есть большая скорость, то будем смещать на меньший шаг. Но в итоге количество сдвигов будет тем же. (Синхронизация объектов)
        pos_X += nextStep;

        restDistance -= CConfig::minShift;
    }

    if (static_cast<int>(pos_X) >= CConfig::rightBorder - width * CConfig::SizeScale)
        pos_X = static_cast<float>(CConfig::rightBorder - width * CConfig::SizeScale);

    if (static_cast<int>(pos_X) <= CConfig::leftBorder)
        pos_X = static_cast<float>(CConfig::leftBorder);
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
        DinosaurMovingState = EDinosaurMovingState::Stop;
        horizontalSpeed = 0.0f;
        return;
    }

    if (leftKeyDown == true) //Обработка нажатия левой клавиши
    {
        DinosaurDirectionState = EDinosaurDirectionState::Left; //TO DO SetState
        DinosaurMovingState = EDinosaurMovingState::MovingLeft;
        horizontalSpeed = -MaxSpeed_X * CConfig::FSizeScale;
    }

    if (rightKeyDown == true) //Обработка нажатия левой клавиши
    {
        DinosaurDirectionState = EDinosaurDirectionState::Right;
        DinosaurMovingState = EDinosaurMovingState::MovingRight;
        horizontalSpeed = MaxSpeed_X * CConfig::FSizeScale;
    }
}
// -----------------------------------------------------------------------------------

// ------------ Прыжок (начало прыжка, подъём Дино от земли, дальше работает метод MoveHorizontal)  (обрабатывает нажатие пробела)
void CDinosaur::Jump()
{
    if (pos_Y == OnGroundPos_Y)
    {
        pos_Y -= 1.0f;
        verticalSpeed = -MaxSpeed_Y;

        //DinoPos_Y -= 1; //Смещаем дино с земли вверх
        ////DinoStep_Y = -DinoStep_Y; //Меняем знак шага перемещения по вертикали (Y) на отрицательный (для движения вверх)
        //DinoMaxSpeed_Y = -DinoMaxStep_Y; //Задаём начальное смещение при прыжке (отрицательное значение для движения вверх)

        //RedrawDino();
        Beep(300, 50); //TO DO: Перенести обработку звука в отдельный поток, чтобы не вызывало задержку
    }
}
// -----------------------------------------------------------------------------------
