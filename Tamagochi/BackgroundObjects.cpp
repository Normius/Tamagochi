#include "BackgroundObjects.h"

// ----------------------------- ����� ������ ��� ------------------------------------

float CBackgroundObjects::speed = 5.0f;
// -----------------------------------------------------------------------------------

// ----------------------------- ����� ������� ������������ ------------------------------------

unsigned int CCollisionObjects::CollisionObjectsActiveCount = 0;
// -----------------------------------------------------------------------------------

// ----------------------------- ����� ����� (���������) -----------------------------
//�����������
CBird::CBird()
    :pos_X(startPos_X), pos_Y(startPos_Y), height(upWingHeight), upWing(true), restDistance(0.0f), active(false), birdRect{}, prevBirdRect{}
{
}

//��������� ����
void CBird::DrawBird(HDC hdc)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    //����
    Rectangle(hdc, pos_x + 13 * CConfig::SizeScale, pos_y + 13 * CConfig::SizeScale, pos_x + 46 * CConfig::SizeScale, pos_y + 23 * CConfig::SizeScale);

    //������
    Rectangle(hdc, pos_x, pos_y + 7 * CConfig::SizeScale, pos_x + 13 * CConfig::SizeScale, pos_y + 16 * CConfig::SizeScale);

    //������� ��������
    CConfig::backgroundColor.SelectColor(hdc);

    //������
    Rectangle(hdc, pos_x, pos_y + 7 * CConfig::SizeScale, pos_x + 8 * CConfig::SizeScale, pos_y + 8 * CConfig::SizeScale);
    Rectangle(hdc, pos_x, pos_y + 8 * CConfig::SizeScale, pos_x + 6 * CConfig::SizeScale, pos_y + 10 * CConfig::SizeScale);
    Rectangle(hdc, pos_x, pos_y + 10 * CConfig::SizeScale, pos_x + 4 * CConfig::SizeScale, pos_y + 12 * CConfig::SizeScale);
    Rectangle(hdc, pos_x, pos_y + 12 * CConfig::SizeScale, pos_x + 2 * CConfig::SizeScale, pos_y + 14 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 11 * CConfig::SizeScale, pos_y + 7 * CConfig::SizeScale, pos_x + 13 * CConfig::SizeScale, pos_y + 10 * CConfig::SizeScale);

    //����
    Rectangle(hdc, pos_x + 13 * CConfig::SizeScale, pos_y + 18 * CConfig::SizeScale, pos_x + 15 * CConfig::SizeScale, pos_y + 20 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 13 * CConfig::SizeScale, pos_y + 20 * CConfig::SizeScale, pos_x + 17 * CConfig::SizeScale, pos_y + 22 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 13 * CConfig::SizeScale, pos_y + 22 * CConfig::SizeScale, pos_x + 19 * CConfig::SizeScale, pos_y + 24 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 31 * CConfig::SizeScale, pos_y + 13 * CConfig::SizeScale, pos_x + 46 * CConfig::SizeScale, pos_y + 15 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 33 * CConfig::SizeScale, pos_y + 15 * CConfig::SizeScale, pos_x + 46 * CConfig::SizeScale, pos_y + 17 * CConfig::SizeScale);

    //�����
    Rectangle(hdc, pos_x + 39 * CConfig::SizeScale, pos_y + 19 * CConfig::SizeScale, pos_x + 46 * CConfig::SizeScale, pos_y + 21 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 44 * CConfig::SizeScale, pos_y + 21 * CConfig::SizeScale, pos_x + 46 * CConfig::SizeScale, pos_y + 23 * CConfig::SizeScale);

    //����
    Rectangle(hdc, pos_x + 7 * CConfig::SizeScale, pos_y + 11 * CConfig::SizeScale, pos_x + 9 * CConfig::SizeScale, pos_y + 12 * CConfig::SizeScale);
}

//��������� �������� �����
void CBird::DrawUpWing(HDC hdc)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    //�����
    Rectangle(hdc, pos_x + 15 * CConfig::SizeScale, pos_y, pos_x + 17 * CConfig::SizeScale, pos_y + 4 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 17 * CConfig::SizeScale, pos_y + 1 * CConfig::SizeScale, pos_x + 19 * CConfig::SizeScale, pos_y + 13 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 19 * CConfig::SizeScale, pos_y + 3 * CConfig::SizeScale, pos_x + 21 * CConfig::SizeScale, pos_y + 13 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 21 * CConfig::SizeScale, pos_y + 5 * CConfig::SizeScale, pos_x + 23 * CConfig::SizeScale, pos_y + 13 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 23 * CConfig::SizeScale, pos_y + 7 * CConfig::SizeScale, pos_x + 25 * CConfig::SizeScale, pos_y + 13 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 25 * CConfig::SizeScale, pos_y + 9 * CConfig::SizeScale, pos_x + 27 * CConfig::SizeScale, pos_y + 13 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 27 * CConfig::SizeScale, pos_y + 11 * CConfig::SizeScale, pos_x + 29 * CConfig::SizeScale, pos_y + 13 * CConfig::SizeScale);
}

