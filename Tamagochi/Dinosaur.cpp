#include "Dinosaur.h"

// ---------------------------- Класс персонажа Dino -------------------------------------------------------------

//Конструктор
CDinosaur::CDinosaur()
    :DinosaurDirectionState(EDinosaurDirectionState::Right), DinosaurMovingState(EDinosaurMovingState::Stop), collision(false), onStartPlatform(false), dinoCollisionRects{ 0 },
     pos_X(startPos_X), pos_Y(static_cast<float>(standingPos_Y)), rgnPos_X(0), rgnPos_Y(0), height(standingHeight), width(standingWidth), onGroundLegsPos_Y(standingPos_Y + standingHeight),
     falling(false), horizontalSpeed(0.0f), verticalSpeed(0.0f), leftKeyDown(false), rightKeyDown(false), DinosaurLevelState(EDinosaurLevelState::StartLevel), DinosaurBodyState(EDinosaurBodyState::Standing),
     currentDinosaurPoints{ 0 }, prevDinosaurPoints{ 0 }, currentRect{ 0 }, prevRect{ 0 }
{
}

//Отрисовка персонажа Dino (основной метод)
void CDinosaur::Draw(HDC hdc, RECT& paintArea)
{
    RECT intersectionRect; //Нужен для ф-ции проверки пересечения прямоугольников, в него сохраняется область пересечения или 0

    if (!IntersectRect(&intersectionRect, &paintArea, &currentRect))
        return;

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
                if (pos_Y + height == onGroundLegsPos_Y)
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
                    if (pos_Y + height == onGroundLegsPos_Y)
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
                if (pos_Y + height == onGroundLegsPos_Y)
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
                if (pos_Y + height == onGroundLegsPos_Y)
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

//Очистка
void CDinosaur::Clear(HDC hdc, RECT& paintArea)
{
    RECT intersectionRect; //Нужен для ф-ции проверки пересечения прямоугольников, в него сохраняется область пересечения или 0

    if (!IntersectRect(&intersectionRect, &paintArea, &prevRect))
        return;

    CConfig::backgroundColor.SelectColor(hdc);

    Polygon(hdc, prevDinosaurPoints, dinosaurWithLegsPointsAmount);
}

//Перерисовка персонажа в новых координатах
void CDinosaur::Redraw()
{
    for (int i = 0; i < dinosaurWithLegsPointsAmount; ++i)
        prevDinosaurPoints[i] = currentDinosaurPoints[i];

    rgnPos_X = static_cast<int>(pos_X);
    rgnPos_Y = static_cast<int>(pos_Y);

    UpdateRgnPoints();

    prevRect = currentRect;

    currentRect.left = rgnPos_X;
    currentRect.top = rgnPos_Y;
    currentRect.right = currentRect.left + width;
    currentRect.bottom = currentRect.top + height;

    InvalidateRect(CConfig::Hwnd, &prevRect, FALSE);
    InvalidateRect(CConfig::Hwnd, &currentRect, FALSE);
}

//Установка состояния положения Дино (стоя/присед)
void CDinosaur::SetBodyState(EDinosaurBodyState newState)
{
    if (DinosaurBodyState == newState)
        return;

    if (newState == EDinosaurBodyState::Crawling)
    {
        if (height != crawlingHeight)
            pos_Y += static_cast<float>(standingHeight - crawlingHeight);

        DinosaurBodyState = EDinosaurBodyState::Crawling;
        height = crawlingHeight;
        width = crawlingWidth;
    }
    else
    {
        if (height != standingHeight)
            pos_Y -= static_cast<float>(standingHeight - crawlingHeight);

        DinosaurBodyState = EDinosaurBodyState::Standing;
        height = standingHeight;
        width = standingWidth;
    }
}

//Установка состояния Динозавра на уровне
void CDinosaur::SetLevelState(EDinosaurLevelState newstate)
{
    if (DinosaurLevelState == newstate)
        return;

    DinosaurLevelState = newstate;
}

//Перемещение по вертикали (падение вниз или движение вверх при прыжке) (работает по таймеру)
void CDinosaur::MoveVertical(float maxSpeed)
{
    if (static_cast<int>(pos_Y) + height == onGroundLegsPos_Y) //Если Дино на земле, ничего не делаем
        return;

    float nextStep = verticalSpeed / maxSpeed * CConfig::minShift;

    pos_Y += nextStep;
}

//Корректируем вертильное положение Динозавра (нахождение на земле и прыжки)
void CDinosaur::CorrectVerticalEdgePosition()
{
    if (onStartPlatform == true)  //Прекращаем падать, если находимся на платформе
        onGroundLegsPos_Y = static_cast<int>(CStartPlatform::pos_Y); //Нормальная позиция ног Дино на платформе
    else
        onGroundLegsPos_Y = (standingPos_Y + standingHeight); //Нормальная позиция ног Дино на земле

    if (static_cast<int>(pos_Y) + height >= onGroundLegsPos_Y) //Двигаемся вниз до тех пор, пока Дино не достигнет земли (или платформы)
    {
        pos_Y = static_cast<float>(onGroundLegsPos_Y - height);
        falling = false;
    }

    if (static_cast<int>(pos_Y) <= onGroundLegsPos_Y - height - maxJumpHeight && falling == false) //Когда Дино достигает максимальной высоты прыжка (или чуть больше), меняем знак шага перемещения на положительный для движения вниз (падения)
    {
        falling = true;
        verticalSpeed = 0.0f; //При достижении максимальной высоты перемещение приравниваем к 0 
    }
}

//Горизонтальное движение по таймеру 
void CDinosaur::MoveHorizontal(float maxSpeed)
{
    if (horizontalSpeed == 0.0f) //Если скорость = 0, ничего не делаем
        return;

    //Смещение на небольшие шажки 
    float nextStep = horizontalSpeed / maxSpeed * CConfig::minShift;

    pos_X += nextStep;
}

//Горизонтальное движение по таймеру 
void CDinosaur::CorrectHorizontalEdgePosition()
{
    if (static_cast<int>(pos_X) + width >= CConfig::rightBorder) //Правая граница
        pos_X = static_cast<float>(CConfig::rightBorder - width);

    if (static_cast<int>(pos_X) < CConfig::leftBorder) //Левая граница
        pos_X = static_cast<float>(CConfig::leftBorder);
}

//Выбор направления движения по горизонтали (обрабатывает нажатия и отжатие клавиш влево-вправо)
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
        if (pos_Y + height == onGroundLegsPos_Y)
        {
            DinosaurMovingState = EDinosaurMovingState::MovingLeft;
            horizontalSpeed = -maxSpeed_X;
        }
    }

    if (rightKeyDown == true) //Обработка нажатия левой клавиши
    {
        DinosaurDirectionState = EDinosaurDirectionState::Right;
        if (pos_Y + height == onGroundLegsPos_Y)
        {
            DinosaurMovingState = EDinosaurMovingState::MovingRight;
            horizontalSpeed = maxSpeed_X;
        }
    }
}

