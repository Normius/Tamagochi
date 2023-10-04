#include "Engine.h"

// ---------------------------- Class Engine -------------------------------------------------------------

// ------------ Конструктор
CEngine::CEngine()
    :TimerId(WM_USER + 1), GameState(EGameState::StartLevel), lastCloudTimerDisappear(CConfig::currentFrameValue), newCloudTimerDelay(CConfig::FPS * 4),
    lastCollisionObjectTimerDisappear(CConfig::currentFrameValue), newCollisionObjectTimerDelay(CConfig::FPS * 4), lastRoadBumpTimerDisappear(CConfig::currentFrameValue), newRoadBumpTimerDelay(CConfig::FPS * 4),
    currentMaxObjectsSpeed(0.0f), objectRestDistance(0.0f), clearStartObjects(false), Cactuses(CConfig::MaxCactuses), RoadStones(CConfig::MaxRoadStones), RoadBumps(CConfig::MaxRoadBumps), Clouds(CConfig::MaxClouds)
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

    RoadBumps[0].firstBumpType = true; //Неровность на дороге из 2 кочек
    RoadBumps[1].firstBumpType = false; //Неровность на дороге из кочки и ямы

    //Создаём вектор указателей на базовый класс для кактусов и птицы
    CollisionObjects.push_back(&Cactuses[0]);
    CollisionObjects.push_back(&Cactuses[1]);
    CollisionObjects.push_back(&Bird);

    BackgroundObjects.push_back(&Clouds[0]);
    BackgroundObjects.push_back(&Clouds[1]);
    BackgroundObjects.push_back(&Clouds[2]);
    BackgroundObjects.push_back(&Clouds[3]);
    BackgroundObjects.push_back(&RoadLine);
    BackgroundObjects.push_back(&RoadBumps[0]);
    BackgroundObjects.push_back(&RoadBumps[1]);
    BackgroundObjects.push_back(&RoadStones[0]);
    BackgroundObjects.push_back(&RoadStones[1]);

    int startCloudsCount = CConfig::GetRandom(1, 4); //Задаём стартовое количество облаков

    //Отрисовываем стартовые облака
    for (int i = 0; i < startCloudsCount; ++i)
    {
        Clouds[i].FirstActivate();
        Clouds[i].Redraw();
    }

    Dinosaur.Redraw();
    
    RoadLine.Activate();
    RoadLine.Redraw();

    RoadStones[0].FirstActivate();
    RoadStones[0].Redraw();

    //Тестовая часть
    if (GameState == EGameState::TestLevel)
    {
        Bird.TestActivate(400.0f, 125.0f);
        Bird.Redraw();

        Cactuses[0].TestActivate(600.0f, CCactus::startPos_Y);
        Cactuses[0].Redraw();

        RoadBumps[0].TestActivate();
        RoadBumps[0].Redraw(); //Неровность на дороге из 2 кочек
    }

    StartPlatform.pos_X = static_cast<float>(CConfig::GetRandom(200, 700));
}
// -----------------------------------------------------------------------------------