//��������� ������� �����
void CBird::DrawDownWing(HDC hdc)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    //�����
    Rectangle(hdc, pos_x + 17 * CConfig::SizeScale, pos_y + 22 * CConfig::SizeScale, pos_x + 19 * CConfig::SizeScale, pos_y + 34 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 19 * CConfig::SizeScale, pos_y + 23 * CConfig::SizeScale, pos_x + 21 * CConfig::SizeScale, pos_y + 31 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 21 * CConfig::SizeScale, pos_y + 23 * CConfig::SizeScale, pos_x + 23 * CConfig::SizeScale, pos_y + 27 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 23 * CConfig::SizeScale, pos_y + 23 * CConfig::SizeScale, pos_x + 25 * CConfig::SizeScale, pos_y + 25 * CConfig::SizeScale);
}

//��������� ����� ���������
void CBird::Draw(HDC hdc, RECT& paintArea)
{
    RECT intersectionRect; //����� ��� �-��� �������� ����������� ���������������, � ���� ����������� ������� ����������� ��� 0

    //TO DO: �������� ������� �������� ������� ���� �������, � �� �������� TRUE � InvalidateRect(CConfig::Hwnd, &prevDinoRect, TRUE);

    if (!IntersectRect(&intersectionRect, &paintArea, &birdRect))
    {
        return;
    }

    DrawBird(hdc);
    MoveWings(hdc);
}

//����������� ��������� � ����� �����������
void CBird::Redraw()
{
    if (active == false)
        return;

    prevBirdRect = birdRect;

    birdRect.left = static_cast<int>(pos_X);
    birdRect.top = static_cast<int>(pos_Y);
    birdRect.right = birdRect.left + width * CConfig::SizeScale;
    birdRect.bottom = birdRect.top + (downWingHeight + 7) * CConfig::SizeScale;

    InvalidateRect(CConfig::Hwnd, &prevBirdRect, TRUE);
    InvalidateRect(CConfig::Hwnd, &birdRect, TRUE);
}

//�������� ������������
//TO DO: ���������� ��������� ������������ (��������� ������ �� ��������� ����������)
bool CBird::CheckHit(float dinoPos_x, float dinopos_y, int dinoHeight, int dinoWidth)
{
    if (active == false)
        return false;

    float dinoUpPos = dinopos_y;
    float dinoDownPos = dinopos_y + dinoHeight;
    float dinoLeftPos = dinoPos_x;
    float dinoRightPos = dinoPos_x + dinoWidth;

    float birdUpPos = pos_Y;
    float birdDownPos = pos_Y + height;
    float birdLeftPos = pos_X;
    float birdRightPos = pos_X + width;

    if (dinoRightPos >= birdLeftPos && dinoLeftPos <= birdRightPos)
        if (dinoDownPos >= birdUpPos && dinoUpPos <= birdDownPos)
        {
            //Beep(100, 10);
            return true;
        }
    return false;
}

//�������� ������� �� ������ (��������� �� ������)
bool CBird::CheckActive()
{
    if (active == true)
        return true;
    else
        return false;
}

//�������� �������
void CBird::MoveWings(HDC hdc)
{
    if (static_cast<int>(CConfig::slowCurrentFrameValue) % 2 == 0) //TO DO: ��������� �������� �������� ����� � ������ �����. ��� ������� �������� ������ ��� 10 ���
    {
        upWing = true;
        height = upWingHeight;
        DrawUpWing(hdc);
    }
    else
    {
        /*upWing = false;
        height = downWingHeight;
        DrawDownWing(hdc);*/
        upWing = true;
        height = upWingHeight;
        DrawUpWing(hdc);
    }
}

//������ ������ �������� � �������� � �������� ����������
void CBird::Activate()
{
    if (CCollisionObjects::CollisionObjectsActiveCount >= CCollisionObjects::maxCollisionObjectsActive)
        return;

    active = true;
    CCollisionObjects::CollisionObjectsActiveCount++;

    int y = 100 + 10 * CConfig::GetRandom(0, 5); //���������� �������� �� 100 �� 150: (100, 110) - ��������� ����, (120, 130) - �������� ��� ����������� ������������, (140-150) - ������ �������������

    pos_X = startPos_X;
    pos_Y = static_cast<float>(y);
}

//�������� ��������� �������
void CBird::TestActivate(float pos_x, float pos_y)
{
    if (CCollisionObjects::CollisionObjectsActiveCount >= CCollisionObjects::maxCollisionObjectsActive)
        return;

    active = true;
    CCollisionObjects::CollisionObjectsActiveCount++;

    pos_X = pos_x;
    pos_Y = pos_y;
}

//�������� ������� �� ��������
void CBird::Move(float maxSpeed)
{
    if (active == false)
        return;

    if (CBackgroundObjects::speed == 0.0f)
        return;

    ////�������� �� ��������� ����� 
    //restDistance += CBackgroundObjects::speed; //�� �������� ���������� ���������, � �����������, ���� �� ����� �� �����

    //while (restDistance > 0)
    //{
    //    //����� �� ����������� ��� (1 pxl)
    //    pos_X -= CConfig::minShift;

    //    restDistance -= CConfig::minShift;
    //}

    float nextStep = CBackgroundObjects::speed / maxSpeed * CConfig::minShift;

    if (static_cast<int>(pos_X) + CBackgroundObjects::speed + width * CConfig::SizeScale <= CConfig::leftBorder)
    {
        active = false; //���� ������ ������� �� ������� ������, ������������ ���
        CCollisionObjects::CollisionObjectsActiveCount--;
    }

    pos_X -= nextStep;
}
// -----------------------------------------------------------------------------------


