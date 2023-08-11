#include "BackgroundObjects.h"

// ----------------------------- ����� ����� (���������) ----------------------------------------------
//�����������
CBird::CBird()
    :pos_X(160.0f * CConfig::FSizeScale), pos_Y(130.0f * CConfig::FSizeScale), flyingSpeed(5.0f), upWing(true), birdRect{}, prevBirdRect{}
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

//�������� ������� �� ��������
void CBird::Move(float maxSpeed)
{
    if (flyingSpeed == 0.0f)
        return;

    //�������� �� ��������� ����� 
    float restDistance = maxSpeed;

    while (restDistance > 0.0f)
    {
        //����� �� ��������� ���
        float nextStep = flyingSpeed / maxSpeed * CConfig::minShift; //��������� ����������� ��� ��� ����������� ���� (����� �������� ���� �� ������������ �������� � �������� ��� �����, �� ������� �� ����������� ���.
                                                                     //���� ���� ������� ��������, �� ����� ������� �� ������� ���. �� � ����� ���������� ������� ����� ��� ��. (������������� ��������)
        pos_X -= nextStep;

        restDistance -= CConfig::minShift;
    }

    if (static_cast<int>(pos_X) <= (CConfig::leftBorder - width))
        pos_X = 160.0f * CConfig::FSizeScale;
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
// -----------------------------------------------------------------------------------


// ----------------------------- ����� ������� (�����������) ----------------------------------------------
//�����������
CCactus::CCactus()
    :pos_X(60 * CConfig::SizeScale), pos_Y(150 * CConfig::SizeScale)
{

}

//���������
void CCactus::Draw(HDC hdc, RECT& paintArea)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    //����� �������
    Rectangle(hdc, pos_X + 8 * CConfig::SizeScale, pos_Y + 2 * CConfig::SizeScale, pos_X + 14 * CConfig::SizeScale, pos_Y + 48 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 10 * CConfig::SizeScale, pos_Y, pos_X + 12 * CConfig::SizeScale, pos_Y + 2 * CConfig::SizeScale);

    //����� ����� �������
    Rectangle(hdc, pos_X + 3 * CConfig::SizeScale, pos_Y + 29 * CConfig::SizeScale, pos_X + 8 * CConfig::SizeScale, pos_Y + 31 * CConfig::SizeScale);
    Rectangle(hdc, pos_X, pos_Y + 15 * CConfig::SizeScale, pos_X + 3 * CConfig::SizeScale, pos_Y + 29 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 1 * CConfig::SizeScale, pos_Y + 13 * CConfig::SizeScale, pos_X + 2 * CConfig::SizeScale, pos_Y + 15 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 1 * CConfig::SizeScale, pos_Y + 29 * CConfig::SizeScale, pos_X + 4 * CConfig::SizeScale, pos_Y + 30 * CConfig::SizeScale);

    //������ ����� �������
    Rectangle(hdc, pos_X + 14 * CConfig::SizeScale, pos_Y + 27 * CConfig::SizeScale, pos_X + 19 * CConfig::SizeScale, pos_Y + 29 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 19 * CConfig::SizeScale, pos_Y + 13 * CConfig::SizeScale, pos_X + 22 * CConfig::SizeScale, pos_Y + 27 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 20 * CConfig::SizeScale, pos_Y + 11 * CConfig::SizeScale, pos_X + 21 * CConfig::SizeScale, pos_Y + 13 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 19 * CConfig::SizeScale, pos_Y + 27 * CConfig::SizeScale, pos_X + 21 * CConfig::SizeScale, pos_Y + 28 * CConfig::SizeScale);

    //����� ����� ������� ������� 2
    //Rectangle(hdc, pos_X + 3 * CConfig::SizeScale, pos_Y + 29 - 6 * CConfig::SizeScale, pos_X + 8 * CConfig::SizeScale, pos_Y + 31 - 6 * CConfig::SizeScale);
    //Rectangle(hdc, pos_X, pos_Y + 15 - 6 * CConfig::SizeScale, pos_X + 3 * CConfig::SizeScale, pos_Y + 29 - 6 * CConfig::SizeScale);
    //Rectangle(hdc, pos_X + 1 * CConfig::SizeScale, pos_Y + 13 - 6 * CConfig::SizeScale, pos_X + 2 * CConfig::SizeScale, pos_Y + 15 - 6 * CConfig::SizeScale);
    //Rectangle(hdc, pos_X + 1 * CConfig::SizeScale, pos_Y + 29 - 6 * CConfig::SizeScale, pos_X + 4 * CConfig::SizeScale, pos_Y + 30 - 6 * CConfig::SizeScale);

    //������ ����� ������� ������� 2
    //Rectangle(hdc, pos_X + 14 * CConfig::SizeScale, pos_Y + 27 * CConfig::SizeScale, pos_X + 19 * CConfig::SizeScale, pos_Y + 29 * CConfig::SizeScale);
    //Rectangle(hdc, pos_X + 19 * CConfig::SizeScale, pos_Y + 13 * CConfig::SizeScale, pos_X + 22 * CConfig::SizeScale, pos_Y + 27 * CConfig::SizeScale);
    //Rectangle(hdc, pos_X + 20 * CConfig::SizeScale, pos_Y + 11 * CConfig::SizeScale, pos_X + 21 * CConfig::SizeScale, pos_Y + 13 * CConfig::SizeScale);
    //Rectangle(hdc, pos_X + 19 * CConfig::SizeScale, pos_Y + 27 * CConfig::SizeScale, pos_X + 21 * CConfig::SizeScale, pos_Y + 28 * CConfig::SizeScale);

    //����� ����� ������� ������� 2
    //Rectangle(hdc, pos_X + 3 * CConfig::SizeScale, pos_Y + 29 - 6 * CConfig::SizeScale, pos_X + 8 * CConfig::SizeScale, pos_Y + 31 - 6 * CConfig::SizeScale);
    //Rectangle(hdc, pos_X, pos_Y + 15 - 6 * CConfig::SizeScale, pos_X + 3 * CConfig::SizeScale, pos_Y + 29 - 6 * CConfig::SizeScale);
    //Rectangle(hdc, pos_X + 1 * CConfig::SizeScale, pos_Y + 13 - 6 * CConfig::SizeScale, pos_X + 2 * CConfig::SizeScale, pos_Y + 15 - 6 * CConfig::SizeScale);
    //Rectangle(hdc, pos_X + 1 * CConfig::SizeScale, pos_Y + 29 - 6 * CConfig::SizeScale, pos_X + 4 * CConfig::SizeScale, pos_Y + 30 - 6 * CConfig::SizeScale);

    //������ ����� ������� ������� 2
    //Rectangle(hdc, pos_X + 14 * CConfig::SizeScale, pos_Y + 27 * CConfig::SizeScale, pos_X + 19 * CConfig::SizeScale, pos_Y + 29 * CConfig::SizeScale);
    //Rectangle(hdc, pos_X + 19 * CConfig::SizeScale, pos_Y + 13 * CConfig::SizeScale, pos_X + 22 * CConfig::SizeScale, pos_Y + 27 * CConfig::SizeScale);
    //Rectangle(hdc, pos_X + 20 * CConfig::SizeScale, pos_Y + 11 * CConfig::SizeScale, pos_X + 21 * CConfig::SizeScale, pos_Y + 13 * CConfig::SizeScale);
    //Rectangle(hdc, pos_X + 19 * CConfig::SizeScale, pos_Y + 27 * CConfig::SizeScale, pos_X + 21 * CConfig::SizeScale, pos_Y + 28 * CConfig::SizeScale);
}
// -----------------------------------------------------------------------------------


