#include "Engine.h"

// ---------------------------- Class Engine -------------------------------------------------------------

// ------------ Конструктор
CEngine::CEngine()
    :GameState(EGameState::FreeMovingLevel), BackgroundObjects{ 0 }
{
}
// -----------------------------------------------------------------------------------

// ------------ Инициализация начальных данных
void CEngine::InitEngine(HWND hwnd)
{
    CConfig::Hwnd = hwnd;

    SYSTEMTIME systemTime; //струткура для хранения системеного времени
    GetSystemTime(&systemTime); //получаем текущее системное время и сохраняем

    srand(systemTime.wMilliseconds); //устанавливаем случайный рандом в зависимости от текущего значения миллесекунд

    int CloudsCount = CConfig::GetRandom(1, 4);

    for (int i = 0; i < CloudsCount; ++i)
    {
        Clouds[i].visible = true;
        Clouds[i].Init();
    }

    for (int i = 0; i < CloudsCount; ++i)
    {
        Clouds[i].Redraw();
    }

    Dinosaur.Redraw();
    Bird.Redraw();
    RoadLevel.Redraw();
    Cactus.Redraw();

    SetTimer(CConfig::Hwnd, TimerId, 1000 / CConfig::FPS, 0);

    memset(BackgroundObjects, 0, sizeof(BackgroundObjects));

    //BackgroundObjects[0] = &Cloud;
    BackgroundObjects[1] = &Bird;
    BackgroundObjects[2] = &Cactus;
    BackgroundObjects[3] = &RoadLevel;
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка кадра
void CEngine::DrawFrame(HDC hdc, RECT& paintArea)
{
    //Cloud.Draw(hdc, paintArea, 0, 0);

    for (int i = 0; i < 4; ++i)
    {
        if (Clouds[i].visible == true)
        {
            Clouds[i].Draw(hdc, paintArea);
        }
    }

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

    //Передвигаем все объекты заднего плана
    for (int i = 1; i < 4; i++)
    {
        if (BackgroundObjects[i] != 0)
            BackgroundObjects[i]->Move();
    }

    for (int i = 0; i < 4; i++)
    {
        if (Clouds[i].visible == true)
        {
            Clouds[i].Move();
        }
    }

    Bird.Redraw();
    Dinosaur.Redraw();

    //Cloud.Redraw();

    RoadLevel.Redraw();
    Cactus.Redraw();

    //Ускорение объектов заднего плана
    //for (int i = 1; i < 4; i++) //Пропускаем индекс = 0, чтобы не ускорять облака
    //{
    //    if (BackgroundObjects[i] != 0)
    //        BackgroundObjects[i]->speed += CConfig::backgroundAcceleration;
    //}

    return 0;
}
// -----------------------------------------------------------------------------------