// ----------------------------- ����� ������� (�����������) -------------------------
//�����������
CCactus::CCactus()
    :pos_X(startPos_X), pos_Y(startPos_Y), restDistance(0.0f), active(false), cactusRect{}, prevCactusRect{}
{

}

//���������
void CCactus::Draw(HDC hdc, RECT& paintArea)
{
    RECT intersectionRect; //����� ��� �-��� �������� ����������� ���������������, � ���� ����������� ������� ����������� ��� 0

    //TO DO: �������� ������� �������� ������� ���� �������, � �� �������� TRUE � InvalidateRect(CConfig::Hwnd, &prevDinoRect, TRUE);

    if (!IntersectRect(&intersectionRect, &paintArea, &cactusRect))
    {
        return;
    }

    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    //����� �������
    Rectangle(hdc, pos_x + 8 * CConfig::SizeScale, pos_y + 2 * CConfig::SizeScale, pos_x + 14 * CConfig::SizeScale, pos_y + 48 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 10 * CConfig::SizeScale, pos_y, pos_x + 12 * CConfig::SizeScale, pos_y + 2 * CConfig::SizeScale);

    //����� ����� �������
    Rectangle(hdc, pos_x + 3 * CConfig::SizeScale, pos_y + 29 * CConfig::SizeScale, pos_x + 8 * CConfig::SizeScale, pos_y + 31 * CConfig::SizeScale);
    Rectangle(hdc, pos_x, pos_y + 15 * CConfig::SizeScale, pos_x + 3 * CConfig::SizeScale, pos_y + 29 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 1 * CConfig::SizeScale, pos_y + 13 * CConfig::SizeScale, pos_x + 2 * CConfig::SizeScale, pos_y + 15 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 1 * CConfig::SizeScale, pos_y + 29 * CConfig::SizeScale, pos_x + 4 * CConfig::SizeScale, pos_y + 30 * CConfig::SizeScale);

    //������ ����� �������
    Rectangle(hdc, pos_x + 14 * CConfig::SizeScale, pos_y + 27 * CConfig::SizeScale, pos_x + 19 * CConfig::SizeScale, pos_y + 29 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 19 * CConfig::SizeScale, pos_y + 13 * CConfig::SizeScale, pos_x + 22 * CConfig::SizeScale, pos_y + 27 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 20 * CConfig::SizeScale, pos_y + 11 * CConfig::SizeScale, pos_x + 21 * CConfig::SizeScale, pos_y + 13 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 19 * CConfig::SizeScale, pos_y + 27 * CConfig::SizeScale, pos_x + 21 * CConfig::SizeScale, pos_y + 28 * CConfig::SizeScale);

    //����� ����� ������� ������� 2
    //Rectangle(hdc, pos_x + 3 * CConfig::SizeScale, pos_y + 29 - 6 * CConfig::SizeScale, pos_x + 8 * CConfig::SizeScale, pos_y + 31 - 6 * CConfig::SizeScale);
    //Rectangle(hdc, pos_x, pos_y + 15 - 6 * CConfig::SizeScale, pos_x + 3 * CConfig::SizeScale, pos_y + 29 - 6 * CConfig::SizeScale);
    //Rectangle(hdc, pos_x + 1 * CConfig::SizeScale, pos_y + 13 - 6 * CConfig::SizeScale, pos_x + 2 * CConfig::SizeScale, pos_y + 15 - 6 * CConfig::SizeScale);
    //Rectangle(hdc, pos_x + 1 * CConfig::SizeScale, pos_y + 29 - 6 * CConfig::SizeScale, pos_x + 4 * CConfig::SizeScale, pos_y + 30 - 6 * CConfig::SizeScale);

    //������ ����� ������� ������� 2
    //Rectangle(hdc, pos_x + 14 * CConfig::SizeScale, pos_y + 27 * CConfig::SizeScale, pos_x + 19 * CConfig::SizeScale, pos_y + 29 * CConfig::SizeScale);
    //Rectangle(hdc, pos_x + 19 * CConfig::SizeScale, pos_y + 13 * CConfig::SizeScale, pos_x + 22 * CConfig::SizeScale, pos_y + 27 * CConfig::SizeScale);
    //Rectangle(hdc, pos_x + 20 * CConfig::SizeScale, pos_y + 11 * CConfig::SizeScale, pos_x + 21 * CConfig::SizeScale, pos_y + 13 * CConfig::SizeScale);
    //Rectangle(hdc, pos_x + 19 * CConfig::SizeScale, pos_y + 27 * CConfig::SizeScale, pos_x + 21 * CConfig::SizeScale, pos_y + 28 * CConfig::SizeScale);

    //����� ����� ������� ������� 2
    //Rectangle(hdc, pos_x + 3 * CConfig::SizeScale, pos_y + 29 - 6 * CConfig::SizeScale, pos_x + 8 * CConfig::SizeScale, pos_y + 31 - 6 * CConfig::SizeScale);
    //Rectangle(hdc, pos_x, pos_y + 15 - 6 * CConfig::SizeScale, pos_x + 3 * CConfig::SizeScale, pos_y + 29 - 6 * CConfig::SizeScale);
    //Rectangle(hdc, pos_x + 1 * CConfig::SizeScale, pos_y + 13 - 6 * CConfig::SizeScale, pos_x + 2 * CConfig::SizeScale, pos_y + 15 - 6 * CConfig::SizeScale);
    //Rectangle(hdc, pos_x + 1 * CConfig::SizeScale, pos_y + 29 - 6 * CConfig::SizeScale, pos_x + 4 * CConfig::SizeScale, pos_y + 30 - 6 * CConfig::SizeScale);

    //������ ����� ������� ������� 2
    //Rectangle(hdc, pos_x + 14 * CConfig::SizeScale, pos_y + 27 * CConfig::SizeScale, pos_x + 19 * CConfig::SizeScale, pos_y + 29 * CConfig::SizeScale);
    //Rectangle(hdc, pos_x + 19 * CConfig::SizeScale, pos_y + 13 * CConfig::SizeScale, pos_x + 22 * CConfig::SizeScale, pos_y + 27 * CConfig::SizeScale);
    //Rectangle(hdc, pos_x + 20 * CConfig::SizeScale, pos_y + 11 * CConfig::SizeScale, pos_x + 21 * CConfig::SizeScale, pos_y + 13 * CConfig::SizeScale);
    //Rectangle(hdc, pos_x + 19 * CConfig::SizeScale, pos_y + 27 * CConfig::SizeScale, pos_x + 21 * CConfig::SizeScale, pos_y + 28 * CConfig::SizeScale);
}

