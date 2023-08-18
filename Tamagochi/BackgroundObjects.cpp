#include "BackgroundObjects.h"

// ----------------------------- ����� ������ ��� ------------------------------------
CBackgroundObjects::CBackgroundObjects()
    :speed(5.0f)
{
}
// -----------------------------------------------------------------------------------


// ----------------------------- ����� ����� (���������) -----------------------------
//�����������
CBird::CBird()
    :pos_X(startPos_X), pos_Y(130.0f), upWing(true), birdRect{}, prevBirdRect{}
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
    prevBirdRect = birdRect;

    birdRect.left = static_cast<int>(pos_X);
    birdRect.top = static_cast<int>(pos_Y);
    birdRect.right = birdRect.left + width * CConfig::SizeScale;
    birdRect.bottom = birdRect.top + (downWingHeight + 7) * CConfig::SizeScale;

    InvalidateRect(CConfig::Hwnd, &prevBirdRect, TRUE);
    InvalidateRect(CConfig::Hwnd, &birdRect, TRUE);
}

//�������� ��� ��� �������� ������
void CBird::MoveWings(HDC hdc)
{
    if (static_cast<int>(CConfig::MovingLegsSpeed) % 2 == 0) //TO DO: ��������� �������� �������� ����� � ������ �����. ��� ������� �������� ������ ��� 10 ���
    {
        upWing = true;
        DrawUpWing(hdc);
    }
    else
    {
        upWing = false;
        DrawDownWing(hdc);
    }
}

//�������� ������� �� ��������
void CBird::Move()
{
    if (speed == 0.0f)
        return;

    //�������� �� ��������� ����� 
    float restDistance = speed;

    while (restDistance > 0.0f)
    {
        //����� �� ��������� ���
        //float nextStep = speed / maxSpeed * CConfig::minShift; //��������� ����������� ��� ��� ����������� ���� (����� �������� ���� �� ������������ �������� � �������� ��� �����, �� ������� �� ����������� ���.
        //���� ���� ������� ��������, �� ����� ������� �� ������� ���. �� � ����� ���������� ������� ����� ��� ��. (������������� ��������)
        pos_X -= CConfig::minShift;

        restDistance -= CConfig::minShift;
    }

    if (static_cast<int>(pos_X) <= (CConfig::leftBorder - width * CConfig::SizeScale))
        pos_X = startPos_X;
}

// -----------------------------------------------------------------------------------


// ----------------------------- ����� ������� (�����������) -------------------------
//�����������
CCactus::CCactus()
    :pos_X(startPos_X), pos_Y(150.0f), cactusRect{ 0 }, prevCactusRect{ 0 }
{

}

//���������
void CCactus::Draw(HDC hdc, RECT& paintArea)
{
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
    prevCactusRect = cactusRect;

    cactusRect.left = static_cast<int>(pos_X);
    cactusRect.top = static_cast<int>(pos_Y);
    cactusRect.right = cactusRect.left + width * CConfig::SizeScale;
    cactusRect.bottom = cactusRect.top + (height) * CConfig::SizeScale;

    InvalidateRect(CConfig::Hwnd, &prevCactusRect, TRUE);
    InvalidateRect(CConfig::Hwnd, &cactusRect, TRUE);
}

//�������� ������� �� ��������
void CCactus::Move()
{
    if (speed == 0.0f)
        return;

    //�������� �� ��������� ����� 
    float restDistance = speed;

    while (restDistance > 0.0f)
    {
        //����� �� ��������� ���
        //float nextStep = speed / maxSpeed * CConfig::minShift; //��������� ����������� ��� ��� ����������� ���� (����� �������� ���� �� ������������ �������� � �������� ��� �����, �� ������� �� ����������� ���.
        //���� ���� ������� ��������, �� ����� ������� �� ������� ���. �� � ����� ���������� ������� ����� ��� ��. (������������� ��������)
        pos_X -= CConfig::minShift;

        restDistance -= CConfig::minShift;
    }

    if (static_cast<int>(pos_X) <= (CConfig::leftBorder - width * CConfig::SizeScale))
        pos_X = startPos_X;
}

// -----------------------------------------------------------------------------------


// ----------------------------- ����� ������ (������� ������ ����) ------------------

