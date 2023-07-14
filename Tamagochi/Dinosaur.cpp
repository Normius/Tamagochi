#include "Dinosaur.h"

// ---------------------------- Класс персонажа Dino -------------------------------------------------------------
CDinosaur::CDinosaur()
    : DinosaurBodyState(Standing), DinosaurDirectionState(RightDirection), DinoHeight(standingDinoHeight), DinoWidth(standingDinoWidth), 
      DinoPos_X(0), DinoPos_Y(50 * CConfig::SizeScale), DinoStep_X(3), DinoSpeed(1), characterPen(0), characterBrush(0)
{
}

// ------------ Инициализация начальных данных
void CDinosaur::Init()
{
    characterPen = CreatePen(PS_SOLID, 0, RGB(19, 30, 24));

    characterBrush = CreateSolidBrush(RGB(19, 30, 24));
}

void CDinosaur::Draw(HDC hdc, RECT& paintArea)
{
    RECT intersectionRect; //Нужен для ф-ции проверки пересечения прямоугольников, в него сохраняется область пересечения или 0

    if (!IntersectRect(&intersectionRect, &paintArea, &dinoRect))
    {
        return;
    }

    switch (DinosaurBodyState)
    {
    case Standing:
    {
        if (DinosaurDirectionState == RightDirection)
        {
            //Драко стоит (вправо)
            DrawRightStandingDino(hdc);
            DrawRightHead(hdc, DinoPos_X, DinoPos_Y);
            DrawRightStandingLegs(hdc);

            //MoveLegsRight(hdc);

            //DrawRightFirstStep(hdc, DinoPos_X, DinoPos_Y);
            //DrawRightSecondStep(hdc, DinoPos_X, DinoPos_Y);
        }
        else
        {
            //Драко стоит (влево)
            DrawLeftStandingDino(hdc);
            DrawLeftHead(hdc, DinoPos_X, DinoPos_Y, standingDinoWidth);
            DrawLeftStandingLegs(hdc);

            //MoveLegsLeft(hdc);
            
            //DrawLeftFirstStep(hdc, DinoPos_X, DinoPos_Y, standingDinoWidth);
            //DrawLeftSecondStep(hdc, DinoPos_X, DinoPos_Y, standingDinoWidth);
        }
     
    }
        break;
    case Crawling:
    {
        if (DinosaurDirectionState == RightDirection)
        {
            //Драко в присяде (вправо)
            DrawRightCrawlingDino(hdc, DinoPos_X, DinoPos_Y);
            DrawRightHead(hdc, DinoPos_X + 16 * CConfig::SizeScale, DinoPos_Y + 18 * CConfig::SizeScale);     //Смещаем отрисовку головы для приседа
            DrawRightStandingLegs(hdc);  //Смещаем отрисовку ног для приседа

            //MoveLegsRight(hdc);
            
            //DrawRightFirstStep(hdc, DinoPos_X, DinoPos_Y);
            //DrawRightSecondStep(hdc, DinoPos_X, DinoPos_Y);
        }
        else
        {
            //Драко в присяде (влево)
            DrawLeftCrawlingDino(hdc, DinoPos_X, DinoPos_Y, crawlingDinoWidth);
            DrawLeftHead(hdc, DinoPos_X - 16 * CConfig::SizeScale, DinoPos_Y + 18 * CConfig::SizeScale, crawlingDinoWidth);
            DrawLeftStandingLegs(hdc);

            //MoveLegsLeft(hdc);
            
            //DrawLeftFirstStep(hdc, DinoPos_X, DinoPos_Y, crawlingDinoWidth);
            //DrawLeftSecondStep(hdc, DinoPos_X, DinoPos_Y, crawlingDinoWidth);
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

// ------------ Перерисовка персонажа в новых координатах
void CDinosaur::RedrawDino()
{
    prevDinoRect = dinoRect;

    dinoRect.left = DinoPos_X;
    dinoRect.top = DinoPos_Y;
    dinoRect.right = dinoRect.left + DinoWidth * CConfig::SizeScale;
    dinoRect.bottom = dinoRect.top + DinoHeight * CConfig::SizeScale;

    InvalidateRect(CConfig::Hwnd, &prevDinoRect, TRUE);
    InvalidateRect(CConfig::Hwnd, &dinoRect, TRUE);
}


// ------------ Очистка фона для перерисовки
void CDinosaur::ClearRightLegsBackground(HDC hdc)
{
    //Очищаем фон ног
    SelectObject(hdc, CConfig::backgroundPen);
    SelectObject(hdc, CConfig::backgroundBrush);
    //Левая нога
    Rectangle(hdc, DinoPos_X + 12 * CConfig::SizeScale, DinoPos_Y + 36 * CConfig::SizeScale, DinoPos_X + 18 * CConfig::SizeScale, DinoPos_Y + 44 * CConfig::SizeScale);
    
    //Правая нога
    Rectangle(hdc, DinoPos_X + 22 * CConfig::SizeScale, DinoPos_Y + 36 * CConfig::SizeScale, DinoPos_X + 28 * CConfig::SizeScale, DinoPos_Y + 44 * CConfig::SizeScale);
}

// ------------ Очистка фона для перерисовки влево
void CDinosaur::ClearLeftLegsBackground(HDC hdc)
{
    //Очищаем фон ног
    SelectObject(hdc, CConfig::backgroundPen);
    SelectObject(hdc, CConfig::backgroundBrush);
    //Левая нога
    Rectangle(hdc, DinoPos_X + (DinoWidth - 12) * CConfig::SizeScale, DinoPos_Y + (36 * CConfig::SizeScale), DinoPos_X + (DinoWidth - 18) * CConfig::SizeScale, DinoPos_Y + (44 * CConfig::SizeScale));
    
    //Правая нога
    Rectangle(hdc, DinoPos_X + (DinoWidth - 22) * CConfig::SizeScale, DinoPos_Y + (36 * CConfig::SizeScale), DinoPos_X + (DinoWidth - 28) * CConfig::SizeScale, DinoPos_Y + (44 * CConfig::SizeScale));
}


// ------------ Отрисовка ног стоя
void CDinosaur::DrawRightStandingLegs(HDC hdc)
{
    ClearRightLegsBackground(hdc);

    //Рисуем ноги
    SelectObject(hdc, characterPen);
    SelectObject(hdc, characterBrush);

    //Левая нога
    Rectangle(hdc, DinoPos_X + 12 * CConfig::SizeScale, DinoPos_Y + 36 * CConfig::SizeScale, DinoPos_X + 15 * CConfig::SizeScale, DinoPos_Y + 44 * CConfig::SizeScale);
    Rectangle(hdc, DinoPos_X + 15 * CConfig::SizeScale, DinoPos_Y + 42 * CConfig::SizeScale, DinoPos_X + 18 * CConfig::SizeScale, DinoPos_Y + 44 * CConfig::SizeScale);

    //Правая нога
    Rectangle(hdc, DinoPos_X + 22 * CConfig::SizeScale, DinoPos_Y + 36 * CConfig::SizeScale, DinoPos_X + 25 * CConfig::SizeScale, DinoPos_Y + 44 * CConfig::SizeScale);
    Rectangle(hdc, DinoPos_X + 25 * CConfig::SizeScale, DinoPos_Y + 42 * CConfig::SizeScale, DinoPos_X + 28 * CConfig::SizeScale, DinoPos_Y + 44 * CConfig::SizeScale);
}

// ------------ Отрисовка ног стоя влево 
void CDinosaur::DrawLeftStandingLegs(HDC hdc)
{
    ClearLeftLegsBackground(hdc);

    //Рисуем ноги
    SelectObject(hdc, characterPen);
    SelectObject(hdc, characterBrush);

    //Левая нога
    Rectangle(hdc, DinoPos_X + (DinoWidth - 12) * CConfig::SizeScale, DinoPos_Y + (36 * CConfig::SizeScale), DinoPos_X + (DinoWidth - 15) * CConfig::SizeScale, DinoPos_Y + (44 * CConfig::SizeScale));
    Rectangle(hdc, DinoPos_X + (DinoWidth - 15) * CConfig::SizeScale, DinoPos_Y + (42 * CConfig::SizeScale), DinoPos_X + (DinoWidth - 18) * CConfig::SizeScale, DinoPos_Y + (44 * CConfig::SizeScale));

    //Правая нога
    Rectangle(hdc, DinoPos_X + (DinoWidth - 22) * CConfig::SizeScale, DinoPos_Y + (36 * CConfig::SizeScale), DinoPos_X + (DinoWidth - 25) * CConfig::SizeScale, DinoPos_Y + (44 * CConfig::SizeScale));
    Rectangle(hdc, DinoPos_X + (DinoWidth - 25) * CConfig::SizeScale, DinoPos_Y + (42 * CConfig::SizeScale), DinoPos_X + (DinoWidth - 28) * CConfig::SizeScale, DinoPos_Y + (44 * CConfig::SizeScale));
}


// ------------ Отрисовка ног при первом шаге
void CDinosaur::DrawRightFirstStep(HDC hdc)
{
    ClearRightLegsBackground(hdc);

    //Рисуем ноги
    SelectObject(hdc, characterPen);
    SelectObject(hdc, characterBrush);

    //Левая нога обычно
    Rectangle(hdc, DinoPos_X + 12 * CConfig::SizeScale, DinoPos_Y + 36 * CConfig::SizeScale, DinoPos_X + 15 * CConfig::SizeScale, DinoPos_Y + 44 * CConfig::SizeScale);
    Rectangle(hdc, DinoPos_X + 15 * CConfig::SizeScale, DinoPos_Y + 42 * CConfig::SizeScale, DinoPos_X + 18 * CConfig::SizeScale, DinoPos_Y + 44 * CConfig::SizeScale);

    //Правая нога поднятая
    Rectangle(hdc, DinoPos_X + 22 * CConfig::SizeScale, DinoPos_Y + (36 - 4) * CConfig::SizeScale, DinoPos_X + 25 * CConfig::SizeScale, DinoPos_Y + (44 - 4) * CConfig::SizeScale);
    Rectangle(hdc, DinoPos_X + 25 * CConfig::SizeScale, DinoPos_Y + (42 - 4) * CConfig::SizeScale, DinoPos_X + 28 * CConfig::SizeScale, DinoPos_Y + (44 - 4) * CConfig::SizeScale);
}

// ------------ Отрисовка ног при первом шаге влево
void CDinosaur::DrawLeftFirstStep(HDC hdc)
{
    ClearLeftLegsBackground(hdc);

    //Рисуем ноги
    SelectObject(hdc, characterPen);
    SelectObject(hdc, characterBrush);

    //Левая нога обычно
    Rectangle(hdc, DinoPos_X + (DinoWidth - 12) * CConfig::SizeScale, DinoPos_Y + (36 * CConfig::SizeScale), DinoPos_X + (DinoWidth - 15) * CConfig::SizeScale, DinoPos_Y + (44 * CConfig::SizeScale));
    Rectangle(hdc, DinoPos_X + (DinoWidth - 15) * CConfig::SizeScale, DinoPos_Y + (42 * CConfig::SizeScale), DinoPos_X + (DinoWidth - 18) * CConfig::SizeScale, DinoPos_Y + (44 * CConfig::SizeScale));

    //Правая нога поднятая
    Rectangle(hdc, DinoPos_X + (DinoWidth - 22) * CConfig::SizeScale, DinoPos_Y + (36 - 4) * CConfig::SizeScale, DinoPos_X + (DinoWidth - 25) * CConfig::SizeScale, DinoPos_Y + (44 - 4) * CConfig::SizeScale);
    Rectangle(hdc, DinoPos_X + (DinoWidth - 25) * CConfig::SizeScale, DinoPos_Y + (42 - 4) * CConfig::SizeScale, DinoPos_X + (DinoWidth - 28) * CConfig::SizeScale, DinoPos_Y + (44 - 4) * CConfig::SizeScale);
}


// ------------ Отрисовка ног при втором шаге
void CDinosaur::DrawRightSecondStep(HDC hdc)
{
    ClearRightLegsBackground(hdc);

    //Рисуем ноги
    SelectObject(hdc, characterPen);
    SelectObject(hdc, characterBrush);

    //Левая нога поднятая
    Rectangle(hdc, DinoPos_X + 12 * CConfig::SizeScale, DinoPos_Y + (36 - 4) * CConfig::SizeScale, DinoPos_X + 15 * CConfig::SizeScale, DinoPos_Y + (44 - 4) * CConfig::SizeScale);
    Rectangle(hdc, DinoPos_X + 15 * CConfig::SizeScale, DinoPos_Y + (42 - 4) * CConfig::SizeScale, DinoPos_X + 18 * CConfig::SizeScale, DinoPos_Y + (44 - 4) * CConfig::SizeScale);

    //Правая нога обычно
    Rectangle(hdc, DinoPos_X + 22 * CConfig::SizeScale, DinoPos_Y + 36 * CConfig::SizeScale, DinoPos_X + 25 * CConfig::SizeScale, DinoPos_Y + 44 * CConfig::SizeScale);
    Rectangle(hdc, DinoPos_X + 25 * CConfig::SizeScale, DinoPos_Y + 42 * CConfig::SizeScale, DinoPos_X + 28 * CConfig::SizeScale, DinoPos_Y + 44 * CConfig::SizeScale);
}

// ------------ Отрисовка ног при втором шаге влево
void CDinosaur::DrawLeftSecondStep(HDC hdc)
{
    ClearLeftLegsBackground(hdc);

    //Рисуем ноги
    SelectObject(hdc, characterPen);
    SelectObject(hdc, characterBrush);

    //Левая нога поднятая
    Rectangle(hdc, DinoPos_X + (DinoWidth - 12) * CConfig::SizeScale, DinoPos_Y + (36 - 4) * CConfig::SizeScale, DinoPos_X + (DinoWidth - 15) * CConfig::SizeScale, DinoPos_Y + (44 - 4) * CConfig::SizeScale);
    Rectangle(hdc, DinoPos_X + (DinoWidth - 15) * CConfig::SizeScale, DinoPos_Y + (42 - 4) * CConfig::SizeScale, DinoPos_X + (DinoWidth - 18) * CConfig::SizeScale, DinoPos_Y + (44 - 4) * CConfig::SizeScale);

    //Правая нога обычно
    Rectangle(hdc, DinoPos_X + (DinoWidth - 22) * CConfig::SizeScale, DinoPos_Y + (36 * CConfig::SizeScale), DinoPos_X + (DinoWidth - 25) * CConfig::SizeScale, DinoPos_Y + (44 * CConfig::SizeScale));
    Rectangle(hdc, DinoPos_X + (DinoWidth - 25) * CConfig::SizeScale, DinoPos_Y + (42 * CConfig::SizeScale), DinoPos_X + (DinoWidth - 28) * CConfig::SizeScale, DinoPos_Y + (44 * CConfig::SizeScale));
}


// ------------ Отрисовка зрачка при стоклновении
void CDinosaur::DrawRightEye(HDC hdc)
{
    SelectObject(hdc, characterPen);
    SelectObject(hdc, characterBrush);

    //Зрачок при столкновении
    Rectangle(hdc, DinoPos_X + 28 * CConfig::SizeScale, DinoPos_Y + 2 * CConfig::SizeScale, DinoPos_X + 29 * CConfig::SizeScale, DinoPos_Y + 5 * CConfig::SizeScale);
}

// ------------ Отрисовка зрачка при стоклновении влево
void CDinosaur::DrawLeftEye(HDC hdc)
{
    SelectObject(hdc, characterPen);
    SelectObject(hdc, characterBrush);

    //Зрачок при столкновении
    Rectangle(hdc, DinoPos_X + (DinoWidth - 28) * CConfig::SizeScale, DinoPos_Y + 2 * CConfig::SizeScale, DinoPos_X + (DinoWidth - 29) * CConfig::SizeScale, DinoPos_Y + 5 * CConfig::SizeScale);
}


// ------------ Отрисовка тела в обычном состоянии
void CDinosaur::DrawRightStandingDino(HDC hdc)
{
    //DinoHeight = standingDinoHeight;
    //DinoWidth = standingDinoWidth;

    SelectObject(hdc, characterPen);
    SelectObject(hdc, characterBrush);

    //Тело
    Rectangle(hdc, DinoPos_X + 11 * CConfig::SizeScale, DinoPos_Y + 36 * CConfig::SizeScale, DinoPos_X + 31 * CConfig::SizeScale, DinoPos_Y + 15 * CConfig::SizeScale);

    //Лапки
    Rectangle(hdc, DinoPos_X + 31 * CConfig::SizeScale, DinoPos_Y + 20 * CConfig::SizeScale, DinoPos_X + 36 * CConfig::SizeScale, DinoPos_Y + 24 * CConfig::SizeScale);

    //Хвост
    Rectangle(hdc, DinoPos_X, DinoPos_Y + 13 * CConfig::SizeScale, DinoPos_X + 11 * CConfig::SizeScale, DinoPos_Y + 36 * CConfig::SizeScale);

    //Фоновые пропуски
    SelectObject(hdc, CConfig::backgroundPen);
    SelectObject(hdc, CConfig::backgroundBrush);

    //Лапки
    Rectangle(hdc, DinoPos_X + 31 * CConfig::SizeScale, DinoPos_Y + 22 * CConfig::SizeScale, DinoPos_X + 34 * CConfig::SizeScale, DinoPos_Y + 24 * CConfig::SizeScale);

    //Хвост
    Rectangle(hdc, DinoPos_X + 4 * CConfig::SizeScale, DinoPos_Y + 12 * CConfig::SizeScale, DinoPos_X + 6 * CConfig::SizeScale, DinoPos_Y + 16 * CConfig::SizeScale);
    Rectangle(hdc, DinoPos_X, DinoPos_Y + 12 * CConfig::SizeScale, DinoPos_X + 1 * CConfig::SizeScale, DinoPos_Y + 16 * CConfig::SizeScale);

    //Тело спереди
    Rectangle(hdc, DinoPos_X + 30 * CConfig::SizeScale, DinoPos_Y + 31 * CConfig::SizeScale, DinoPos_X + 33 * CConfig::SizeScale, DinoPos_Y + 34 * CConfig::SizeScale);
    Rectangle(hdc, DinoPos_X + 28 * CConfig::SizeScale, DinoPos_Y + 33 * CConfig::SizeScale, DinoPos_X + 33 * CConfig::SizeScale, DinoPos_Y + 36 * CConfig::SizeScale);
    Rectangle(hdc, DinoPos_X + 26 * CConfig::SizeScale, DinoPos_Y + 35 * CConfig::SizeScale, DinoPos_X + 33 * CConfig::SizeScale, DinoPos_Y + 39 * CConfig::SizeScale);

    //Тело сзади
    Rectangle(hdc, DinoPos_X, DinoPos_Y + 30 * CConfig::SizeScale, DinoPos_X + 4 * CConfig::SizeScale, DinoPos_Y + 32 * CConfig::SizeScale);
    Rectangle(hdc, DinoPos_X, DinoPos_Y + 32 * CConfig::SizeScale, DinoPos_X + 6 * CConfig::SizeScale, DinoPos_Y + 34 * CConfig::SizeScale);
    Rectangle(hdc, DinoPos_X, DinoPos_Y + 28 * CConfig::SizeScale, DinoPos_X + 2 * CConfig::SizeScale, DinoPos_Y + 30 * CConfig::SizeScale);
    Rectangle(hdc, DinoPos_X, DinoPos_Y + 34 * CConfig::SizeScale, DinoPos_X + 9 * CConfig::SizeScale, DinoPos_Y + 36 * CConfig::SizeScale);


    //На спине
    Rectangle(hdc, DinoPos_X + 6 * CConfig::SizeScale, DinoPos_Y + 13 * CConfig::SizeScale, DinoPos_X + 18 * CConfig::SizeScale, DinoPos_Y + 17 * CConfig::SizeScale);
    Rectangle(hdc, DinoPos_X + 6 * CConfig::SizeScale, DinoPos_Y + 17 * CConfig::SizeScale, DinoPos_X + 16 * CConfig::SizeScale, DinoPos_Y + 19 * CConfig::SizeScale);
    Rectangle(hdc, DinoPos_X + 6 * CConfig::SizeScale, DinoPos_Y + 19 * CConfig::SizeScale, DinoPos_X + 14 * CConfig::SizeScale, DinoPos_Y + 21 * CConfig::SizeScale);
    Rectangle(hdc, DinoPos_X + 7 * CConfig::SizeScale, DinoPos_Y + 21 * CConfig::SizeScale, DinoPos_X + 12 * CConfig::SizeScale, DinoPos_Y + 23 * CConfig::SizeScale);
}

// ------------ Отрисовка тела в обычном состоянии влево
void CDinosaur::DrawLeftStandingDino(HDC hdc)
{
    //DinoHeight = standingDinoHeight;
    //DinoWidth = standingDinoWidth;

    SelectObject(hdc, characterPen);
    SelectObject(hdc, characterBrush);

    //Тело
    Rectangle(hdc, DinoPos_X + (DinoWidth - 11) * CConfig::SizeScale, DinoPos_Y + (36 * CConfig::SizeScale), DinoPos_X + (DinoWidth - 31) * CConfig::SizeScale, DinoPos_Y + (15 * CConfig::SizeScale));

    //Лапки
    Rectangle(hdc, DinoPos_X + (DinoWidth - 31) * CConfig::SizeScale, DinoPos_Y + (20 * CConfig::SizeScale), DinoPos_X + (DinoWidth - 36) * CConfig::SizeScale, DinoPos_Y + (24 * CConfig::SizeScale));

    //Хвост
    Rectangle(hdc, DinoPos_X + (DinoWidth * CConfig::SizeScale), DinoPos_Y + (13 * CConfig::SizeScale), DinoPos_X + (DinoWidth - 11) * CConfig::SizeScale, DinoPos_Y + (36 * CConfig::SizeScale));

    //Фоновые пропуски (контур динозавра)
    SelectObject(hdc, CConfig::backgroundPen);
    SelectObject(hdc, CConfig::backgroundBrush);

    //Лапки
    Rectangle(hdc, DinoPos_X + (DinoWidth - 31) * CConfig::SizeScale, DinoPos_Y + (22 * CConfig::SizeScale), DinoPos_X + (DinoWidth - 34) * CConfig::SizeScale, DinoPos_Y + (24 * CConfig::SizeScale));

    //Хвост
    Rectangle(hdc, DinoPos_X + (DinoWidth - 4) * CConfig::SizeScale, DinoPos_Y + (12 * CConfig::SizeScale), DinoPos_X + (DinoWidth - 6) * CConfig::SizeScale, DinoPos_Y + (16 * CConfig::SizeScale));
    Rectangle(hdc, DinoPos_X + (DinoWidth * CConfig::SizeScale), DinoPos_Y + (12 * CConfig::SizeScale), DinoPos_X + (DinoWidth - 1) * CConfig::SizeScale, DinoPos_Y + (16 * CConfig::SizeScale));

    //Тело спереди
    Rectangle(hdc, DinoPos_X + (DinoWidth - 30) * CConfig::SizeScale, DinoPos_Y + (31 * CConfig::SizeScale), DinoPos_X + (DinoWidth - 33) * CConfig::SizeScale, DinoPos_Y + (34 * CConfig::SizeScale));
    Rectangle(hdc, DinoPos_X + (DinoWidth - 28) * CConfig::SizeScale, DinoPos_Y + (33 * CConfig::SizeScale), DinoPos_X + (DinoWidth - 33) * CConfig::SizeScale, DinoPos_Y + (36 * CConfig::SizeScale));
    Rectangle(hdc, DinoPos_X + (DinoWidth - 26) * CConfig::SizeScale, DinoPos_Y + (35 * CConfig::SizeScale), DinoPos_X + (DinoWidth - 33) * CConfig::SizeScale, DinoPos_Y + (39 * CConfig::SizeScale));

    //Тело сзади
    Rectangle(hdc, DinoPos_X + (DinoWidth * CConfig::SizeScale), DinoPos_Y + (30 * CConfig::SizeScale), DinoPos_X + (DinoWidth - 4) * CConfig::SizeScale, DinoPos_Y + (32 * CConfig::SizeScale));
    Rectangle(hdc, DinoPos_X + (DinoWidth * CConfig::SizeScale), DinoPos_Y + (32 * CConfig::SizeScale), DinoPos_X + (DinoWidth - 6) * CConfig::SizeScale, DinoPos_Y + (34 * CConfig::SizeScale));
    Rectangle(hdc, DinoPos_X + (DinoWidth * CConfig::SizeScale), DinoPos_Y + (28 * CConfig::SizeScale), DinoPos_X + (DinoWidth - 2) * CConfig::SizeScale, DinoPos_Y + (30 * CConfig::SizeScale));
    Rectangle(hdc, DinoPos_X + (DinoWidth * CConfig::SizeScale), DinoPos_Y + (34 * CConfig::SizeScale), DinoPos_X + (DinoWidth - 9) * CConfig::SizeScale, DinoPos_Y + (36 * CConfig::SizeScale));

    //На спине
    Rectangle(hdc, DinoPos_X + (DinoWidth - 6) * CConfig::SizeScale, DinoPos_Y + (13 * CConfig::SizeScale), DinoPos_X + (DinoWidth - 18) * CConfig::SizeScale, DinoPos_Y + (17 * CConfig::SizeScale));
    Rectangle(hdc, DinoPos_X + (DinoWidth - 6) * CConfig::SizeScale, DinoPos_Y + (17 * CConfig::SizeScale), DinoPos_X + (DinoWidth - 16) * CConfig::SizeScale, DinoPos_Y + (19 * CConfig::SizeScale));
    Rectangle(hdc, DinoPos_X + (DinoWidth - 6) * CConfig::SizeScale, DinoPos_Y + (19 * CConfig::SizeScale), DinoPos_X + (DinoWidth - 14) * CConfig::SizeScale, DinoPos_Y + (21 * CConfig::SizeScale));
    Rectangle(hdc, DinoPos_X + (DinoWidth - 7) * CConfig::SizeScale, DinoPos_Y + (21 * CConfig::SizeScale), DinoPos_X + (DinoWidth - 12) * CConfig::SizeScale, DinoPos_Y + (23 * CConfig::SizeScale));
}


// ------------ Отрисовка головы влево
void CDinosaur::DrawRightHead(HDC hdc, int pos_x, int pos_y)
{
    SelectObject(hdc, characterPen);
    SelectObject(hdc, characterBrush);

    //Голова
    Rectangle(hdc, pos_x + 23 * CConfig::SizeScale, pos_y, pos_x + 44 * CConfig::SizeScale, pos_y + 15 * CConfig::SizeScale);

    SelectObject(hdc, CConfig::backgroundPen);
    SelectObject(hdc, CConfig::backgroundBrush);

    //Голова
    Rectangle(hdc, pos_x + 34 * CConfig::SizeScale, pos_y + 10 * CConfig::SizeScale, pos_x + 44 * CConfig::SizeScale, pos_y + 12 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 41 * CConfig::SizeScale, pos_y + 12 * CConfig::SizeScale, pos_x + 44 * CConfig::SizeScale, pos_y + 15 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 23 * CConfig::SizeScale, pos_y, pos_x + 25 * CConfig::SizeScale, pos_y + 1 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 42 * CConfig::SizeScale, pos_y, pos_x + 44 * CConfig::SizeScale, pos_y + 1 * CConfig::SizeScale);

    //Глаз
    Rectangle(hdc, pos_x + 27 * CConfig::SizeScale, pos_y + 2 * CConfig::SizeScale, pos_x + 30 * CConfig::SizeScale, pos_y + 5 * CConfig::SizeScale);
}

// ------------ Отрисовка головы
void CDinosaur::DrawLeftHead(HDC hdc, int pos_x, int pos_y, int reverseOffset)
{
    SelectObject(hdc, characterPen);
    SelectObject(hdc, characterBrush);

    //Голова
    Rectangle(hdc, pos_x + (reverseOffset - 23) * CConfig::SizeScale, pos_y, pos_x + (reverseOffset - 44) * CConfig::SizeScale, pos_y + 15 * CConfig::SizeScale);

    SelectObject(hdc, CConfig::backgroundPen);
    SelectObject(hdc, CConfig::backgroundBrush);

    //Голова
    Rectangle(hdc, pos_x + (reverseOffset - 34) * CConfig::SizeScale, pos_y + 10 * CConfig::SizeScale, pos_x + (reverseOffset - 44) * CConfig::SizeScale, pos_y + 12 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (reverseOffset - 41) * CConfig::SizeScale, pos_y + 12 * CConfig::SizeScale, pos_x + (reverseOffset - 44) * CConfig::SizeScale, pos_y + 15 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (reverseOffset - 23) * CConfig::SizeScale, pos_y, pos_x + (reverseOffset - 25) * CConfig::SizeScale, pos_y + 1 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (reverseOffset - 42) * CConfig::SizeScale, pos_y, pos_x + (reverseOffset - 44) * CConfig::SizeScale, pos_y + 1 * CConfig::SizeScale);

    //Глаз
    Rectangle(hdc, pos_x + (reverseOffset - 27) * CConfig::SizeScale, pos_y + (2 * CConfig::SizeScale), pos_x + (reverseOffset - 30) * CConfig::SizeScale, pos_y + (5 * CConfig::SizeScale));
}


// ----------- Отрисовка тела в присяде
void CDinosaur::DrawRightCrawlingDino(HDC hdc, int pos_x, int pos_y)
{
    //DinoHeight = crawlingDinoHeight;
    //DinoWidth = crawlingDinoWidth;

    SelectObject(hdc, characterPen);
    SelectObject(hdc, characterBrush);

    //Тело
    Rectangle(hdc, pos_x, pos_y + 18 * CConfig::SizeScale, pos_x + 39 * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale);

    //Лапы
    Rectangle(hdc, pos_x + 32 * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale, pos_x + 34 * CConfig::SizeScale, pos_y + 40 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 33 * CConfig::SizeScale, pos_y + 38 * CConfig::SizeScale, pos_x + 36 * CConfig::SizeScale, pos_y + 40 * CConfig::SizeScale);

    //Рисуем пропуски фоновые(контур динозавра)
    SelectObject(hdc, CConfig::backgroundPen);
    SelectObject(hdc, CConfig::backgroundBrush);

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

// ----------- Отрисовка тела в присяде влево -------------------------------------------------
void CDinosaur::DrawLeftCrawlingDino(HDC hdc, int pos_x, int pos_y, int reverseOffset)
{
    //DinoHeight = crawlingDinoHeight;
    //DinoWidth = crawlingDinoWidth;

    SelectObject(hdc, characterPen);
    SelectObject(hdc, characterBrush);

    //Тело
    Rectangle(hdc, pos_x + (reverseOffset * CConfig::SizeScale), pos_y + 18 * CConfig::SizeScale, pos_x + (reverseOffset - 39) * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale);

    //Лапы
    Rectangle(hdc, pos_x + (reverseOffset - 32) * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale, pos_x + (reverseOffset - 34) * CConfig::SizeScale, pos_y + 40 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (reverseOffset - 33) * CConfig::SizeScale, pos_y + 38 * CConfig::SizeScale, pos_x + (reverseOffset - 36) * CConfig::SizeScale, pos_y + 40 * CConfig::SizeScale);

    //Рисуем пропуски фоновые
    SelectObject(hdc, CConfig::backgroundPen);
    SelectObject(hdc, CConfig::backgroundBrush);

    //Тело спереди
    Rectangle(hdc, pos_x + (reverseOffset - 36) * CConfig::SizeScale, pos_y + 32 * CConfig::SizeScale, pos_x + (reverseOffset - 39) * CConfig::SizeScale, pos_y + 34 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (reverseOffset - 34) * CConfig::SizeScale, pos_y + 34 * CConfig::SizeScale, pos_x + (reverseOffset - 39) * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale);

    //Тело сзади
    Rectangle(hdc, pos_x + (reverseOffset * CConfig::SizeScale), pos_y + 24 * CConfig::SizeScale, pos_x + (reverseOffset - 1) * CConfig::SizeScale, pos_y + 26 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (reverseOffset * CConfig::SizeScale), pos_y + 26 * CConfig::SizeScale, pos_x + (reverseOffset - 2) * CConfig::SizeScale, pos_y + 28 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (reverseOffset * CConfig::SizeScale), pos_y + 28 * CConfig::SizeScale, pos_x + (reverseOffset - 4) * CConfig::SizeScale, pos_y + 30 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (reverseOffset * CConfig::SizeScale), pos_y + 30 * CConfig::SizeScale, pos_x + (reverseOffset - 6) * CConfig::SizeScale, pos_y + 32 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (reverseOffset * CConfig::SizeScale), pos_y + 32 * CConfig::SizeScale, pos_x + (reverseOffset - 8) * CConfig::SizeScale, pos_y + 34 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (reverseOffset * CConfig::SizeScale), pos_y + 34 * CConfig::SizeScale, pos_x + (reverseOffset - 10) * CConfig::SizeScale, pos_y + 36 * CConfig::SizeScale);

    //На спине
    Rectangle(hdc, pos_x + (reverseOffset - 2) * CConfig::SizeScale, pos_y + 18 * CConfig::SizeScale, pos_x + (reverseOffset - 39) * CConfig::SizeScale, pos_y + 19 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (reverseOffset - 3) * CConfig::SizeScale, pos_y + 18 * CConfig::SizeScale, pos_x + (reverseOffset - 16) * CConfig::SizeScale, pos_y + 20 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (reverseOffset - 5) * CConfig::SizeScale, pos_y + 20 * CConfig::SizeScale, pos_x + (reverseOffset - 14) * CConfig::SizeScale, pos_y + 21 * CConfig::SizeScale);

    Rectangle(hdc, pos_x + (reverseOffset - 34) * CConfig::SizeScale, pos_y + 18 * CConfig::SizeScale, pos_x + (reverseOffset - 39) * CConfig::SizeScale, pos_y + 20 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (reverseOffset - 36) * CConfig::SizeScale, pos_y + 20 * CConfig::SizeScale, pos_x + (reverseOffset - 39) * CConfig::SizeScale, pos_y + 21 * CConfig::SizeScale);
}


// ------------ Анимация ног при движении вправо
void CDinosaur::MoveLegsRight(HDC hdc)
{
    if (CConfig::CurrentTimerValue % 2 == 0)
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
    if (CConfig::CurrentTimerValue % 2 == 0)
    {
        DrawLeftFirstStep(hdc);

    }
    else
    {
        DrawLeftSecondStep(hdc);
    }
}
// -----------------------------------------------------------------------------------