//����������� ��������� � ����� �����������
void CCactus::Redraw()
{
    if (active == false)
        return;

    prevCactusRect = cactusRect;

    cactusRect.left = static_cast<int>(pos_X);
    cactusRect.top = static_cast<int>(pos_Y);
    cactusRect.right = cactusRect.left + width * CConfig::SizeScale;
    cactusRect.bottom = cactusRect.top + (height) * CConfig::SizeScale;

    InvalidateRect(CConfig::Hwnd, &prevCactusRect, TRUE);
    InvalidateRect(CConfig::Hwnd, &cactusRect, TRUE);
}

//�������� ������������
bool CCactus::CheckHit(float dinoPos_x, float dinopos_y, int dinoHeight, int dinoWidth)
{
    if (active == false)
        return false;

    if (dinoPos_x + dinoWidth >= pos_X && dinoPos_x <= pos_X + width)
        if (dinopos_y + dinoHeight >= pos_Y && dinopos_y <= pos_Y + height)
        {
            //Beep(100, 10);
            return true;
        }
    return false;
}

//�������� ������� �� ������ (��������� �� ������)
bool CCactus::CheckActive()
{
    if (active == true)
        return true;
    else
        return false;
}

//������ ������ �������� � �������� � �������� ����������
void CCactus::Activate()
{
    if (CCollisionObjects::CollisionObjectsActiveCount >= maxCollisionObjectsActive)
        return;

    active = true;
    CCollisionObjects::CollisionObjectsActiveCount++;

    pos_X = startPos_X;
    pos_Y = static_cast<float>(startPos_Y);
}

//�������� ��������� �������
void CCactus::TestActivate(float pos_x, float pos_y)
{
    if (CCollisionObjects::CollisionObjectsActiveCount >= CCollisionObjects::maxCollisionObjectsActive)
        return;

    active = true;
    CCollisionObjects::CollisionObjectsActiveCount++;

    pos_X = pos_x;
    pos_Y = pos_y;
}

//�������� ������� �� ��������
void CCactus::Move(float maxSpeed)
{
    if (active == false)
        return;

    if (CBackgroundObjects::speed == 0.0f)
        return;

    ////�������� �� ��������� ����� 
    //restDistance += CBackgroundObjects::speed;

    //while (restDistance > 0.0f)
    //{
    //    //����� �� ����������� ��� (1 pxl)
    //    pos_X -= CConfig::minShift;
    //    restDistance -= CConfig::minShift;
    //}

    float nextStep = CBackgroundObjects::speed / maxSpeed * CConfig::minShift;

    pos_X -= nextStep;

    if (static_cast<int>(pos_X) + CBackgroundObjects::speed + width * CConfig::SizeScale <= CConfig::leftBorder)
    {
        active = false;
        CCollisionObjects::CollisionObjectsActiveCount--;
    }
}
// -----------------------------------------------------------------------------------


// ----------------------------- ����� ����� ������ (������� ������ ����) ------------------
//�����������
CRoadLine::CRoadLine()
    :active(false), roadLineRect{}, prevRoadLineRect{}
{
}

//��������� �����
void CRoadLine::Draw(HDC hdc, RECT& paintArea)
{
    RECT intersectionRect; //����� ��� �-��� �������� ����������� ���������������, � ���� ����������� ������� ����������� ��� 0

    //TO DO: �������� ������� �������� ������� ���� �������, � �� �������� TRUE � InvalidateRect(CConfig::Hwnd, &prevDinoRect, TRUE);

    if (!IntersectRect(&intersectionRect, &paintArea, &roadLineRect))
    {
        return;
    }
    
    //TO DO: �������� ����� ������ ��� �����������
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    //������ ������
    Rectangle(hdc, pos_x, pos_y, pos_x + lineWidth, pos_y + lineHeight * CConfig::SizeScale);
}