//�����������
CRoadLevel::CRoadLevel()
    :pos_X(startPos_X), pos_Y(180.0f), roadRect{ 0 }, prevRoadRect{ 0 }
{
}

//��������� �����
void CRoadLevel::Draw(HDC hdc, RECT& paintArea)
{
    DrawRoad(hdc, paintArea);
    DrawPit(hdc, paintArea, 10);
    DrawBump(hdc, paintArea, 40);
    DrawRocks(hdc, paintArea, 10, 15);
}

//��������� ����� ������
void CRoadLevel::DrawRoad(HDC hdc, RECT& paintArea)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    //������ ������
    Rectangle(hdc, pos_x, pos_y + 6 * CConfig::SizeScale, pos_x + CConfig::rightBorder, pos_y + 7 * CConfig::SizeScale);
}

//��������� ������ (������ ���� ������)
void CRoadLevel::DrawRocks(HDC hdc, RECT& paintArea, int offset_x, int offset_y)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    int randomoffsetbetweenrocks_x = 5;
    int randomoffsetbetweenrocks_y = 5;
    //����� �� ������
    Rectangle(hdc, pos_x + (10 + offset_x) * CConfig::SizeScale, pos_y + (13 + offset_y) * CConfig::SizeScale, pos_x + (12 + offset_x) * CConfig::SizeScale, pos_y + (15 + offset_y) * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (10 + offset_x + randomoffsetbetweenrocks_x) * CConfig::SizeScale, pos_y + (13 + offset_y) * CConfig::SizeScale, pos_x + (13 + offset_x + randomoffsetbetweenrocks_x) * CConfig::SizeScale, pos_y + (15 + offset_y) * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (10 + offset_x) * CConfig::SizeScale, pos_y + (13 + offset_y + randomoffsetbetweenrocks_y) * CConfig::SizeScale, pos_x + (14 + offset_x) * CConfig::SizeScale, pos_y + (15 + offset_y + randomoffsetbetweenrocks_y) * CConfig::SizeScale);
}

//��������� ���
void CRoadLevel::DrawPit(HDC hdc, RECT& paintArea, int offset_x)
{
    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    //���
    //������ �������� �������
    CConfig::backgroundColor.SelectColor(hdc);

    Rectangle(hdc, pos_x + (1 + offset_x) * CConfig::SizeScale, pos_y + 6 * CConfig::SizeScale, pos_x + (13 + offset_x) * CConfig::SizeScale, pos_y + 7 * CConfig::SizeScale);

    CConfig::mainBrightColor.SelectColor(hdc);

    Rectangle(hdc, pos_x + offset_x * CConfig::SizeScale, pos_y + 7 * CConfig::SizeScale, pos_x + (2 + offset_x) * CConfig::SizeScale, pos_y + 8 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (1 + offset_x) * CConfig::SizeScale, pos_y + 8 * CConfig::SizeScale, pos_x + (3 + offset_x) * CConfig::SizeScale, pos_y + 9 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (2 + offset_x) * CConfig::SizeScale, pos_y + 9 * CConfig::SizeScale, pos_x + (12 + offset_x) * CConfig::SizeScale, pos_y + 10 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (11 + offset_x) * CConfig::SizeScale, pos_y + 8 * CConfig::SizeScale, pos_x + (13 + offset_x) * CConfig::SizeScale, pos_y + 9 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (12 + offset_x) * CConfig::SizeScale, pos_y + 7 * CConfig::SizeScale, pos_x + (14 + offset_x) * CConfig::SizeScale, pos_y + 8 * CConfig::SizeScale);
}

