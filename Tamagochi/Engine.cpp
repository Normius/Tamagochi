#include "Engine.h"

// ---------------------------- Class Engine -------------------------------------------------------------

// ------------ Конструктор
CEngine::CEngine()
    :TimerId(WM_USER + 1), GameState(EGameState::RunLevel), CollisionObjects{ 0 }, lastCloudTimerDisappear(0), newCloudTimerDelay(CConfig::FPS * 4),
    lastCollisionObjectTimerDisappear(0), newCollisionObjectTimerDelay(CConfig::FPS * 2), lastRoadBumpTimerDisappear(0), newRoadBumpTimerDelay(CConfig::FPS * 2), 
    currentMaxObjectsSpeed(0.0f), objectRestDistance(0.0f)
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

    if (GameState == EGameState::FreeMovingLevel)
    {
        Bird.TestActivate(400.0f, Bird.startPos_Y);
        Bird.Redraw();

        Cactuses[0].TestActivate(600.0f, CCactus::startPos_Y);
        Cactuses[0].Redraw();
    }
}
// -----------------------------------------------------------------------------------

// ------------ Отрисовка кадра
void CEngine::DrawFrame(HDC hdc, RECT& paintArea)
{
    /*if (GameState != EGameState::LoseRunLevel)
    {
        for (int i = 0; i < CConfig::CConfig::MaxClouds; ++i)
        {
            Clouds[i].Clear(hdc, paintArea);
        }

        RoadLine.Clear(hdc, paintArea);
        RoadStones[0].Clear(hdc, paintArea);
        RoadStones[1].Clear(hdc, paintArea);
        RoadBumps[0].Clear(hdc, paintArea);
        RoadBumps[1].Clear(hdc, paintArea);

        for (int i = 0; i < CConfig::MaxCollisionObjects; ++i)
        {
            CollisionObjects[i]->Clear(hdc, paintArea);
        }

        Dinosaur.Clear(hdc, paintArea);
    }*/

    for (int i = 0; i < CConfig::CConfig::MaxClouds; ++i)
    {
        Clouds[i].Clear(hdc, paintArea);
    }

    RoadLine.Clear(hdc, paintArea);
    RoadStones[0].Clear(hdc, paintArea);
    RoadStones[1].Clear(hdc, paintArea);
    RoadBumps[0].Clear(hdc, paintArea);
    RoadBumps[1].Clear(hdc, paintArea);

    for (int i = 0; i < CConfig::MaxCollisionObjects; ++i)
    {
        CollisionObjects[i]->Clear(hdc, paintArea);
    }

    Dinosaur.Clear(hdc, paintArea);

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
        if (GameState == EGameState::FreeMovingLevel || GameState == EGameState::RunLevel)
        {
            Dinosaur.CheckHorizontalDirection(true, keyPressed);
        }
        break;

    case EKeyType::RightKey:
        if (GameState == EGameState::FreeMovingLevel || GameState == EGameState::RunLevel)
        {
            Dinosaur.CheckHorizontalDirection(false, keyPressed);
        }
        break;

    case EKeyType::DownKey:
        if (GameState == EGameState::FreeMovingLevel || GameState == EGameState::RunLevel)
        {
            Dinosaur.SetBodyState(EDinosaurBodyState::Crawling);
            break;
        }

    case EKeyType::UpKey:
        if (GameState == EGameState::FreeMovingLevel || GameState == EGameState::RunLevel)
        {
            Dinosaur.SetBodyState(EDinosaurBodyState::Standing);
            break;
        }

    case EKeyType::SpaceKey:
        if (GameState == EGameState::FreeMovingLevel || GameState == EGameState::RunLevel)
        {
            if (keyPressed)
                Dinosaur.Jump();
            break;
        }
    }

    return 0;
}
// -----------------------------------------------------------------------------------

float CEngine::GetMaxSpeed()
{
    if (fabs(Dinosaur.MaxSpeed_Y) > CBackgroundObjects::speed)
        return fabs(Dinosaur.MaxSpeed_Y);
    else
        return CBackgroundObjects::speed;
}

bool CEngine::CheckCollisionObjectsDistance()
{
    bool reachedMinDistance = false;

    for (int i = 0; i < CConfig::MaxCollisionObjects; ++i)
    {
        if (CollisionObjects[i]->CheckActive() == true)
        {
            if (CollisionObjects[i]->GetPos_X() <= + static_cast<float>(CConfig::rightBorder) - CCollisionObjects::minDistanceBetweenCollisionObjects)
                reachedMinDistance = true;

            break;
        }
        else continue;
    }

    return reachedMinDistance;
}