//Прыжок (начало прыжка, подъём Дино от земли, дальше работает метод MoveHorizontal)  (обрабатывает нажатие пробела)
void CDinosaur::Jump()
{
    if (static_cast<int>(pos_Y) + height == onGroundLegsPos_Y)
    {
        pos_Y -= 1.0f;
        verticalSpeed = -maxSpeed_Y;
    }
}

//Модель Динозавра поделена на 3 прямоугольника, с которыми проверяем столкновения других объектов
void CDinosaur::SetDinoCollisionRects()
{
    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    switch (DinosaurBodyState)
    {
    case EDinosaurBodyState::Standing:

        if (DinosaurDirectionState == EDinosaurDirectionState::Right)
        {
            SetRect(&dinoCollisionRects[0], pos_x + 23, pos_y, pos_x + 43, pos_y + 14);
            SetRect(&dinoCollisionRects[1], pos_x + 9, pos_y + 19, pos_x + 27, pos_y + 43);
            SetRect(&dinoCollisionRects[2], pos_x, pos_y + 13, pos_x + 6, pos_y + 31);
        }
        else //left
        {
            SetRect(&dinoCollisionRects[0], pos_x + width - 23, pos_y, pos_x + width - 43, pos_y + 14);
            SetRect(&dinoCollisionRects[1], pos_x + width - 9, pos_y + 19, pos_x + width - 27, pos_y + 43);
            SetRect(&dinoCollisionRects[2], pos_x + width - 0, pos_y + 13, pos_x + width - 6, pos_y + 31);
        }
        break;

    case EDinosaurBodyState::Crawling:

        if (DinosaurDirectionState == EDinosaurDirectionState::Right)
        {
            SetRect(&dinoCollisionRects[0], pos_x + 6, pos_y, pos_x + 59, pos_y + 14);
            SetRect(&dinoCollisionRects[1], pos_x + 11, pos_y + 15, pos_x + 35, pos_y + 25);
            SetRect(&dinoCollisionRects[2], pos_x, pos_y, pos_x + 5, pos_y + 9);
        }
        else //left
        {
            SetRect(&dinoCollisionRects[0], pos_x + width - 6, pos_y, pos_x + width - 59, pos_y + 14);
            SetRect(&dinoCollisionRects[1], pos_x + width - 11, pos_y + 15, pos_x + width - 35, pos_y + 25);
            SetRect(&dinoCollisionRects[2], pos_x + width - 0, pos_y, pos_x + width - 5, pos_y + 9);
        }
        break;

    default:
        break;
    }
}