// ----------------------------- ����� ������ (������� ������ ����) --------------------------------------

//�����������
CRoadLevel::CRoadLevel()
    :pos_X(0), pos_Y(180 * CConfig::SizeScale)
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

    //������ ������
    Rectangle(hdc, pos_X, pos_Y + 6 * CConfig::SizeScale, pos_X + 200 * CConfig::SizeScale, pos_Y + 7 * CConfig::SizeScale);
}

//��������� ������ (������ ���� ������)
void CRoadLevel::DrawRocks(HDC hdc, RECT& paintArea, int offset_x, int offset_y)
{
    CConfig::mainBrightColor.SelectColor(hdc);

    int randomoffsetbetweenrocks_x = 5;
    int randomoffsetbetweenrocks_y = 5;
    //����� �� ������
    Rectangle(hdc, pos_X + (10 + offset_x) * CConfig::SizeScale, pos_Y + (13 + offset_y) * CConfig::SizeScale, pos_X + (12 + offset_x) * CConfig::SizeScale, pos_Y + (15 + offset_y) * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (10 + offset_x + randomoffsetbetweenrocks_x) * CConfig::SizeScale, pos_Y + (13 + offset_y) * CConfig::SizeScale, pos_X + (13 + offset_x + randomoffsetbetweenrocks_x) * CConfig::SizeScale, pos_Y + (15 + offset_y) * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (10 + offset_x) * CConfig::SizeScale, pos_Y + (13 + offset_y + randomoffsetbetweenrocks_y) * CConfig::SizeScale, pos_X + (14 + offset_x) * CConfig::SizeScale, pos_Y + (15 + offset_y + randomoffsetbetweenrocks_y) * CConfig::SizeScale);
}