// ------------ Отрисовка кадра
void CEngine::DrawFrame(HDC hdc, RECT& paintArea)
{
    //Очистка объектов игры
    for (auto* backgroundObject : BackgroundObjects)
        backgroundObject->Clear(hdc, paintArea);

    for (auto* collisionObject : CollisionObjects)
        collisionObject->Clear(hdc, paintArea);

    Dinosaur.Clear(hdc, paintArea);

    Scoreboard.Clear(hdc, paintArea);

    //Отрисовка объектов игры
    for (auto* backgroundObject : BackgroundObjects)
        backgroundObject->Draw(hdc, paintArea);

    Dinosaur.Draw(hdc, paintArea);

    for (auto* collisionObject : CollisionObjects)
        collisionObject->Draw(hdc, paintArea);

    //Очистка стартовых объектов игры
    if (GameState == EGameState::RestartRunLevel && clearStartObjects == true) //Очистку стартовой платформы нужно проводить после перерисовки Дино, чтобы он переместился в начало уровня, а затем очистилась платформа
    {
        PopupTip.Clear(hdc, paintArea);
        ControlTip.Clear(hdc, paintArea);
        StartPlatform.Clear(hdc, paintArea);

        RoadStones[0].Draw(hdc, paintArea);
        RoadStones[1].Draw(hdc, paintArea);

        RoadLine.Draw(hdc, paintArea);

        RoadBumps[0].Draw(hdc, paintArea);
        RoadBumps[1].Draw(hdc, paintArea);
    }

    if (GameState == EGameState::StartLevel || GameState == EGameState::TeleportingDinosaur) //Рисуем стартовую платформу и подсказку по управлению только на стартовом уровне и во время телепортации
    {
        StartPlatform.Draw(hdc, paintArea);
        ControlTip.Draw(hdc, paintArea);
    }

    if ( (GameState == EGameState::StartLevel && Dinosaur.ReadyForStartPlatfrom(StartPlatform) == true) || GameState == EGameState::LoseRunLevel) //Всплывающую подсказку рисуем только на стартовом уровне, когда находимся в нужном месте
        PopupTip.Draw(hdc, paintArea);
    else if (GameState == EGameState::StartLevel && Dinosaur.ReadyForStartPlatfrom(StartPlatform) == false)
        PopupTip.Clear(hdc, paintArea);

    Scoreboard.Draw(hdc, paintArea);
}
// -----------------------------------------------------------------------------------


// ------------ Обработка клавиш
int CEngine::OnKey(EKeyType keyType, bool keyPressed) //keyPressed == true (нажатие), == false (отжатие)
{
    switch (keyType)
    {
    case EKeyType::LeftKey:
        if (GameState == EGameState::RunLevel || GameState == EGameState::StartLevel || GameState == EGameState::TestLevel)
            Dinosaur.CheckHorizontalDirection(true, keyPressed);

        break;

    case EKeyType::RightKey:
        if (GameState == EGameState::RunLevel || GameState == EGameState::StartLevel || GameState == EGameState::TestLevel)
            Dinosaur.CheckHorizontalDirection(false, keyPressed);

        break;

    case EKeyType::DownKey:
        if (GameState == EGameState::RunLevel || GameState == EGameState::StartLevel || GameState == EGameState::TestLevel)
            Dinosaur.SetBodyState(EDinosaurBodyState::Crawling);

        break;

    case EKeyType::UpKey:
        if (GameState == EGameState::RunLevel || GameState == EGameState::StartLevel || GameState == EGameState::TestLevel)
            Dinosaur.SetBodyState(EDinosaurBodyState::Standing);

        break;

    case EKeyType::SpaceKey:

        //Если находимся в состоянии рестарта уровня, то прыжком стартуем уровень
        if (GameState == EGameState::RestartRunLevel)
        {
            GameState = EGameState::RunLevel;
            Dinosaur.SetLevelState(EDinosaurLevelState::RunLevel);
            Dinosaur.DinosaurMovingState = EDinosaurMovingState::MovingRight;
        }

        if (GameState == EGameState::RunLevel || GameState == EGameState::StartLevel || GameState == EGameState::TestLevel)
        {
            if (keyPressed)
                Dinosaur.Jump();
        }

        break;

    case EKeyType::ActionKey_E:
        if (GameState == EGameState::StartLevel && Dinosaur.ReadyForStartPlatfrom(StartPlatform) == true) //Телепортация в начало уровня со стартовой платформы при нажатии Е
        {
            GameState = EGameState::TeleportingDinosaur;
            Dinosaur.SetLevelState(EDinosaurLevelState::Teleporting);
            Dinosaur.verticalSpeed = 3.0f;
            Dinosaur.onStartPlatform = false;
        }
        else if (GameState == EGameState::LoseRunLevel) //Телепортация в начало уровня после столкновения с препятствием
            RestartLevel();

        break;
    }

    return 0;
}
// -----------------------------------------------------------------------------------