//Падение под действием "гравитации" (корректируем вертикальную позицию Дино каждый кадр (опускаем вниз))
void CDinosaur::GravityFalling()
{
    if (DinosaurLevelState == EDinosaurLevelState::Teleporting)
        return;

    verticalSpeed += 7.15f;
}

//Метод для учёта платформы на стартовом уровне (для столкновений с ним)
void CDinosaur::CorrectPositionWithStartPlatform(const CStartPlatform* startPlatform)
{
    if (static_cast<int>(pos_X) + width > static_cast<int>(startPlatform->GetPos_X()) && static_cast<int>(pos_X) < static_cast<int>(startPlatform->GetPos_X()) + startPlatform->GetTopWidth()) //Проверка по Х координате для столкновения
    {
        if (onStartPlatform == false)
        {
            if (horizontalSpeed > 0) //Если движемся вправо (подходим слева), то упираемся в платформу
                pos_X = startPlatform->GetPos_X() - width;
            else if (horizontalSpeed < 0) //Если движемся влево (подходим справа), то упираемся в платформу
                pos_X = startPlatform->GetPos_X() + static_cast<float>(startPlatform->GetTopWidth());

            if (static_cast<int>(pos_Y) + height <= static_cast<int>(startPlatform->pos_Y)) //Проверка по Y координате (для возможности запрыгнуть/перепрыгнуть)
                onStartPlatform = true;
        }
    }
    else
        onStartPlatform = false;
}

//Рестарт уровня при проигрыше или начало со стартовой платформы
void CDinosaur::RestartLevel()
{
    DinosaurLevelState = EDinosaurLevelState::RestartRunLevel;
    horizontalSpeed = 0.0f;
    verticalSpeed = 0.0f;
    SetBodyState(EDinosaurBodyState::Standing);
    DinosaurMovingState = EDinosaurMovingState::Stop;
    DinosaurDirectionState = EDinosaurDirectionState::Right;
    pos_X = startPos_X;
    pos_Y = (static_cast<float>(standingPos_Y));
    collision = false;

    onStartPlatform = false;
}

//Проверяем условия для возможности телепортации Динозавра со стартовой платформы
bool CDinosaur::ReadyForStartPlatfrom(const CStartPlatform* startPlatform)
{
    bool ready = true;
    ready = ready && (static_cast<int>(pos_Y) + height == static_cast<int>(startPlatform->pos_Y));
    ready = ready && (static_cast<int>(pos_X) > static_cast<int>(startPlatform->GetPos_X() + (startPlatform->GetTopWidth() - startPlatform->GetDownWidth()) / 2));
    ready = ready && (static_cast<int>(pos_X) + width < static_cast<int>(startPlatform->GetPos_X()) + startPlatform->GetDownWidth());
    ready = ready && DinosaurBodyState == EDinosaurBodyState::Standing;

    return ready;
}

//Устанавливаем вертикальную скорость Динозавра для телепортации со стартовой платформы
void CDinosaur::SetVerticalSpeedForTeleporting()
{
    verticalSpeed = 3.0f;
}

//Проверяем, находится ли дино на земле
bool CDinosaur::CheckDinosaurOnGround()
{
    return (static_cast<int>(pos_Y) + height == onGroundLegsPos_Y);
}

