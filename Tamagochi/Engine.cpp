#include "Engine.h"

// ---------------------------- Class Engine -------------------------------------------------------------

// ------------ Конструктор
CEngine::CEngine()
    :GameState(EGameState::FreeMovingLevel), CollisionObjects{ 0 }, lastCloudTimerDisappear(0), newCloudTimerDelay(CConfig::FPS * 4),
    lastCollisionObjectTimerDisappear(0), newCollisionObjectTimerDelay(CConfig::FPS * 2), lastRoadBumpTimerDisappear(0), newRoadBumpTimerDelay(CConfig::FPS * 2), objectRestDistance(0.0f)
{
}
// -----------------------------------------------------------------------------------

// ------------ Инициализация начальных данных
void CEngine::InitEngine(HWND hwnd)
{
    CConfig::Hwnd = hwnd;

    SetTimer(CConfig::Hwnd, TimerId, 1000 / CConfig::FPS, 0);

    SYSTEMTIME systemTime; //Струткура для хранения системеного времени
    GetSystemTime(&systemTime); //Получаем текущее системное время и сохраняем

    srand(systemTime.wMilliseconds); //Устанавливаем случайный рандом в зависимости от текущего значения миллесекунд

    //Инициализируем указатели
    /*for (int i = 0; i < CConfig::MaxClouds; ++i)
    {
        BackgroundObjects[i] = &Clouds[i];
    }*/

    //TO DO: Переделать инициализацию массивов, скомпоновать как-то по-другому
    //BackgroundObjects[CConfig::MaxClouds] = &RoadLine;

    //BackgroundObjects[CConfig::MaxBackgroundObjects - 4] = &RoadStones[0];
    //BackgroundObjects[CConfig::MaxBackgroundObjects - 3] = &RoadStones[1];

    RoadBumps[0].firstBumpType = true; //Неровность на дороге из 2 кочек
    RoadBumps[1].firstBumpType = false; //Неровность на дороге из кочки и ямы

    //BackgroundObjects[CConfig::MaxBackgroundObjects - 2] = &RoadBumps[0];
    //BackgroundObjects[CConfig::MaxBackgroundObjects - 1] = &RoadBumps[1];

    CollisionObjects[0] = &Cactuses[0];
    CollisionObjects[1] = &Cactuses[1];
    CollisionObjects[2] = &Bird;

    /*for (int i = 0; i < CConfig::MaxCactuses; ++i)
    {
        CollisionObjects[i] = &Cactuses[i];
    }

    CollisionObjects[CConfig::MaxCollisionObjects - 1] = &Bird;*/


    int startCloudsCount = CConfig::GetRandom(1, 4); //Задаём стартовое количество облаков

    //Отрисовываем стартовые облака
    for (int i = 0; i < startCloudsCount; ++i)
    {
        Clouds[i].FirstActivate();
    }

    for (int i = 0; i < startCloudsCount; ++i)
    {
        if (Clouds[i].active == true)
            Clouds[i].Redraw();
    }

    RoadLine.Activate();
    RoadStones[0].FirstActivate();

    Dinosaur.Redraw();
    RoadLine.Redraw();
    RoadStones[0].Redraw();

    Bird.TestActivate(400.0f, Bird.startPos_Y);
    Bird.Redraw();

    Cactuses[0].TestActivate(600.0f, CCactus::startPos_Y);
    Cactuses[0].Redraw();

    //RoadBumps[1].TestActivate();
    //RoadBumps[1].Redraw();

    //RoadLevel.Redraw();
    //Bird.Redraw();
    //Cactus.Redraw();
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка кадра
void CEngine::DrawFrame(HDC hdc, RECT& paintArea)
{

    /*for (int i = 0; i < CConfig::MaxBackgroundObjects; ++i)
    {
        BackgroundObjects[i]->Draw(hdc, paintArea);
    }*/

    for (int i = 0; i < CConfig::CConfig::MaxClouds; ++i)
    {
        Clouds[i].Draw(hdc, paintArea);
    }

    RoadLine.Draw(hdc, paintArea);
    RoadStones[0].Draw(hdc, paintArea);
    RoadStones[1].Draw(hdc, paintArea);
    RoadBumps[0].Draw(hdc, paintArea);
    RoadBumps[1].Draw(hdc, paintArea);
    
    for (int i = 0; i < CConfig::MaxCollisionObjects; ++i)
    {
        CollisionObjects[i]->Draw(hdc, paintArea);
    }

    Dinosaur.Draw(hdc, paintArea);
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

float CEngine::GetMaxSpeed()
{
    if (fabs(Dinosaur.verticalSpeed) > CBackgroundObjects::speed)
        return fabs(Dinosaur.verticalSpeed);
    else
        return CBackgroundObjects::speed;
}

// ------------ Метод для обработки действий по таймеру
int CEngine::OnTimer()
{
    if (GameState == EGameState::LoseRunLevel)
        return 0;

    ++CConfig::currentFrameValue; //значение таймера

    CConfig::slowCurrentFrameValue += 0.5f;

    //Активируем по таймеру неровности на дороге
    if (lastRoadBumpTimerDisappear + newRoadBumpTimerDelay == CConfig::currentFrameValue) //Отрисовываем новое облако только через некоторую временную паузу
    {
        newRoadBumpTimerDelay = CConfig::FPS / 4 * CConfig::GetRandom(1, 4); //Случайное время до появления нового облака
        lastRoadBumpTimerDisappear = CConfig::currentFrameValue + newRoadBumpTimerDelay; //Обновляем время последнего исчезновения облака

        int bumpObjectIndex = CConfig::GetRandom(0, CConfig::MaxRoadBumps - 1);
        if (RoadBumps[bumpObjectIndex].active == false)
        {
            RoadBumps[bumpObjectIndex].Activate();
        }
    }

    //Двигаем неровности на дороге
    if (GameState == EGameState::FreeMovingLevel)
    {
        for (int i = 0; i < CConfig::MaxRoadBumps; i++)
        {
            RoadBumps[i].Move(CBackgroundObjects::speed);
        }
    }

    //Активируем облака по таймеру
    if (lastCloudTimerDisappear + newCloudTimerDelay == CConfig::currentFrameValue) //Отрисовываем новое облако только через некоторую временную паузу
    {
        newCloudTimerDelay = CConfig::FPS / 2 * CConfig::GetRandom(2, 4); //Случайное время до появления нового облака
        lastCloudTimerDisappear = CConfig::currentFrameValue + newCloudTimerDelay; //Обновляем время последнего исчезновения облака

        for (int i = 0; i < CConfig::MaxClouds; ++i) //Перебираем все облака, находим ушедшее за экран и отрисовываем его
        {
            if (Clouds[i].active == false)
            {
                Clouds[i].Activate();
                break;
            }
        }
    }

    //Зацикливаем камни (штрихи) на дороге
    if (RoadStones[0].pos_X <= CConfig::leftBorder && RoadStones[1].active == false)
        RoadStones[1].Activate();
    else if (RoadStones[1].pos_X <= CConfig::leftBorder && RoadStones[0].active == false)
        RoadStones[0].Activate();

    //Двигаем камни (штрихи) на дороге
    RoadStones[0].Move(CBackgroundObjects::speed);
    RoadStones[1].Move(CBackgroundObjects::speed);

    //Передвигаем облака (объединить в сдвиг BackgroundObjects)
    if (GameState == EGameState::FreeMovingLevel)
    {
        for (int i = 0; i < CConfig::MaxClouds; i++)
        {
            Clouds[i].Move(Clouds[i].cloudsSpeed);
        }
    }







    //Активируем по таймеру случайный объект столкновения
    if (lastCollisionObjectTimerDisappear + newCollisionObjectTimerDelay == CConfig::currentFrameValue)
    {
        newCollisionObjectTimerDelay = CConfig::FPS / 4 * CConfig::GetRandom(1, 4);
        lastCollisionObjectTimerDisappear = CConfig::currentFrameValue + newCollisionObjectTimerDelay;

        int collisionObjectIndex = CConfig::GetRandom(0, CConfig::MaxCollisionObjects - 1);

        for (int i = 0; i < CConfig::MaxCollisionObjects; ++i)
        {
            if (CollisionObjects[collisionObjectIndex]->CheckActive() == false) //TO DO Если попадают на активный объект, то ничего не отображают, хотя таймер прошёл
            {
                CollisionObjects[collisionObjectIndex]->Activate();
                break;
            }

            ++collisionObjectIndex;
            if (collisionObjectIndex >= CConfig::MaxCollisionObjects)
                collisionObjectIndex = 0;
        }
    }


    //Смещение объектов столкновения на небольшие шажки (вытащили из метода Move)
    float currentMaxObjectsSpeed = GetMaxSpeed();
    objectRestDistance += currentMaxObjectsSpeed;
     //Увеличиваем сдвиг при падении, то есть ускоряемся при движении вниз (значение подобрано вручную)

    while (objectRestDistance > 0.0f)
    {
        Dinosaur.MoveHorizontal(currentMaxObjectsSpeed);
        Dinosaur.MoveVertical(currentMaxObjectsSpeed);
        Dinosaur.SetDinoCollisionRects();

        for (int i = 0; i < CConfig::MaxCollisionObjects; ++i)
        {
            if (CollisionObjects[i] != 0)
            {
                if (CollisionObjects[i]->CheckHit(Dinosaur.dinoCollisionRects, Dinosaur.collisionRectsAmount) == true)
                {
                    GameState = EGameState::LoseRunLevel;
                    CBackgroundObjects::speed = 0.0f;
                    Dinosaur.collision = true;
                    break;
                }

                CollisionObjects[i]->Move(currentMaxObjectsSpeed);
            }
        }
        if (Dinosaur.collision == true)
            break;
        objectRestDistance -= CConfig::minShift;
    }

    //Перерисовка (Redraw) объектов столкновения (вытащили из метода Move)
    for (int i = 0; i <= CConfig::MaxCollisionObjects - 1; ++i)
    {
        if (CollisionObjects[i] != 0)
            CollisionObjects[i]->Redraw();
    }

    Dinosaur.Redraw();

    if (GameState == EGameState::FreeMovingLevel)
        CBackgroundObjects::speed += CConfig::backgroundAcceleration;

    if (static_cast<int>(Dinosaur.pos_Y) + Dinosaur.height != Dinosaur.OnGroundLegsPos_Y) //Если Дино на земле, ничего не делаем
        Dinosaur.verticalSpeed += 2.9f;

    return 0;
}
// -----------------------------------------------------------------------------------