//��������� ���
void CRoadLevel::DrawPit(HDC hdc, RECT& paintArea, int offset_x)
{
    //���

    //������ �������� �������
    CConfig::backgroundColor.SelectColor(hdc);

    Rectangle(hdc, pos_X + (1 + offset_x) * CConfig::SizeScale, pos_Y + 6 * CConfig::SizeScale, pos_X + (14 + offset_x) * CConfig::SizeScale, pos_Y + 7 * CConfig::SizeScale);

    CConfig::mainBrightColor.SelectColor(hdc);

    Rectangle(hdc, pos_X + offset_x * CConfig::SizeScale, pos_Y + 7 * CConfig::SizeScale, pos_X + (2 + offset_x) * CConfig::SizeScale, pos_Y + 8 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (1 + offset_x) * CConfig::SizeScale, pos_Y + 8 * CConfig::SizeScale, pos_X + (3 + offset_x) * CConfig::SizeScale, pos_Y + 9 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (2 + offset_x) * CConfig::SizeScale, pos_Y + 9 * CConfig::SizeScale, pos_X + (13 + offset_x) * CConfig::SizeScale, pos_Y + 10 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (12 + offset_x) * CConfig::SizeScale, pos_Y + 8 * CConfig::SizeScale, pos_X + (14 + offset_x) * CConfig::SizeScale, pos_Y + 9 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (13 + offset_x) * CConfig::SizeScale, pos_Y + 7 * CConfig::SizeScale, pos_X + (15 + offset_x) * CConfig::SizeScale, pos_Y + 8 * CConfig::SizeScale);
}

//��������� �����
void CRoadLevel::DrawBump(HDC hdc, RECT& paintArea, int offset_x)
{
    //������ �������� �������
    CConfig::backgroundColor.SelectColor(hdc);

    Rectangle(hdc, pos_X + (2 + offset_x) * CConfig::SizeScale, pos_Y + 6 * CConfig::SizeScale, pos_X + (14 + offset_x) * CConfig::SizeScale, pos_Y + 7 * CConfig::SizeScale);

    //�����
    CConfig::mainBrightColor.SelectColor(hdc);

    Rectangle(hdc, pos_X + (1 + offset_x) * CConfig::SizeScale, pos_Y + 5 * CConfig::SizeScale, pos_X + (3 + offset_x) * CConfig::SizeScale, pos_Y + 6 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (2 + offset_x) * CConfig::SizeScale, pos_Y + 4 * CConfig::SizeScale, pos_X + (4 + offset_x) * CConfig::SizeScale, pos_Y + 5 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (3 + offset_x) * CConfig::SizeScale, pos_Y + 3 * CConfig::SizeScale, pos_X + (13 + offset_x) * CConfig::SizeScale, pos_Y + 4 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (12 + offset_x) * CConfig::SizeScale, pos_Y + 4 * CConfig::SizeScale, pos_X + (14 + offset_x) * CConfig::SizeScale, pos_Y + 5 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + (13 + offset_x) * CConfig::SizeScale, pos_Y + 5 * CConfig::SizeScale, pos_X + (15 + offset_x) * CConfig::SizeScale, pos_Y + 6 * CConfig::SizeScale);
}
// -----------------------------------------------------------------------------------