// ------------ Метод для обработки действий по таймеру
int CEngine::OnTimer()
{
    if (GameState == EGameState::LoseRunLevel)
        return 0;

    ++CConfig::currentFrameValue; //значение таймера

    CConfig::slowCurrentFrameValue += 0.5f;




    //--------------------------------------------------- Активация движущихся объектов ------------------------------------------------
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

    //Активируем по таймеру случайный объект столкновения
    if (lastCollisionObjectTimerDisappear + newCollisionObjectTimerDelay == CConfig::currentFrameValue)
    {
        newCollisionObjectTimerDelay = CConfig::FPS / 4 * CConfig::GetRandom(1, 4);
        lastCollisionObjectTimerDisappear = CConfig::currentFrameValue + newCollisionObjectTimerDelay;

        int collisionObjectIndex = CConfig::GetRandom(0, CConfig::MaxCollisionObjects - 1);

        for (int i = 0; i < CConfig::MaxCollisionObjects; ++i)
        {
            if (CCollisionObjects::CollisionObjectsActiveCount == 0) //Если на экране 0 активных объектов, активируем любой
            {
                CollisionObjects[collisionObjectIndex]->Activate();
                break;
            }

            if (CollisionObjects[collisionObjectIndex]->CheckActive() == false && CheckCollisionObjectsDistance() == true) //Если уже есть активный объект на экране, проверяем достаточное ли расстояние до другого активного объекта
            {
                CollisionObjects[collisionObjectIndex]->Activate();
                break;
            }

            ++collisionObjectIndex;
            if (collisionObjectIndex >= CConfig::MaxCollisionObjects)
                collisionObjectIndex = 0;
        }
    }
    //---------------------------------------------------------------------------------------------------




    //--------------------------------------------------- Передвижение движущихся объектов ------------------------------------------------
    
    if (GameState == EGameState::RunLevel)
    {
        //Двигаем неровности на дороге
        for (int i = 0; i < CConfig::MaxRoadBumps; i++)
        {
            RoadBumps[i].Move(CBackgroundObjects::speed);
        } 

        //Двигаем камни (штрихи) на дороге
        RoadStones[0].Move(CBackgroundObjects::speed);
        RoadStones[1].Move(CBackgroundObjects::speed);

        //Двигаем облака
        for (int i = 0; i < CConfig::MaxClouds; i++)
        {
            Clouds[i].Move(Clouds[i].cloudsSpeed);
        }
    }

    //Двигаем объектов столкновения на небольшие шажки (вытащили из метода Move)
    currentMaxObjectsSpeed = GetMaxSpeed(); //Получаем текущую максимальную скорость среди всех объектов
    objectRestDistance += currentMaxObjectsSpeed; //Максимальное расстояние, на которое необходимо сдвинуть объекты в течение текущего кадра

    while (objectRestDistance > 0.0f)
    {
        if (GameState == EGameState::FreeMovingLevel)
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
                    Beep(600, 25);
                    break;
                }
            }

            if (GameState == EGameState::RunLevel)
                CollisionObjects[i]->Move(currentMaxObjectsSpeed);
        }
        if (Dinosaur.collision == true)
            break;

        objectRestDistance -= CConfig::minShift; //Вычитаем минимальный шаг. Таким образом Дино и объекты столкновения проходят одинаковое количество шагов (но разных по длине +-CConfig::minShift)
    }
    //---------------------------------------------------------------------------------------------------

    Dinosaur.Redraw();

    //Перерисовка (Redraw) объектов столкновения (вытащили из метода Move)
    if (GameState == EGameState::RunLevel)
    {
        for (int i = 0; i <= CConfig::MaxCollisionObjects - 1; ++i)
        {
            if (CollisionObjects[i] != 0)
                CollisionObjects[i]->Redraw();
        }
    }


    if (GameState == EGameState::RunLevel)
        CBackgroundObjects::speed += CConfig::backgroundAcceleration;

    //TO DO: !!!Вынести в метод Динозавра, связанный с падением
    //Увеличиваем сдвиг при падении, то есть ускоряемся при движении вниз (значение подобрано вручную)
    if (GameState == EGameState::RunLevel)
    {
        if (static_cast<int>(Dinosaur.pos_Y) + Dinosaur.height != Dinosaur.OnGroundLegsPos_Y) //Если Дино на земле, ничего не делаем
            Dinosaur.verticalSpeed += 4.8f;
    }

    return 0;
}
// -----------------------------------------------------------------------------------