//Обновляем точки для создания региона для отрисовки
void CDinosaur::UpdateRgnPoints()
{
    switch (DinosaurBodyState)
    {
    case EDinosaurBodyState::Standing:
    {
        if (DinosaurDirectionState == EDinosaurDirectionState::Right)
        {
            currentDinosaurPoints[0] = { rgnPos_X + 11, rgnPos_Y + 36 };
            currentDinosaurPoints[1] = { rgnPos_X + 1, rgnPos_Y + 27 }; 
            currentDinosaurPoints[2] = { rgnPos_X + 1, rgnPos_Y + 16 }; 
            currentDinosaurPoints[3] = { rgnPos_X + 3, rgnPos_Y + 13 }; 
            currentDinosaurPoints[4] = { rgnPos_X + 7, rgnPos_Y + 23 }; 
            currentDinosaurPoints[5] = { rgnPos_X + 11, rgnPos_Y + 23 };
            currentDinosaurPoints[6] = { rgnPos_X + 20, rgnPos_Y + 15 };
            currentDinosaurPoints[7] = { rgnPos_X + 23, rgnPos_Y + 15 };
            currentDinosaurPoints[8] = { rgnPos_X + 23, rgnPos_Y + 1 }; 
            currentDinosaurPoints[9] = { rgnPos_X + 25, rgnPos_Y + 0 }; 
            currentDinosaurPoints[10] = { rgnPos_X + 41, rgnPos_Y + 0 };
            currentDinosaurPoints[11] = { rgnPos_X + 43, rgnPos_Y + 1 };
            currentDinosaurPoints[12] = { rgnPos_X + 43, rgnPos_Y + 9 };
            currentDinosaurPoints[13] = { rgnPos_X + 33, rgnPos_Y + 9 };
            currentDinosaurPoints[14] = { rgnPos_X + 33, rgnPos_Y + 12 };
            currentDinosaurPoints[15] = { rgnPos_X + 40, rgnPos_Y + 12 };
            currentDinosaurPoints[16] = { rgnPos_X + 40, rgnPos_Y + 14 };
            currentDinosaurPoints[17] = { rgnPos_X + 30, rgnPos_Y + 14 };
            currentDinosaurPoints[18] = { rgnPos_X + 30, rgnPos_Y + 20 };
            currentDinosaurPoints[19] = { rgnPos_X + 35, rgnPos_Y + 20 };
            currentDinosaurPoints[20] = { rgnPos_X + 35, rgnPos_Y + 23 };
            currentDinosaurPoints[21] = { rgnPos_X + 34, rgnPos_Y + 23 };
            currentDinosaurPoints[22] = { rgnPos_X + 34, rgnPos_Y + 21 };
            currentDinosaurPoints[23] = { rgnPos_X + 30, rgnPos_Y + 21 };
            currentDinosaurPoints[24] = { rgnPos_X + 30, rgnPos_Y + 30 };
            currentDinosaurPoints[25] = { rgnPos_X + 24, rgnPos_Y + 36 };

            currentDinosaurPoints[26] = { rgnPos_X + 28, rgnPos_Y + 36 };
            currentDinosaurPoints[27] = { rgnPos_X + 28, rgnPos_Y + 43 };
            currentDinosaurPoints[28] = { rgnPos_X + 11, rgnPos_Y + 43 };
        }
        else //left
        {
            currentDinosaurPoints[0] = { rgnPos_X + width - 11, rgnPos_Y + 36 };
            currentDinosaurPoints[1] = { rgnPos_X + width - 1, rgnPos_Y + 27 };
            currentDinosaurPoints[2] = { rgnPos_X + width - 1, rgnPos_Y + 16 };
            currentDinosaurPoints[3] = { rgnPos_X + width - 3, rgnPos_Y + 13 };
            currentDinosaurPoints[4] = { rgnPos_X + width - 7, rgnPos_Y + 23 };
            currentDinosaurPoints[5] = { rgnPos_X + width - 11, rgnPos_Y + 23 };
            currentDinosaurPoints[6] = { rgnPos_X + width - 20, rgnPos_Y + 15 };
            currentDinosaurPoints[7] = { rgnPos_X + width - 23, rgnPos_Y + 15 };
            currentDinosaurPoints[8] = { rgnPos_X + width - 23, rgnPos_Y + 1 };
            currentDinosaurPoints[9] = { rgnPos_X + width - 25, rgnPos_Y + 0 };
            currentDinosaurPoints[10] = { rgnPos_X + width - 41, rgnPos_Y + 0 };
            currentDinosaurPoints[11] = { rgnPos_X + width - 43, rgnPos_Y + 1 };
            currentDinosaurPoints[12] = { rgnPos_X + width - 43, rgnPos_Y + 9 };
            currentDinosaurPoints[13] = { rgnPos_X + width - 33, rgnPos_Y + 9 };
            currentDinosaurPoints[14] = { rgnPos_X + width - 33, rgnPos_Y + 12 };
            currentDinosaurPoints[15] = { rgnPos_X + width - 40, rgnPos_Y + 12 };
            currentDinosaurPoints[16] = { rgnPos_X + width - 40, rgnPos_Y + 14 };
            currentDinosaurPoints[17] = { rgnPos_X + width - 30, rgnPos_Y + 14 };
            currentDinosaurPoints[18] = { rgnPos_X + width - 30, rgnPos_Y + 20 };
            currentDinosaurPoints[19] = { rgnPos_X + width - 35, rgnPos_Y + 20 };
            currentDinosaurPoints[20] = { rgnPos_X + width - 35, rgnPos_Y + 23 };
            currentDinosaurPoints[21] = { rgnPos_X + width - 34, rgnPos_Y + 23 };
            currentDinosaurPoints[22] = { rgnPos_X + width - 34, rgnPos_Y + 21 };
            currentDinosaurPoints[23] = { rgnPos_X + width - 30, rgnPos_Y + 21 };
            currentDinosaurPoints[24] = { rgnPos_X + width - 30, rgnPos_Y + 30 };
            currentDinosaurPoints[25] = { rgnPos_X + width - 24, rgnPos_Y + 36 };

            currentDinosaurPoints[26] = { rgnPos_X + width - 28, rgnPos_Y + 36 };
            currentDinosaurPoints[27] = { rgnPos_X + width - 28, rgnPos_Y + 43 };
            currentDinosaurPoints[28] = { rgnPos_X + width - 11, rgnPos_Y + 43 };
        }
    }
    break;

    case EDinosaurBodyState::Crawling:
    {
        if (DinosaurDirectionState == EDinosaurDirectionState::Right)
        {
            currentDinosaurPoints[0] = { rgnPos_X + 11, rgnPos_Y + 17 };
            currentDinosaurPoints[1] = { rgnPos_X + 1, rgnPos_Y + 5 };
            currentDinosaurPoints[2] = { rgnPos_X + 1, rgnPos_Y + 0 };
            currentDinosaurPoints[3] = { rgnPos_X + 5, rgnPos_Y + 3 };
            currentDinosaurPoints[4] = { rgnPos_X + 13, rgnPos_Y + 3 };
            currentDinosaurPoints[5] = { rgnPos_X + 16, rgnPos_Y + 1 };
            currentDinosaurPoints[6] = { rgnPos_X + 33, rgnPos_Y + 1 };
            currentDinosaurPoints[7] = { rgnPos_X + 36, rgnPos_Y + 3 };
            currentDinosaurPoints[8] = { rgnPos_X + 39, rgnPos_Y + 3 };
            currentDinosaurPoints[9] = { rgnPos_X + 41, rgnPos_Y + 0 };
            currentDinosaurPoints[10] = { rgnPos_X + 57, rgnPos_Y + 0 };
            currentDinosaurPoints[11] = { rgnPos_X + 59, rgnPos_Y + 1 };
            currentDinosaurPoints[12] = { rgnPos_X + 59, rgnPos_Y + 9 };
            currentDinosaurPoints[13] = { rgnPos_X + 49, rgnPos_Y + 9 };
            currentDinosaurPoints[14] = { rgnPos_X + 49, rgnPos_Y + 12 };
            currentDinosaurPoints[15] = { rgnPos_X + 56, rgnPos_Y + 12 };
            currentDinosaurPoints[16] = { rgnPos_X + 56, rgnPos_Y + 14 };
            currentDinosaurPoints[17] = { rgnPos_X + 42, rgnPos_Y + 14 };
            currentDinosaurPoints[18] = { rgnPos_X + 39, rgnPos_Y + 13 };
            currentDinosaurPoints[19] = { rgnPos_X + 36, rgnPos_Y + 13 };
            currentDinosaurPoints[20] = { rgnPos_X + 33, rgnPos_Y + 16 };
            currentDinosaurPoints[21] = { rgnPos_X + 33, rgnPos_Y + 20 };
            currentDinosaurPoints[22] = { rgnPos_X + 35, rgnPos_Y + 20 };
            currentDinosaurPoints[23] = { rgnPos_X + 35, rgnPos_Y + 21 };
            currentDinosaurPoints[24] = { rgnPos_X + 32, rgnPos_Y + 21 };
            currentDinosaurPoints[25] = { rgnPos_X + 32, rgnPos_Y + 17 };

            currentDinosaurPoints[26] = { rgnPos_X + 28, rgnPos_Y + 17 };
            currentDinosaurPoints[27] = { rgnPos_X + 28, rgnPos_Y + 25 };
            currentDinosaurPoints[28] = { rgnPos_X + 11, rgnPos_Y + 25 };
        }
        else //left
        {
            currentDinosaurPoints[0] = { rgnPos_X + width - 11, rgnPos_Y + 17 };
            currentDinosaurPoints[1] = { rgnPos_X + width - 1, rgnPos_Y + 5 };
            currentDinosaurPoints[2] = { rgnPos_X + width - 1, rgnPos_Y + 0 };
            currentDinosaurPoints[3] = { rgnPos_X + width - 5, rgnPos_Y + 3 };
            currentDinosaurPoints[4] = { rgnPos_X + width - 13, rgnPos_Y + 3 };
            currentDinosaurPoints[5] = { rgnPos_X + width - 16, rgnPos_Y + 1 };
            currentDinosaurPoints[6] = { rgnPos_X + width - 33, rgnPos_Y + 1 };
            currentDinosaurPoints[7] = { rgnPos_X + width - 36, rgnPos_Y + 3 };
            currentDinosaurPoints[8] = { rgnPos_X + width - 39, rgnPos_Y + 3 };
            currentDinosaurPoints[9] = { rgnPos_X + width - 41, rgnPos_Y + 0 };
            currentDinosaurPoints[10] = { rgnPos_X + width - 57, rgnPos_Y + 0 };
            currentDinosaurPoints[11] = { rgnPos_X + width - 59, rgnPos_Y + 1 };
            currentDinosaurPoints[12] = { rgnPos_X + width - 59, rgnPos_Y + 9 };
            currentDinosaurPoints[13] = { rgnPos_X + width - 49, rgnPos_Y + 9 };
            currentDinosaurPoints[14] = { rgnPos_X + width - 49, rgnPos_Y + 12 };
            currentDinosaurPoints[15] = { rgnPos_X + width - 56, rgnPos_Y + 12 };
            currentDinosaurPoints[16] = { rgnPos_X + width - 56, rgnPos_Y + 14 };
            currentDinosaurPoints[17] = { rgnPos_X + width - 42, rgnPos_Y + 14 };
            currentDinosaurPoints[18] = { rgnPos_X + width - 39, rgnPos_Y + 13 };
            currentDinosaurPoints[19] = { rgnPos_X + width - 36, rgnPos_Y + 13 };
            currentDinosaurPoints[20] = { rgnPos_X + width - 33, rgnPos_Y + 16 };
            currentDinosaurPoints[21] = { rgnPos_X + width - 33, rgnPos_Y + 20 };
            currentDinosaurPoints[22] = { rgnPos_X + width - 35, rgnPos_Y + 20 };
            currentDinosaurPoints[23] = { rgnPos_X + width - 35, rgnPos_Y + 21 };
            currentDinosaurPoints[24] = { rgnPos_X + width - 32, rgnPos_Y + 21 };
            currentDinosaurPoints[25] = { rgnPos_X + width - 32, rgnPos_Y + 17 };

            currentDinosaurPoints[26] = { rgnPos_X + width - 28, rgnPos_Y + 17 };
            currentDinosaurPoints[27] = { rgnPos_X + width - 28, rgnPos_Y + 25 };
            currentDinosaurPoints[28] = { rgnPos_X + width - 11, rgnPos_Y + 25 };
        }
    }
    break;

    default:
        break;
    }
}

