#include "Engine.h"

// ---------------------------- Class Engine -------------------------------------------------------------

// ------------ Конструктор
CEngine::CEngine()
    :GameState(EGameState::FreeMovingLevel), BackgroundObjects{ 0 }, lastCloudTimerDisappear(0), newCloudTimerDelay(0)
{
}
// -----------------------------------------------------------------------------------

// ------------ Инициализация начальных данных
void CEngine::InitEngine(HWND hwnd)
{
    CConfig::Hwnd = hwnd;

    SYSTEMTIME systemTime; //Струткура для хранения системеного времени
    GetSystemTime(&systemTime); //Получаем текущее системное время и сохраняем

    srand(systemTime.wMilliseconds); //Устанавливаем случайный рандом в зависимости от текущего значения миллесекунд

    int startCloudsCount = CConfig::GetRandom(1, 4); //Задаём стартовое количество облаков

    //Отрисовываем стартовые облака
    for (int i = 0; i < startCloudsCount; ++i)
    {
        int x = CConfig::GetRandom(100, 700);
        int y = CConfig::GetRandom(20, 120);

        Clouds[i].Init(x, y);
    }

    for (int i = 0; i < startCloudsCount; ++i)
    {
        if (Clouds[i].visible == true)
            Clouds[i].Redraw();
    }

    Dinosaur.Redraw();
    Bird.Redraw();
    RoadLevel.Redraw();
    Cactus.Redraw();

    SetTimer(CConfig::Hwnd, TimerId, 1000 / CConfig::FPS, 0);

    memset(BackgroundObjects, 0, sizeof(BackgroundObjects)); //Обнуляем указатели в массиве

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
            Clouds[i].Draw(hdc, paintArea);
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
    ++CConfig::currentTimerValue; //значение

    CConfig::slowCurrentTimerValue += 0.5f;

    Dinosaur.MoveVertical(Dinosaur.MaxSpeed_Y);

    Dinosaur.MoveHorizontal(Dinosaur.MaxSpeed_Y);

    //Передвигаем все объекты заднего плана
    for (int i = 1; i < 4; i++)
    {
        if (BackgroundObjects[i] != 0)
            BackgroundObjects[i]->Move();
    }

    //TO DO: !!!Логика для облака, возможно создать метод и перенести в класс облака и вызывать здесь в цикле этот метод

    newCloudTimerDelay = CConfig::FPS/2 * CConfig::GetRandom(1, 8); //Случайное время до появления нового облака
    //Отрисовываем новые облака
    if (lastCloudTimerDisappear + newCloudTimerDelay <= CConfig::currentTimerValue) //Отрисовываем новое облако только через некоторую временную паузу
    {
        lastCloudTimerDisappear = CConfig::currentTimerValue + newCloudTimerDelay; //Обновляем время последнего исчезновения облака

        for (int i = 0; i < CConfig::MaxClouds; ++i) //Перебираем все облака, находим ушедшее за экран и отрисовываем его
        {
            if (Clouds[i].visible == false)
            {
                int y = CConfig::GetRandom(40, 130);
                Clouds[i].Init(CConfig::rightBorder, y);
                break;
            }
        }
    }

    //Передвигаем облака
    for (int i = 0; i < CConfig::MaxClouds; i++)
    {
        if (Clouds[i].visible == true)
            Clouds[i].Move();
    }

    Bird.Redraw();
    Dinosaur.Redraw();

    RoadLevel.Redraw();
    Cactus.Redraw();

    //Ускорение объектов заднего плана
    for (int i = 1; i < 4; i++) //Пропускаем индекс = 0, чтобы не ускорять облака
    {
        if (BackgroundObjects[i] != 0)
            BackgroundObjects[i]->speed += CConfig::backgroundAcceleration;
    }

    return 0;
}
// -----------------------------------------------------------------------------------

