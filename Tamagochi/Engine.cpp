#include "Engine.h"

// ---------------------------- Class Engine -------------------------------------------------------------
CEngine::CEngine()
    :GameState(EGameState::Playing)
{
}

// ------------ Инициализация начальных данных
void CEngine::InitEngine(HWND hwnd)
{
    CConfig::Hwnd = hwnd;

    Dinosaur.Init();

    Cloud.Init();

    Bird.Init();

    Cactus.Init();

    RoadLevel.Init();

    Dinosaur.RedrawDino();

    SetTimer(CConfig::Hwnd, TimerId, 1000/CConfig::FPS, 0);
}


// ------------ Отрисовка кадра
void CEngine::DrawFrame(HDC hdc, RECT& paintArea)
{
    RoadLevel.Draw(hdc, paintArea);
    Cloud.Draw(hdc, paintArea);
    Cactus.Draw(hdc, paintArea);
    Bird.Draw(hdc, paintArea);
    Dinosaur.Draw(hdc, paintArea);
}

// ------------ Обработка клавиш
int CEngine::OnKeyDown(EKeyType keyType)
{
    switch (keyType)
    {
    case EKeyType::LeftKey:
        Dinosaur.DinosaurDirectionState = LeftDirection; //TO DO SetState

        Dinosaur.DinoPos_X -= Dinosaur.DinoStep_X * CConfig::SizeScale;

        if (Dinosaur.DinoPos_X <= leftBorder)
            Dinosaur.DinoPos_X = leftBorder;

        Dinosaur.RedrawDino();
        //Beep(300, 75);
        break;

    case EKeyType::RightKey:
        Dinosaur.DinosaurDirectionState = RightDirection;

        Dinosaur.DinoPos_X += Dinosaur.DinoStep_X * CConfig::SizeScale;

        if (Dinosaur.DinoPos_X >= rightBorder - Dinosaur.DinoWidth * CConfig::SizeScale)
            Dinosaur.DinoPos_X = rightBorder - Dinosaur.DinoWidth * CConfig::SizeScale;

        Dinosaur.RedrawDino();
        //Beep(300, 75);
        break;

    case EKeyType::DownKey:
        Dinosaur.DinosaurBodyState = Crawling;
        Dinosaur.DinoHeight = Dinosaur.crawlingDinoHeight;
        Dinosaur.DinoWidth = Dinosaur.crawlingDinoWidth;

        //Dinosaur.DinoPos_Y += Dinosaur.DinoStep_X * Dinosaur.CConfig::SizeScale;

        //if (Dinosaur.DinoPos_Y >= downBorder - Dinosaur.DinoHeight * Dinosaur.CConfig::SizeScale)
            //Dinosaur.DinoPos_Y = downBorder - Dinosaur.DinoHeight * Dinosaur.CConfig::SizeScale;

        Dinosaur.RedrawDino();
        break;

    case EKeyType::UpKey:
        Dinosaur.DinosaurBodyState = Standing;
        Dinosaur.DinoHeight = Dinosaur.standingDinoHeight;
        Dinosaur.DinoWidth = Dinosaur.standingDinoWidth;

        //Dinosaur.DinoPos_Y -= Dinosaur.DinoStep_X * Dinosaur.CConfig::SizeScale;

        //if (Dinosaur.DinoPos_Y <= topBorder)
            //Dinosaur.DinoPos_Y = topBorder;
        Dinosaur.RedrawDino();
        break;

    case EKeyType::SpaceKey:
        Dinosaur.DinoPos_Y -= Dinosaur.DinoStep_X * CConfig::SizeScale;

        if (Dinosaur.DinoPos_Y <= topBorder)
            Dinosaur.DinoPos_Y = topBorder;

        Dinosaur.RedrawDino();
        //Beep(300, 100);
        break;
    }

    return 0;
}


// ------------ Метод-таймер
int CEngine::OnTimer()
{
    ++CConfig::CurrentTimerValue;

    switch (GameState)
    {
    case Starting:
        break;
    case Playing:
        Dinosaur.RedrawDino();
        //Background.AutoMove(Hwnd);
        break;
    case Pause:
        break;
    case Gameover:
        break;
    case Free:
        break;
    default:
        break;
    }

    //Dinosaur.MoveDino(Hwnd);

    

    return 0;
}