//��������� �����
void CRoadLevel::DrawBump(HDC hdc, RECT& paintArea, int offset_x)
{
    int pos_x = static_cast<int>(pos_X);
    int pos_y = static_cast<int>(pos_Y);

    //������ �������� �������
    CConfig::backgroundColor.SelectColor(hdc);

    Rectangle(hdc, pos_x + (2 + offset_x) * CConfig::SizeScale, pos_y + 6 * CConfig::SizeScale, pos_x + (14 + offset_x) * CConfig::SizeScale, pos_y + 7 * CConfig::SizeScale);

    //�����
    CConfig::mainBrightColor.SelectColor(hdc);

    Rectangle(hdc, pos_x + (1 + offset_x) * CConfig::SizeScale, pos_y + 5 * CConfig::SizeScale, pos_x + (3 + offset_x) * CConfig::SizeScale, pos_y + 6 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (2 + offset_x) * CConfig::SizeScale, pos_y + 4 * CConfig::SizeScale, pos_x + (4 + offset_x) * CConfig::SizeScale, pos_y + 5 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (3 + offset_x) * CConfig::SizeScale, pos_y + 3 * CConfig::SizeScale, pos_x + (13 + offset_x) * CConfig::SizeScale, pos_y + 4 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (12 + offset_x) * CConfig::SizeScale, pos_y + 4 * CConfig::SizeScale, pos_x + (14 + offset_x) * CConfig::SizeScale, pos_y + 5 * CConfig::SizeScale);
    Rectangle(hdc, pos_x + (13 + offset_x) * CConfig::SizeScale, pos_y + 5 * CConfig::SizeScale, pos_x + (15 + offset_x) * CConfig::SizeScale, pos_y + 6 * CConfig::SizeScale);
}

//����������� ��������� � ����� �����������
void CRoadLevel::Redraw()
{
    prevRoadRect = roadRect;

    roadRect.left = static_cast<int>(pos_X);
    roadRect.top = static_cast<int>(pos_Y);
    roadRect.right = roadRect.left + width * CConfig::SizeScale;
    roadRect.bottom = roadRect.top + (height)*CConfig::SizeScale;

    InvalidateRect(CConfig::Hwnd, &prevRoadRect, TRUE);
    InvalidateRect(CConfig::Hwnd, &roadRect, TRUE);
}

//�������� ������� �� ��������
void CRoadLevel::Move()
{
    if (speed == 0.0f)
        return;

    //�������� �� ��������� ����� 
    float restDistance = speed;

    while (restDistance > 0.0f)
    {
        //����� �� ��������� ���
        //float nextStep = speed / maxSpeed * CConfig::minShift; //��������� ����������� ��� ��� ����������� ���� (����� �������� ���� �� ������������ �������� � �������� ��� �����, �� ������� �� ����������� ���.
        //���� ���� ������� ��������, �� ����� ������� �� ������� ���. �� � ����� ���������� ������� ����� ��� ��. (������������� ��������)
        pos_X -= CConfig::minShift;

        restDistance -= CConfig::minShift;
    }

    if (static_cast<int>(pos_X) <= (CConfig::leftBorder - width * CConfig::SizeScale))
        pos_X = startPos_X;
}

// -----------------------------------------------------------------------------------


// ----------------------------- ����� ������ �� ������ ����� ------------------------
//�����������
CCloud::CCloud()
    :pos_X(0), pos_Y(0), cloudRect{ 0 }, prevCloudRect{ 0 }, visible(false)
{
}

//��������� ��������
void CCloud::Draw(HDC hdc, RECT& paintArea)
{
    //RECT intersectionRect; //����� ��� �-��� �������� ����������� ���������������, � ���� ����������� ������� ����������� ��� 0

    //if (!IntersectRect(&intersectionRect, &paintArea, &dinoRect))
    //{
    //    return;
    //}

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
    prevCloudRect = cloudRect;

    cloudRect.left = static_cast<int>(pos_X);
    cloudRect.top = static_cast<int>(pos_Y);
    cloudRect.right = cloudRect.left + width * CConfig::SizeScale;
    cloudRect.bottom = cloudRect.top + height * CConfig::SizeScale;

    InvalidateRect(CConfig::Hwnd, &prevCloudRect, TRUE);
    InvalidateRect(CConfig::Hwnd, &cloudRect, TRUE);
}

//������������� ���������� ��������� �������
void CCloud::Init()
{
    float startPos_X = static_cast<float>(CConfig::GetRandom(100, 600));
    float startPos_Y = static_cast<float>(CConfig::GetRandom(50, 130));
    pos_X = startPos_X;
    pos_Y = startPos_Y;
}

//�������� ������� �� ��������
void CCloud::Move()
{
    if (speed == 0.0f)
        return;

    pos_X -= speed;

    if (static_cast<int>(pos_X) <= (CConfig::leftBorder - width * CConfig::SizeScale))
        visible = false;
        //pos_X = startPos_X;

    Redraw();
}

// -----------------------------------------------------------------------------------