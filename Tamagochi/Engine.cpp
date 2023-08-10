#include "Engine.h"

// ---------------------------- Class Engine -------------------------------------------------------------

// ------------ Конструктор
CEngine::CEngine()
    :GameState(EGameState::FreeMovingLevel)
{
}
// -----------------------------------------------------------------------------------

// ------------ Инициализация начальных данных
void CEngine::InitEngine(HWND hwnd)
{
    CConfig::Hwnd = hwnd;

    Dinosaur.Redraw();

    SetTimer(CConfig::Hwnd, TimerId, 1000/CConfig::FPS, 0);
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка кадра
void CEngine::DrawFrame(HDC hdc, RECT& paintArea)
{
    Cloud.Draw(hdc, paintArea);
    RoadLevel.Draw(hdc, paintArea);
    Dinosaur.Draw(hdc, paintArea);
    Cactus.Draw(hdc, paintArea);
    Bird.Draw(hdc, paintArea);
}
// -----------------------------------------------------------------------------------

// ------------ Обработка клавиш
int CEngine::OnKey(EKeyType keyType, bool keyPressed) //keyPressed == true (нажатие), == false (отжатие)
{
    switch (keyType)
    {
    case EKeyType::LeftKey:
        if (GameState == EGameState::FreeMovingLevel)
        {
            Dinosaur.CheckHorizontalDirection(true, keyPressed);
        }
        break;

    case EKeyType::RightKey:
        if (GameState == EGameState::FreeMovingLevel)
        {
            Dinosaur.CheckHorizontalDirection(false, keyPressed);
        }
        break;

    case EKeyType::DownKey:
        Dinosaur.SetBodyState(EDinosaurBodyState::Crawling);
        break;

    case EKeyType::UpKey:
        Dinosaur.SetBodyState(EDinosaurBodyState::Standing);
        break;

    case EKeyType::SpaceKey:
        if (keyPressed)
            Dinosaur.Jump();
        break;
    }

    return 0;
}
// -----------------------------------------------------------------------------------

// ------------ Метод для обработки действий по таймеру
int CEngine::OnTimer()
{
    ++CConfig::CurrentTimerValue;

    CConfig::MovingLegsSpeed += 0.5f;

    Dinosaur.MoveVertical(Dinosaur.MaxSpeed_Y);

    Dinosaur.MoveHorizontal(Dinosaur.MaxSpeed_Y);

    Bird.Move(Dinosaur.MaxSpeed_Y);

    Bird.Redraw();
    Dinosaur.Redraw();

    return 0;
}
// -----------------------------------------------------------------------------------