//����������� � ����� �����������
void CRoadLine::Redraw()
{
    if (active == false)
        return;

    prevRoadLineRect = roadLineRect;

    roadLineRect.left = static_cast<int>(pos_X);
    roadLineRect.top = static_cast<int>(pos_Y);
    roadLineRect.right = roadLineRect.left + lineWidth; //�� ��������� �� SizeScale, ��� ��� ������ �� ���� �����
    roadLineRect.bottom = roadLineRect.top + lineHeight  * CConfig::SizeScale;

    InvalidateRect(CConfig::Hwnd, &prevRoadLineRect, TRUE);
    InvalidateRect(CConfig::Hwnd, &roadLineRect, TRUE);
}

//������ ������ �������� � �������� � �������� ����������
void CRoadLine::Activate()
{
    active = true;
}

//�������� ������� �� ��������
void CRoadLine::Move(float maxSpeed) //� ������� �� ������ ��������, �� ������� ����� ������, � ������ �������������� �� ��� �� �����
{
    if (active == false)
        return;

    if (CBackgroundObjects::speed == 0.0f)
        return;

    Redraw();
}
// -----------------------------------------------------------------------------------


// ----------------------------- ����� ������ (�������) �� ������ (������� ������ ����) ------------------
//�����������
CRoadStones::CRoadStones()
    :pos_X(startPos_X), pos_Y(startPos_Y), active(false), roadStonesRect{}, prevRoadStonesRect{}
{
}

//��������� �����
void CRoadStones::Draw(HDC hdc, RECT& paintArea)
{
    RECT intersectionRect; //����� ��� �-��� �������� ����������� ���������������, � ���� ����������� ������� ����������� ��� 0

    //TO DO: �������� ������� �������� ������� ���� �������, � �� �������� TRUE � InvalidateRect(CConfig::Hwnd, &prevDinoRect, TRUE);

    if (!IntersectRect(&intersectionRect, &paintArea, &roadStonesRect))
    {
        return;
    }

    
    CConfig::secondPaleColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    //TO DO: �������� ��������� � �������� ��������� �� Scale
    //������ ������
    Rectangle(hdc, pos_x, pos_y + 6, pos_x + 4, pos_y + 6 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 7, pos_y + 3, pos_x + 7 + 5, pos_y + 3 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 15, pos_y + 6, pos_x + 15 + 2, pos_y + 6 + stonesHeight * CConfig::SizeScale);
    
    Rectangle(hdc, pos_x + 40, pos_y + 4, pos_x + 40 + 1, pos_y + 5 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 48, pos_y + 5, pos_x + 48 + 5, pos_y + 5 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 55, pos_y + 2, pos_x + 55 + 4, pos_y + 2 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 68, pos_y + 4, pos_x + 68 + 3, pos_y + 4 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 80, pos_y + 2, pos_x + 80 + 1, pos_y + 3 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 84, pos_y + 4, pos_x + 84 + 5, pos_y + 4 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 94, pos_y + 2, pos_x + 94 + 3, pos_y + 2 + stonesHeight * CConfig::SizeScale);
    
    Rectangle(hdc, pos_x + 112, pos_y + 4, pos_x + 112 + 1, pos_y + 5 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 122, pos_y + 4, pos_x + 122 + 3, pos_y + 4 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 134, pos_y + 1, pos_x + 134 + 5, pos_y + 1 + stonesHeight * CConfig::SizeScale);
    
    Rectangle(hdc, pos_x + 156, pos_y + 3, pos_x + 156 + 1, pos_y + 4 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 160, pos_y + 2, pos_x + 160 + 2, pos_y + 2 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 166, pos_y + 3, pos_x + 166 + 4, pos_y + 3 + stonesHeight * CConfig::SizeScale);
    
    Rectangle(hdc, pos_x + 186, pos_y + 2, pos_x + 186 + 1, pos_y + 3 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 200, pos_y + 2, pos_x + 200 + 3, pos_y + 2 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 206, pos_y + 3, pos_x + 206 + 1, pos_y + 4 + stonesHeight * CConfig::SizeScale);
    
    Rectangle(hdc, pos_x + 220, pos_y + 3, pos_x + 220 + 2, pos_y + 3 + stonesHeight * CConfig::SizeScale);

    Rectangle(hdc, pos_x + 238, pos_y + 4, pos_x + 238 + 3, pos_y + 4 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 244, pos_y + 4, pos_x + 244 + 2, pos_y + 4 + stonesHeight * CConfig::SizeScale);

    Rectangle(hdc, pos_x + 260, pos_y + 4, pos_x + 260 + 4, pos_y + 4 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 280, pos_y + 3, pos_x + 280 + 3, pos_y + 3 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 304, pos_y + 2, pos_x + 304 + 1, pos_y + 3 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 320, pos_y + 4, pos_x + 320 + 3, pos_y + 4 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 340, pos_y + 1, pos_x + 340 + 3, pos_y + 1 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 350, pos_y + 2, pos_x + 350 + 1, pos_y + 3 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 370, pos_y + 2, pos_x + 370 + 3, pos_y + 2 + stonesHeight * CConfig::SizeScale);
    
    Rectangle(hdc, pos_x + 390, pos_y + 3, pos_x + 390 + 2, pos_y + 3 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 398, pos_y + 4, pos_x + 398 + 3, pos_y + 4 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 410, pos_y + 3, pos_x + 410 + 1, pos_y + 4 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 424, pos_y + 2, pos_x + 424 + 2, pos_y + 2 + stonesHeight * CConfig::SizeScale);
    
    Rectangle(hdc, pos_x + 450, pos_y + 3, pos_x + 450 + 3, pos_y + 3 + stonesHeight * CConfig::SizeScale);
    
    Rectangle(hdc, pos_x + 480, pos_y + 2, pos_x + 480 + 1, pos_y + 3 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 488, pos_y + 2, pos_x + 488 + 3, pos_y + 2 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 506, pos_y + 3, pos_x + 506 + 4, pos_y + 3 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 518, pos_y + 5, pos_x + 518 + 2, pos_y + 5 + stonesHeight * CConfig::SizeScale);
    
    Rectangle(hdc, pos_x + 540, pos_y + 1, pos_x + 540 + 1, pos_y + 2 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 548, pos_y + 2, pos_x + 548 + 3, pos_y + 2 + stonesHeight * CConfig::SizeScale);
    
    Rectangle(hdc, pos_x + 564, pos_y + 2, pos_x + 564 + 3, pos_y + 2 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 580, pos_y + 3, pos_x + 580 + 1, pos_y + 4 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 586, pos_y + 1, pos_x + 586 + 5, pos_y + 1 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 604, pos_y + 4, pos_x + 604 + 1, pos_y + 5 + stonesHeight * CConfig::SizeScale);
    
    Rectangle(hdc, pos_x + 618, pos_y + 4, pos_x + 618 + 3, pos_y + 4 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 626, pos_y + 2, pos_x + 626 + 4, pos_y + 2 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 632, pos_y + 4, pos_x + 632 + 2, pos_y + 4 + stonesHeight * CConfig::SizeScale);
    
    Rectangle(hdc, pos_x + 646, pos_y + 2, pos_x + 646 + 4, pos_y + 2 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 652, pos_y + 4, pos_x + 652 + 2, pos_y + 4 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 658, pos_y + 1, pos_x + 658 + 1, pos_y + 2 + stonesHeight * CConfig::SizeScale);
    
    Rectangle(hdc, pos_x + 678, pos_y + 2, pos_x + 678 + 3, pos_y + 2 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 686, pos_y + 4, pos_x + 686 + 3, pos_y + 4 + stonesHeight * CConfig::SizeScale);
    
    Rectangle(hdc, pos_x + 700, pos_y + 1, pos_x + 700 + 4, pos_y + 1 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 710, pos_y + 2, pos_x + 710 + 2, pos_y + 2 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 720, pos_y + 3, pos_x + 720 + 1, pos_y + 4 + stonesHeight * CConfig::SizeScale);
    
    Rectangle(hdc, pos_x + 740, pos_y + 3, pos_x + 740 + 3, pos_y + 3 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 754, pos_y + 1, pos_x + 754 + 2, pos_y + 1 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 764, pos_y + 3, pos_x + 764 + 3, pos_y + 3 + stonesHeight * CConfig::SizeScale);
    
    Rectangle(hdc, pos_x + 782, pos_y + 4, pos_x + 782 + 4, pos_y + 4 + stonesHeight * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 790, pos_y + 2, pos_x + 790 + 1, pos_y + 3 + stonesHeight * CConfig::SizeScale);
}