// ----------------------------- ����� ������ �� ������ ����� ----------------------------------------------
//�����������
CCloud::CCloud()
    :pos_X(90 * CConfig::SizeScale), pos_Y(130 * CConfig::SizeScale)
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

    CConfig::secondPaleColor.SelectColor(hdc);

    //����
    Rectangle(hdc, pos_X, pos_Y, pos_X + 58 * CConfig::SizeScale, pos_Y + 16 * CConfig::SizeScale);

    //������� ��������
    CConfig::backgroundColor.SelectColor(hdc);

    //������� ����
    Rectangle(hdc, pos_X, pos_Y, pos_X + 6 * CConfig::SizeScale, pos_Y + 11 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 6 * CConfig::SizeScale, pos_Y, pos_X + 16 * CConfig::SizeScale, pos_Y + 7 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 16 * CConfig::SizeScale, pos_Y, pos_X + 20 * CConfig::SizeScale, pos_Y + 6 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 20 * CConfig::SizeScale, pos_Y, pos_X + 23 * CConfig::SizeScale, pos_Y + 4 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 23 * CConfig::SizeScale, pos_Y, pos_X + 25 * CConfig::SizeScale, pos_Y + 3 * CConfig::SizeScale);

    Rectangle(hdc, pos_X + 38 * CConfig::SizeScale, pos_Y, pos_X + 40 * CConfig::SizeScale, pos_Y + 2 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 40 * CConfig::SizeScale, pos_Y, pos_X + 43 * CConfig::SizeScale, pos_Y + 5 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 43 * CConfig::SizeScale, pos_Y, pos_X + 47 * CConfig::SizeScale, pos_Y + 6 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 47 * CConfig::SizeScale, pos_Y, pos_X + 49 * CConfig::SizeScale, pos_Y + 7 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 49 * CConfig::SizeScale, pos_Y, pos_X + 52 * CConfig::SizeScale, pos_Y + 8 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 51 * CConfig::SizeScale, pos_Y, pos_X + 55 * CConfig::SizeScale, pos_Y + 11 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 55 * CConfig::SizeScale, pos_Y, pos_X + 58 * CConfig::SizeScale, pos_Y + 13 * CConfig::SizeScale);

    //������ ������
    Rectangle(hdc, pos_X + 2 * CConfig::SizeScale, pos_Y + 13 * CConfig::SizeScale, pos_X + 54 * CConfig::SizeScale, pos_Y + 14 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 8 * CConfig::SizeScale, pos_Y + 9 * CConfig::SizeScale, pos_X + 49 * CConfig::SizeScale, pos_Y + 14 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 42 * CConfig::SizeScale, pos_Y + 8 * CConfig::SizeScale, pos_X + 46 * CConfig::SizeScale, pos_Y + 9 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 39 * CConfig::SizeScale, pos_Y + 7 * CConfig::SizeScale, pos_X + 42 * CConfig::SizeScale, pos_Y + 9 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 35 * CConfig::SizeScale, pos_Y + 8 * CConfig::SizeScale, pos_X + 39 * CConfig::SizeScale, pos_Y + 9 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 28 * CConfig::SizeScale, pos_Y + 2 * CConfig::SizeScale, pos_X + 35 * CConfig::SizeScale, pos_Y + 9 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 35 * CConfig::SizeScale, pos_Y + 3 * CConfig::SizeScale, pos_X + 37 * CConfig::SizeScale, pos_Y + 6 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 22 * CConfig::SizeScale, pos_Y + 6 * CConfig::SizeScale, pos_X + 23 * CConfig::SizeScale, pos_Y + 9 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 23 * CConfig::SizeScale, pos_Y + 5 * CConfig::SizeScale, pos_X + 25 * CConfig::SizeScale, pos_Y + 9 * CConfig::SizeScale);
    Rectangle(hdc, pos_X + 25 * CConfig::SizeScale, pos_Y + 4 * CConfig::SizeScale, pos_X + 28 * CConfig::SizeScale, pos_Y + 9 * CConfig::SizeScale);
}
// -----------------------------------------------------------------------------------