//Анимация ног при движении вправо
void CDinosaur::MoveLegsRight(HDC hdc)
{
    if (static_cast<int>(CConfig::slowCurrentFrameValue) % 2 == 0)
        DrawRightFirstStep(hdc);
    else
        DrawRightSecondStep(hdc);
}

//Анимация ног при движении вправо
void CDinosaur::MoveLegsLeft(HDC hdc)
{
    if (static_cast<int>(CConfig::slowCurrentFrameValue) % 2 == 0)
        DrawLeftFirstStep(hdc);
    else
        DrawLeftSecondStep(hdc);
}

//Очистка фона для перерисовки
void CDinosaur::ClearRightLegsBackground(HDC hdc)
{
    //Очищаем фон ног
    CConfig::backgroundColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    if (DinosaurBodyState == EDinosaurBodyState::Crawling)
        pos_y -= (standingHeight - crawlingHeight);

    //Левая нога
    Rectangle(hdc, pos_x + 12, pos_y + 36, pos_x + 22, pos_y + 44);

    //Правая нога
    Rectangle(hdc, pos_x + 22, pos_y + 36, pos_x + 28, pos_y + 44);
}

//Очистка фона для перерисовки влево
void CDinosaur::ClearLeftLegsBackground(HDC hdc)
{
    //Очищаем фон ног
    CConfig::backgroundColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    if (DinosaurBodyState == EDinosaurBodyState::Crawling)
        pos_y -= (standingHeight - crawlingHeight);

    //Левая нога
    Rectangle(hdc, pos_x + (width - 12), pos_y + (36), pos_x + (width - 18), pos_y + (44));

    //Правая нога
    Rectangle(hdc, pos_x + (width - 22), pos_y + (36), pos_x + (width - 28), pos_y + (44));
}