//����������� � ����� �����������
void CRoadStones::Redraw()
{
    if (active == false)
        return;

    prevRoadStonesRect = roadStonesRect;

    roadStonesRect.left = static_cast<int>(pos_X);
    roadStonesRect.top = static_cast<int>(pos_Y);
    roadStonesRect.right = roadStonesRect.left + CConfig::rightBorder;
    roadStonesRect.bottom = roadStonesRect.top + maxStonesHeight * CConfig::SizeScale;

    InvalidateRect(CConfig::Hwnd, &prevRoadStonesRect, TRUE);
    InvalidateRect(CConfig::Hwnd, &roadStonesRect, TRUE);
}

//������ ������ �������� � �������� � �������� ����������
void CRoadStones::Activate()
{
    active = true;

    pos_X = restartPos_X;
}

void CRoadStones::FirstActivate()
{
    active = true;

    pos_X = 0.0f;
}

//�������� ������� �� ��������
void CRoadStones::Move(float maxSpeed)
{
    if (active == false)
        return;

    if (speed == 0.0f)
        return;

    //pos_X -= CBackgroundObjects::speed;

    //�������� �� ��������� ����� 
    //float restDistance = CBackgroundObjects::speed;

    //while (restDistance > 0.0f)
    //{
    //    //����� �� ����������� ��� (1 pxl)
    //    pos_X -= CConfig::minShift;

    //    restDistance -= CConfig::minShift;
    //}

    pos_X -= CBackgroundObjects::speed;

    if (static_cast<int>(pos_X) + 700 + stonesWidth + speed <= CConfig::leftBorder)
    {
        active = false;
    }

    Redraw();
}
// -----------------------------------------------------------------------------------


// ----------------------------- ����� ��� �� ������ (������� ������ ����) ------------------

CRoadBump::CRoadBump()
    :pos_X(restartPos_X), firstBumpType(true), active(false), bumpRect{}, prevBumpRect{}
{
}