// ------------ Получаем наибольшую скорость из всех объектов
float CEngine::GetMaxSpeed()
{
    if (fabs(Dinosaur.MaxSpeed_Y) > Bird.birdSpeed) //Проверяем скорость птицы, так как она имеет увеличенную на 5 скорость, относительно других объектов заднего плана
        return fabs(Dinosaur.MaxSpeed_Y);
    else
        return Bird.speed;
}
// -----------------------------------------------------------------------------------


// ------------ Проверяем расстояние между объектами столкновения, чтобы они не шли подряд и можно было перепрыгнуть
bool CEngine::CheckCollisionObjectsDistance()
{
    bool reachedMinDistance = false;

    for (auto* collisionObject : CollisionObjects)
    {
        if (collisionObject->CheckActive() == true)
        {
            if (collisionObject->GetPos_X() <= static_cast<float>(CConfig::rightBorder) - CCollisionObjects::minDistanceBetweenCollisionObjects)
                reachedMinDistance = true;

            break;
        }
        else continue;
    }

    return reachedMinDistance;
}
// -----------------------------------------------------------------------------------


// ------------ Проверяем объекты на столкновения при перемещении
void CEngine::CheckCollisions()
{
    for (auto* collisionObject : CollisionObjects)
    {
        if (collisionObject->CheckActive() == false)
            continue;

        if (collisionObject->CheckHit(Dinosaur.dinoCollisionRects, Dinosaur.collisionRectsAmount) == true)
        {
            GameState = EGameState::LoseRunLevel;
            CBackgroundObjects::speed = 0.0f;
            Dinosaur.collision = true;
            return;
        }
    }
}
//---------------------------------------------------------------------------------------------------


//--------------------------------------------------- Передвижение движущихся объектов ------------------------------------------------
void CEngine::MoveCollisionObjects()
{
    //Двигаем объектов столкновения на небольшие шажки (вытащили из метода Move)
    objectRestDistance += currentMaxObjectsSpeed; //Максимальное расстояние, на которое необходимо сдвинуть объекты в течение текущего кадра

    while (objectRestDistance > 0.0f)
    {
        if (GameState == EGameState::StartLevel || GameState == EGameState::TestLevel)
            Dinosaur.MoveHorizontal(currentMaxObjectsSpeed);

        Dinosaur.MoveVertical(currentMaxObjectsSpeed);

        Dinosaur.SetDinoCollisionRects();

        if (Dinosaur.collision == true)
            break;

        if (GameState == EGameState::RunLevel)
        {
            for (auto* collisionObject : CollisionObjects)
                collisionObject->Move(currentMaxObjectsSpeed);
        }

        CheckCollisions(); //Проверяем столкновения после сдвига птиц и кактусов

        if (Dinosaur.collision == true)
            break;

        objectRestDistance -= CConfig::minShift; //Вычитаем минимальный шаг. Таким образом Дино и объекты столкновения проходят одинаковое количество шагов (но разных по длине +-CConfig::minShift)
    }

    //Корректируем крайние позиции Дино по вертикали и горизонтали после всех минимальных перемещений (вне while)

    Dinosaur.CorrectVerticalEdgePosition();

    if (GameState == EGameState::StartLevel || GameState == EGameState::TestLevel)
        Dinosaur.CorrectHorizontalEdgePosition();

    if (GameState == EGameState::StartLevel)
        Dinosaur.CorrectPositionWithStartPlatform(StartPlatform); 
}
//---------------------------------------------------------------------------------------------------


//--------------------------------------------------- Активация объектов столкновения ------------------------------------------------
void CEngine::ActivateCollisionObjects()
{
    //Активируем по таймеру случайный объект столкновения
    if (lastCollisionObjectTimerDisappear + newCollisionObjectTimerDelay <= CConfig::currentFrameValue)
    {
        newCollisionObjectTimerDelay = CConfig::FPS / 4 * CConfig::GetRandom(1, 3);
        lastCollisionObjectTimerDisappear = CConfig::currentFrameValue + newCollisionObjectTimerDelay;
    
        int collisionObjectIndex = CConfig::GetRandom(0, CConfig::MaxCollisionObjects - 1);
        
        for (int i = collisionObjectIndex; i < CConfig::MaxCollisionObjects; ++i)
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
    
            ++collisionObjectIndex; //Если попали на объект, который уже активирован, то увеличиваем индекс на один и пробуем ещё раз
            if (collisionObjectIndex >= CConfig::MaxCollisionObjects) //Если индекс вышел за пределы, обнуляем
                collisionObjectIndex = 0;
        }
    }
}
//---------------------------------------------------------------------------------------------------