//Отрисовка ног стоя
void CDinosaur::DrawRightStandingLegs(HDC hdc)
{
    //Рисуем ноги
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    if (DinosaurBodyState == EDinosaurBodyState::Crawling)
        pos_y -= (standingHeight - crawlingHeight);

    //Левая нога
    Rectangle(hdc, pos_x + 12, pos_y + 36, pos_x + 15, pos_y + 44);
    Rectangle(hdc, pos_x + 15, pos_y + 42, pos_x + 18, pos_y + 44);

    //Правая нога
    Rectangle(hdc, pos_x + 22, pos_y + 36, pos_x + 25, pos_y + 44);
    Rectangle(hdc, pos_x + 25, pos_y + 42, pos_x + 28, pos_y + 44);
}

//Отрисовка ног стоя влево 
void CDinosaur::DrawLeftStandingLegs(HDC hdc)
{
    //Рисуем ноги
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    if (DinosaurBodyState == EDinosaurBodyState::Crawling)
        pos_y -= (standingHeight - crawlingHeight);

    //Левая нога
    Rectangle(hdc, pos_x + (width - 12), pos_y + (36), pos_x + (width - 15), pos_y + (44));
    Rectangle(hdc, pos_x + (width - 15), pos_y + (42), pos_x + (width - 18), pos_y + (44));

    //Правая нога
    Rectangle(hdc, pos_x + (width - 22), pos_y + (36), pos_x + (width - 25), pos_y + (44));
    Rectangle(hdc, pos_x + (width - 25), pos_y + (42), pos_x + (width - 28), pos_y + (44));
}