//��������� �����
void CRoadBump::Draw(HDC hdc, RECT& paintArea)
{
    RECT intersectionRect; //����� ��� �-��� �������� ����������� ���������������, � ���� ����������� ������� ����������� ��� 0

    //TO DO: �������� ������� �������� ������� ���� �������, � �� �������� TRUE � InvalidateRect(CConfig::Hwnd, &prevDinoRect, TRUE);

    if (!IntersectRect(&intersectionRect, &paintArea, &bumpRect))
    {
        return;
    }

    if (firstBumpType == true)
    {
        DrawPit(hdc, paintArea, 0.0f);
        DrawPit(hdc, paintArea, 30.0f);
    }
    else
    {
        DrawBump(hdc, paintArea, 0.0f);
        DrawPit(hdc, paintArea, 30.0f);
    }
}

//����������� � ����� �����������
void CRoadBump::Redraw()
{
    if (active == false)
        return;

    prevBumpRect = bumpRect;

    bumpRect.left = static_cast<int>(pos_X);
    bumpRect.top = static_cast<int>(pos_Y);
    bumpRect.right = bumpRect.left + width;
    bumpRect.bottom = bumpRect.top + height * CConfig::SizeScale;

    InvalidateRect(CConfig::Hwnd, &prevBumpRect, TRUE);
    InvalidateRect(CConfig::Hwnd, &bumpRect, TRUE);
}

void CRoadBump::TestActivate()
{
    active = true;

    pos_X = restartPos_X / 2.0f;
}

void CRoadBump::Activate()
{
    active = true;

    pos_X = restartPos_X;
}

//�������� ������� �� ��������
void CRoadBump::Move(float maxSpeed)
{
    if (active == false)
        return;

    if (CBackgroundObjects::speed == 0.0f)
        return;

    pos_X -= CBackgroundObjects::speed;

    if (static_cast<int>(pos_X) + CBackgroundObjects::speed + width * CConfig::SizeScale <= CConfig::leftBorder)
        active = false;

    Redraw();
}

//��������� ���
void CRoadBump::DrawPit(HDC hdc, RECT& paintArea, float offset_x)
{
    int pos_x = static_cast<int>(pos_X  + offset_x);
    int pos_y = static_cast<int>(pos_Y);

    //���
    //������ �������� �������
    CConfig::backgroundColor.SelectColor(hdc);

    Rectangle(hdc, pos_x + 1 * CConfig::SizeScale, pos_y + 3 * CConfig::SizeScale, pos_x + 13 * CConfig::SizeScale, pos_y + 4 * CConfig::SizeScale);

    CConfig::mainBrightColor.SelectColor(hdc);

    Rectangle(hdc, pos_x, pos_y + 4 * CConfig::SizeScale, pos_x + 2 * CConfig::SizeScale, pos_y + 5 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 1 * CConfig::SizeScale, pos_y + 5 * CConfig::SizeScale, pos_x + 3 * CConfig::SizeScale, pos_y + 6 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 2 * CConfig::SizeScale, pos_y + 6 * CConfig::SizeScale, pos_x + 12 * CConfig::SizeScale, pos_y + 7 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 11 * CConfig::SizeScale, pos_y + 5 * CConfig::SizeScale, pos_x + 13 * CConfig::SizeScale, pos_y + 6 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 12 * CConfig::SizeScale, pos_y + 4 * CConfig::SizeScale, pos_x + 14 * CConfig::SizeScale, pos_y + 5 * CConfig::SizeScale);
}

//��������� �����
void CRoadBump::DrawBump(HDC hdc, RECT& paintArea, float offset_x)
{
    int pos_x = static_cast<int>(pos_X + offset_x);
    int pos_y = static_cast<int>(pos_Y);

    //������ �������� �������
    CConfig::backgroundColor.SelectColor(hdc);

    Rectangle(hdc, pos_x + 2 * CConfig::SizeScale, pos_y + 3 * CConfig::SizeScale, pos_x + 14 * CConfig::SizeScale, pos_y + 4 * CConfig::SizeScale);

    //�����
    CConfig::mainBrightColor.SelectColor(hdc);

    Rectangle(hdc, pos_x + 1 * CConfig::SizeScale, pos_y + 2 * CConfig::SizeScale, pos_x + 3 * CConfig::SizeScale, pos_y + 3 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 2 * CConfig::SizeScale, pos_y + 1 * CConfig::SizeScale, pos_x + 4 * CConfig::SizeScale, pos_y + 2 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 3 * CConfig::SizeScale, pos_y, pos_x + 13 * CConfig::SizeScale, pos_y + 1 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 12 * CConfig::SizeScale, pos_y + 1 * CConfig::SizeScale, pos_x + 14 * CConfig::SizeScale, pos_y + 2 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 13 * CConfig::SizeScale, pos_y + 2 * CConfig::SizeScale, pos_x + 15 * CConfig::SizeScale, pos_y + 3 * CConfig::SizeScale);
}


// -----------------------------------------------------------------------------------



// ----------------------------- ����� ������ �� ������ ����� ------------------------

const float CCloud::cloudsSpeed = CBackgroundObjects::speed;

//�����������
CCloud::CCloud()
    :pos_X(800.0f), pos_Y(startPos_Y), active(false), cloudRect{}, prevCloudRect{}
{
}