// ------------ Проверяем расстояние между неровностями на дороге, чтобы они не шли подряд
bool CEngine::CheckRoadBumpsDistance()
{
    bool reachedMinDistance = false;

    for (auto &roadBump : RoadBumps)
    {
        if (roadBump.active == true)
        {
            if (roadBump.pos_X <= static_cast<float>(CConfig::rightBorder) - CCollisionObjects::minDistanceBetweenCollisionObjects)
                reachedMinDistance = true;

            break;
        }
        else continue;
    }

    return reachedMinDistance;
}
// -----------------------------------------------------------------------------------


//--------------------------------------------------- Активация неровностей на дороге ------------------------------------------------
void CEngine::ActivateRoadBumps()
{
    //Активируем по таймеру неровности на дороге
    if (lastRoadBumpTimerDisappear + newRoadBumpTimerDelay <= CConfig::currentFrameValue) //Отрисовываем новое облако только через некоторую временную паузу
    {
        newRoadBumpTimerDelay = CConfig::FPS / 5 * CConfig::GetRandom(3, 6); //Случайное время до появления нового облака
        lastRoadBumpTimerDisappear = CConfig::currentFrameValue + newRoadBumpTimerDelay; //Обновляем время последнего исчезновения облака

        int bumpObjectIndex = CConfig::GetRandom(0, CConfig::MaxRoadBumps - 1);

        bool anyActive = false; //Накопительная переменная для проверки, активен ли хотя бы один объект

        for (auto &roadBump : RoadBumps)
            anyActive = anyActive || roadBump.active; //Если ни один объект не активен, то переменная останется false
            
        if (anyActive == false) //Активируем объект без каких либо условий, если ни один не активен
            RoadBumps[bumpObjectIndex].Activate(); 

        if (RoadBumps[bumpObjectIndex].active == false && CheckRoadBumpsDistance() == true) //Активируем второй объект, если первый уже активен, только в случае, если между ними достаточное расстояние
            RoadBumps[bumpObjectIndex].Activate();
    }
}
//---------------------------------------------------------------------------------------------------

//--------------------------------------------------- Активация облаков ------------------------------------------------
void CEngine::ActivateClouds()
{
    //Активируем облака по таймеру
    if (lastCloudTimerDisappear + newCloudTimerDelay <= CConfig::currentFrameValue) //Отрисовываем новое облако только через некоторую временную паузу
    {
        newCloudTimerDelay = CConfig::FPS / 2 * CConfig::GetRandom(1, 3); //Случайное время до появления нового облака
        lastCloudTimerDisappear = CConfig::currentFrameValue + newCloudTimerDelay; //Обновляем время последнего исчезновения облака

        for (auto &cloud : Clouds) //Перебираем все облака, находим ушедшее за экран и отрисовываем его
        {
            if (cloud.active == false)
            {
                cloud.Activate();
                break;
            }
        }
    }
}
//---------------------------------------------------------------------------------------------------

//--------------------------------------------------- Передвижение и перерисовка объектов заднего плана ------------------------------------------------
void CEngine::ActivateRoadStones()
{
    //Зацикливаем камни (штрихи) на дороге
    if (RoadStones[0].pos_X <= CConfig::leftBorder && RoadStones[1].active == false)
        RoadStones[1].Activate();
    else if (RoadStones[1].pos_X <= CConfig::leftBorder && RoadStones[0].active == false)
        RoadStones[0].Activate();
}
//---------------------------------------------------------------------------------------------------