//Отрисовка ног при первом шаге
void CDinosaur::DrawRightFirstStep(HDC hdc)
{
    ClearRightLegsBackground(hdc);

    //Рисуем ноги
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    if (DinosaurBodyState == EDinosaurBodyState::Crawling)
        pos_y -= (standingHeight - crawlingHeight);

    //Левая нога обычно
    Rectangle(hdc, pos_x + 12, pos_y + 36, pos_x + 15, pos_y + 44);
    Rectangle(hdc, pos_x + 15, pos_y + 42, pos_x + 18, pos_y + 44);

    //Правая нога поднятая
    Rectangle(hdc, pos_x + 22, pos_y + (36 - 4), pos_x + 25, pos_y + (44 - 4));
    Rectangle(hdc, pos_x + 25, pos_y + (42 - 4), pos_x + 28, pos_y + (44 - 4));
}

//Отрисовка ног при первом шаге влево
void CDinosaur::DrawLeftFirstStep(HDC hdc)
{
    ClearLeftLegsBackground(hdc);

    //Рисуем ноги
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    if (DinosaurBodyState == EDinosaurBodyState::Crawling)
        pos_y -= (standingHeight - crawlingHeight);

    //Левая нога обычно
    Rectangle(hdc, pos_x + (width - 12), pos_y + (36), pos_x + (width - 15), pos_y + (44));
    Rectangle(hdc, pos_x + (width - 15), pos_y + (42), pos_x + (width - 18), pos_y + (44));

    //Правая нога поднятая
    Rectangle(hdc, pos_x + (width - 22), pos_y + (36 - 4), pos_x + (width - 25), pos_y + (44 - 4));
    Rectangle(hdc, pos_x + (width - 25), pos_y + (42 - 4), pos_x + (width - 28), pos_y + (44 - 4));
}