//��������� ��������
void CCloud::Draw(HDC hdc, RECT& paintArea)
{
    RECT intersectionRect; //����� ��� �-��� �������� ����������� ���������������, � ���� ����������� ������� ����������� ��� 0

    if (!IntersectRect(&intersectionRect, &paintArea, &cloudRect))
    {
        return;
    }

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    CConfig::secondPaleColor.SelectColor(hdc);

    //����
    Rectangle(hdc, pos_x, pos_y, pos_x + 58 * CConfig::SizeScale, pos_y + 16 * CConfig::SizeScale);

    //������� ��������
    CConfig::backgroundColor.SelectColor(hdc);

    //������� ����
    Rectangle(hdc, pos_x, pos_y, pos_x + 6 * CConfig::SizeScale, pos_y + 11 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 6 * CConfig::SizeScale, pos_y, pos_x + 16 * CConfig::SizeScale, pos_y + 7 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 16 * CConfig::SizeScale, pos_y, pos_x + 20 * CConfig::SizeScale, pos_y + 6 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 20 * CConfig::SizeScale, pos_y, pos_x + 23 * CConfig::SizeScale, pos_y + 4 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 23 * CConfig::SizeScale, pos_y, pos_x + 25 * CConfig::SizeScale, pos_y + 3 * CConfig::SizeScale);

    Rectangle(hdc, pos_x + 38 * CConfig::SizeScale, pos_y, pos_x + 40 * CConfig::SizeScale, pos_y + 2 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 40 * CConfig::SizeScale, pos_y, pos_x + 43 * CConfig::SizeScale, pos_y + 5 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 43 * CConfig::SizeScale, pos_y, pos_x + 47 * CConfig::SizeScale, pos_y + 6 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 47 * CConfig::SizeScale, pos_y, pos_x + 49 * CConfig::SizeScale, pos_y + 7 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 49 * CConfig::SizeScale, pos_y, pos_x + 52 * CConfig::SizeScale, pos_y + 8 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 51 * CConfig::SizeScale, pos_y, pos_x + 55 * CConfig::SizeScale, pos_y + 11 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 55 * CConfig::SizeScale, pos_y, pos_x + 58 * CConfig::SizeScale, pos_y + 13 * CConfig::SizeScale);

    //������ ������
    Rectangle(hdc, pos_x + 2 * CConfig::SizeScale, pos_y + 13 * CConfig::SizeScale, pos_x + 54 * CConfig::SizeScale, pos_y + 14 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 8 * CConfig::SizeScale, pos_y + 9 * CConfig::SizeScale, pos_x + 49 * CConfig::SizeScale, pos_y + 14 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 42 * CConfig::SizeScale, pos_y + 8 * CConfig::SizeScale, pos_x + 46 * CConfig::SizeScale, pos_y + 9 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 39 * CConfig::SizeScale, pos_y + 7 * CConfig::SizeScale, pos_x + 42 * CConfig::SizeScale, pos_y + 9 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 35 * CConfig::SizeScale, pos_y + 8 * CConfig::SizeScale, pos_x + 39 * CConfig::SizeScale, pos_y + 9 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 28 * CConfig::SizeScale, pos_y + 2 * CConfig::SizeScale, pos_x + 35 * CConfig::SizeScale, pos_y + 9 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 35 * CConfig::SizeScale, pos_y + 3 * CConfig::SizeScale, pos_x + 37 * CConfig::SizeScale, pos_y + 6 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 22 * CConfig::SizeScale, pos_y + 6 * CConfig::SizeScale, pos_x + 23 * CConfig::SizeScale, pos_y + 9 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 23 * CConfig::SizeScale, pos_y + 5 * CConfig::SizeScale, pos_x + 25 * CConfig::SizeScale, pos_y + 9 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + 25 * CConfig::SizeScale, pos_y + 4 * CConfig::SizeScale, pos_x + 28 * CConfig::SizeScale, pos_y + 9 * CConfig::SizeScale);
}

//����������� ��������� � ����� �����������
void CCloud::Redraw()
{
    if (active == false)
        return;

    prevCloudRect = cloudRect;

    cloudRect.left = static_cast<int>(pos_X);
    cloudRect.top = static_cast<int>(pos_Y);
    cloudRect.right = cloudRect.left + width * CConfig::SizeScale;
    cloudRect.bottom = cloudRect.top + height * CConfig::SizeScale;

    InvalidateRect(CConfig::Hwnd, &prevCloudRect, TRUE);
    InvalidateRect(CConfig::Hwnd, &cloudRect, TRUE);
}

//������ ������ �������� � �������� � �������� ����������
void CCloud::Activate()
{
    active = true;

    int y = CConfig::GetRandom(20, 120);

    pos_X = restartPos_X;
    pos_Y = static_cast<float>(y);
}

void CCloud::FirstActivate()
{
    active = true;

    pos_X = static_cast<float>(CConfig::GetRandom(100, 700));
    pos_Y = static_cast<float>(CConfig::GetRandom(20, 130));
}

//�������� ������� �� ��������
void CCloud::Move(float maxSpeed)
{
    if (active == false)
        return;

    if (cloudsSpeed == 0.0f)
        return;

    pos_X -= cloudsSpeed;

    if (static_cast<int>(pos_X) + cloudsSpeed + width * CConfig::SizeScale <= CConfig::leftBorder)
        active = false;
        //pos_X = startPos_X;

    Redraw();
}
// -----------------------------------------------------------------------------------