// ------------ Метод для обработки действий по таймеру
int CEngine::OnTimer()
{
    if (GameState == EGameState::LoseRunLevel)
        return 0;

    ++CConfig::currentFrameValue;

    CConfig::slowCurrentFrameValue += 0.5f;

    currentMaxObjectsSpeed = GetMaxSpeed(); //Получаем текущую максимальную скорость среди всех объектов

    MoveCollisionObjects();

    ActivateRoadBumps();
    ActivateClouds();
    ActivateRoadStones();

    Dinosaur.Redraw();

    for (auto* collisionObject : CollisionObjects)
        collisionObject->Redraw();

    switch (GameState)
    {
    case EGameState::StartLevel:

        PopupTip.Redraw();
        Dinosaur.GravityFalling();

        break;

    case EGameState::RestartRunLevel:

        Scoreboard.Redraw();

        break;

    case EGameState::RunLevel:

        ActivateCollisionObjects();
        for (auto* backgroundObject : BackgroundObjects)
            backgroundObject->Move(currentMaxObjectsSpeed);

        CBackgroundObjects::speed += CConfig::backgroundAcceleration; //Ускорение передвижения заднего плана
        CConfig::score++;
        Dinosaur.GravityFalling();
        Scoreboard.Redraw();

        break;

    case EGameState::LoseRunLevel:

        PopupTip.Redraw();

        break;

    case EGameState::TestLevel:

        Dinosaur.GravityFalling();

        break;

    case EGameState::TeleportingDinosaur:

        if (static_cast<int>(Dinosaur.pos_Y) + Dinosaur.height == Dinosaur.OnGroundLegsPos_Y)
            FirstStartLevel();

        break;

    default:

        break;
    }

    //TO DO: !!! Заменил if на switch/case 
    //if (GameState == EGameState::StartLevel || GameState == EGameState::LoseRunLevel)
    //    PopupTip.Redraw();

    //if (Dinosaur.collision == true)
    //{
    //    Scoreboard.UpdateHighScore();
    //    return 0; //Если зафиксировано столкновение, выходим из ф-ции
    //}   

    ////Каждый кадр ускоряем скорость объектов заднего фона (кроме облаков)
    //if (GameState == EGameState::RunLevel)
    //{
    //    ActivateCollisionObjects();
    //    MoveBackgroundObjects();
    //    CBackgroundObjects::speed += CConfig::backgroundAcceleration;
    //    CConfig::score++;
    //}

    ////Увеличиваем сдвиг при падении, то есть ускоряемся при движении вниз (значение подобрано вручную)
    //if (GameState == EGameState::RunLevel || GameState == EGameState::StartLevel || GameState == EGameState::TestLevel)
    //    Dinosaur.GravityFalling();

    ////Если Дино телепортируется, то ждём, пока он опустится до земли, а затем активируем старт уровня
    //if (GameState == EGameState::TeleportingDinosaur && static_cast<int>(Dinosaur.pos_Y) + Dinosaur.height == Dinosaur.OnGroundLegsPos_Y)
    //    FirstStartLevel();

    //if (GameState == EGameState::RunLevel || GameState == EGameState::RestartRunLevel)
    //    Scoreboard.Redraw();        

    return 0;
}
// -----------------------------------------------------------------------------------

// ------------ Старт уровня со стартовой платформы
void CEngine::FirstStartLevel()
{
    GameState = EGameState::RestartRunLevel;

    PopupTip.Redraw();
    ControlTip.Redraw();
    
    StartPlatform.Redraw();
    clearStartObjects = true;

    RoadLine.Activate();
    RoadStones[0].FirstActivate();
    RoadLine.Redraw();
    RoadStones[0].Redraw();

    Dinosaur.RestartLevel();

    CBackgroundObjects::speed = CBackgroundObjects::startSpeed;
}
// -----------------------------------------------------------------------------------

// ------------ Рестарт уровня при проигрыше
void CEngine::RestartLevel()
{
    GameState = EGameState::RestartRunLevel;

    PopupTip.Redraw();
    
    CConfig::score = 0;

    for (auto* collisionObject : CollisionObjects)
        collisionObject->Deactivate();

    Dinosaur.RestartLevel();

    CBackgroundObjects::speed = CBackgroundObjects::startSpeed;
}
// -----------------------------------------------------------------------------------