//Отрисовка ног при втором шаге
void CDinosaur::DrawRightSecondStep(HDC hdc)
{
    ClearRightLegsBackground(hdc);

    //Рисуем ноги
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    if (DinosaurBodyState == EDinosaurBodyState::Crawling)
        pos_y -= (standingHeight - crawlingHeight);

    //Левая нога поднятая
    Rectangle(hdc, pos_x + 12, pos_y + (36 - 4), pos_x + 15, pos_y + (44 - 4));
    Rectangle(hdc, pos_x + 15, pos_y + (42 - 4), pos_x + 18, pos_y + (44 - 4));

    //Правая нога обычно
    Rectangle(hdc, pos_x + 22, pos_y + 36, pos_x + 25, pos_y + 44);
    Rectangle(hdc, pos_x + 25, pos_y + 42, pos_x + 28, pos_y + 44);
}

//Отрисовка ног при втором шаге влево
void CDinosaur::DrawLeftSecondStep(HDC hdc)
{
    ClearLeftLegsBackground(hdc);

    //Рисуем ноги
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    if (DinosaurBodyState == EDinosaurBodyState::Crawling)
        pos_y -= (standingHeight - crawlingHeight);

    //Левая нога поднятая
    Rectangle(hdc, pos_x + (width - 12), pos_y + (36 - 4), pos_x + (width - 15), pos_y + (44 - 4));
    Rectangle(hdc, pos_x + (width - 15), pos_y + (42 - 4), pos_x + (width - 18), pos_y + (44 - 4));

    //Правая нога обычно
    Rectangle(hdc, pos_x + (width - 22), pos_y + (36), pos_x + (width - 25), pos_y + (44));
    Rectangle(hdc, pos_x + (width - 25), pos_y + (42), pos_x + (width - 28), pos_y + (44));
}

//Отрисовка зрачка при стоклновении
void CDinosaur::DrawRightEye(HDC hdc)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    if (DinosaurBodyState == EDinosaurBodyState::Crawling)
        pos_x += (crawlingWidth - standingWidth);

    //Зрачок при столкновении
    Rectangle(hdc, pos_x + 28, pos_y + 3, pos_x + 30, pos_y + 5);
}

//Отрисовка зрачка при стоклновении влево
void CDinosaur::DrawLeftEye(HDC hdc)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    if (DinosaurBodyState == EDinosaurBodyState::Crawling)
        pos_x -= (crawlingWidth - standingWidth);

    //Зрачок при столкновении
    Rectangle(hdc, pos_x + (width - 28), pos_y + 3, pos_x + (width - 30), pos_y + 5);
}

//Отрисовка тела в обычном состоянии
void CDinosaur::DrawRightStanding(HDC hdc)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    Polygon(hdc, currentDinosaurPoints, dinosaurBodyPointsAmount);

    //Фоновые пропуски
    CConfig::backgroundColor.SelectColor(hdc);

    //Глаз
    Rectangle(hdc, rgnPos_X + 27, rgnPos_Y + 2, rgnPos_X + 31, rgnPos_Y + 6);
}

//Отрисовка тела в обычном состоянии влево
void CDinosaur::DrawLeftStanding(HDC hdc)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    Polygon(hdc, currentDinosaurPoints, dinosaurBodyPointsAmount);

    CConfig::backgroundColor.SelectColor(hdc);

    //Глаз
    Rectangle(hdc, rgnPos_X + (width - 27), rgnPos_Y + (2), rgnPos_X + (width - 31), rgnPos_Y + (6));
}

//Отрисовка тела в присяде
void CDinosaur::DrawRightCrawling(HDC hdc)
{
    CConfig::mainBrightColor.SelectColor(hdc);
                                  
    Polygon(hdc, currentDinosaurPoints, dinosaurBodyPointsAmount);

    //Фоновые пропуски
    CConfig::backgroundColor.SelectColor(hdc);

    //Глаз
    Rectangle(hdc, rgnPos_X + 43, rgnPos_Y + 2, rgnPos_X + 47, rgnPos_Y + 6);
}

//Отрисовка тела в присяде влево
void CDinosaur::DrawLeftCrawling(HDC hdc)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    Polygon(hdc, currentDinosaurPoints, dinosaurBodyPointsAmount);

    //Фоновые пропуски
    CConfig::backgroundColor.SelectColor(hdc);

    //Глаз
    Rectangle(hdc, rgnPos_X + width - 43, rgnPos_Y + 2, rgnPos_X + width - 47, rgnPos_Y + 6);
}