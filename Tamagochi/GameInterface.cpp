﻿#include "GameInterface.h"

// ----------------------------- Класс панели очков ------------------------

const std::string CScoreboard::filePath = "HighScore.txt";

//Конструктор
CScoreboard::CScoreboard()
    :ScoreFont(0), currentScoreStr(), highScoreStr(L"00000"), buff{}, showHighScore(true)
{
    //MakeFont(); //Выбор стандартного шрифта через меню Windows

    //Шрифт Consolas
    LOGFONT logFont{};

    logFont.lfHeight = -40;
    logFont.lfWeight = 400;
    logFont.lfOutPrecision = 3;
    logFont.lfClipPrecision = 2;
    logFont.lfQuality = 1;
    logFont.lfPitchAndFamily = 49;
    wcscpy_s(logFont.lfFaceName, L"Consolas");

    ScoreFont = CreateFontIndirect(&logFont);

    ReadHighScoreFromFile();
}
// -----------------------------------------------------------------------------------
 
void CScoreboard::MakeFont()
{
    CHOOSEFONT cf{};
    LOGFONT lf{};
    

    cf.lStructSize = sizeof(CHOOSEFONT);
    cf.lpLogFont = &lf;
    cf.Flags = CF_SCREENFONTS;
    cf.nFontType = SCREEN_FONTTYPE; 

    ChooseFont(&cf);

    HFONT newfont = CreateFontIndirect(cf.lpLogFont);
}


// Метод отрисовки
void CScoreboard::Draw(HDC hdc, RECT& paintArea)
{
    const wchar_t* highStr = L"High";

    SelectObject(hdc, ScoreFont);

    SetBkMode(hdc, TRANSPARENT);

    SetTextColor(hdc, CConfig::mainBrightColor.GetRGBColor());

    swprintf(buff, 32, L"%.5i", CConfig::score);

    currentScoreStr = buff;

    TextOut(hdc, currentScorePos_X, currentAndHighScorePos_Y, currentScoreStr.c_str(), static_cast<int>( wcslen( currentScoreStr.c_str() )));

    if (showHighScore == true)
    {
        SetTextColor(hdc, CConfig::secondPaleColor.GetRGBColor());
        TextOut(hdc, highPos_X, currentAndHighScorePos_Y, highStr, 4);
        TextOut(hdc, highScorePos_X, currentAndHighScorePos_Y, highScoreStr.c_str(), static_cast<int>( wcslen( highScoreStr.c_str() )));
    }
}
// -----------------------------------------------------------------------------------


// Метод очистки
void CScoreboard::Clear(HDC hdc, RECT& paintArea)
{
    CConfig::backgroundColor.SelectColor(hdc);

    Rectangle(hdc, highScorePos_X, currentAndHighScorePos_Y, currentScorePos_X + currentScoreWidth, currentAndHighScorePos_Y + currentScoreHeight);
}
// -----------------------------------------------------------------------------------


// Метод перерисовки
void CScoreboard::Redraw()
{
    RECT rect{};

    rect.left = currentScorePos_X;
    rect.top = currentAndHighScorePos_Y;
    rect.right = rect.left + currentScoreWidth;
    rect.bottom = rect.top + currentScoreHeight;

    InvalidateRect(CConfig::Hwnd, &rect, FALSE);
}
// -----------------------------------------------------------------------------------

// Обновляем рекорд очков
void CScoreboard::UpdateHighScore()
{
    if ( CConfig::score <= std::stoi(highScoreStr) )
        return;

    highScoreStr = currentScoreStr;

    WriteHighScoreToFile();

    RECT rect{};

    rect.left = highPos_X;
    rect.top = currentAndHighScorePos_Y;
    rect.right = highScorePos_X + currentScoreWidth;
    rect.bottom = rect.top + currentScoreHeight;

    InvalidateRect(CConfig::Hwnd, &rect, FALSE);
}
// -----------------------------------------------------------------------------------


// Записываем рекорд очков в файл
void CScoreboard::WriteHighScoreToFile()
{
    fs.open(filePath, std::fstream::out);

    if (!fs.is_open())
        return;
    
    fs << CConfig::score;

    fs.close();
}
// -----------------------------------------------------------------------------------


// Считываем рекорд очков с файла (если файла с рекордом нет, он создаётся)
void CScoreboard::ReadHighScoreFromFile()
{
    fs.open(filePath, std::fstream::in);

    if (!fs.is_open())
        return;

    while (!fs.eof())
    {
        int fileHighScore = 0;

        fs >> fileHighScore;

        swprintf(buff, 32, L"%.5i", fileHighScore);

        highScoreStr = buff;
    }

    fs.close();
}
// -----------------------------------------------------------------------------------


// ----------------------------- Класс подсказки по управлению ------------------------

//Конструктор
СControlTip::СControlTip()
    :сontrolTipFont(0)
{
    //Шрифт Consolas
    LOGFONT logFont{};

    logFont.lfHeight = -18;
    logFont.lfWeight = 400;
    logFont.lfOutPrecision = 3;
    logFont.lfClipPrecision = 2;
    logFont.lfQuality = 1;
    logFont.lfPitchAndFamily = 49;
    wcscpy_s(logFont.lfFaceName, L"Consolas");

    сontrolTipFont = CreateFontIndirect(&logFont);
}
// -----------------------------------------------------------------------------------

// Метод отрисовки
void СControlTip::Draw(HDC hdc, RECT& paintArea)
{
    const wchar_t* StandStr = L"W, стрелка вверх - выпрямиться";
    const wchar_t* moveLeftStr = L"A, стрелка влево - движение влево";
    const wchar_t* CrawlStr = L"S, стрелка вниз - пригнуться";
    const wchar_t* moveRightStr = L"D, стрелка вправо - движение вправо";
    const wchar_t* JumpStr = L"Пробел - прыжок/запустить уровень";
    const wchar_t* ActionStr = L"Е - рестарт после проигрыша";

    SelectObject(hdc, сontrolTipFont);

    SetBkMode(hdc, TRANSPARENT);

    SetTextColor(hdc, CConfig::mainBrightColor.GetRGBColor());

    TextOut( hdc, controlTextPos_X, controlTextPos_Y, StandStr, static_cast<int>(wcslen(StandStr)) );
    TextOut( hdc, controlTextPos_X, controlTextPos_Y + verticalSpaceBetweenStr, moveLeftStr, static_cast<int>(wcslen(moveLeftStr)) );
    TextOut( hdc, controlTextPos_X, controlTextPos_Y + verticalSpaceBetweenStr * 2, CrawlStr, static_cast<int>(wcslen(CrawlStr)) );
    TextOut( hdc, controlTextPos_X, controlTextPos_Y + verticalSpaceBetweenStr * 3, moveRightStr, static_cast<int>(wcslen(moveRightStr)) );
    TextOut( hdc, controlTextPos_X, controlTextPos_Y + verticalSpaceBetweenStr * 4, JumpStr, static_cast<int>(wcslen(JumpStr)) );
    TextOut( hdc, controlTextPos_X, controlTextPos_Y + verticalSpaceBetweenStr * 5, ActionStr, static_cast<int>(wcslen(ActionStr)) );

    CConfig::paleCloudColor.SelectColor(hdc);

    const POINT controlTipFramePoints[5]{ {controlFramePos_X, controlFramePos_Y}, {controlFramePos_X + width, controlFramePos_Y}, {controlFramePos_X + width, controlFramePos_Y + height}, {controlFramePos_X, controlFramePos_Y + height}, {controlFramePos_X, controlFramePos_Y - 1} };

    Polyline(hdc, controlTipFramePoints, 5);
}
// -----------------------------------------------------------------------------------


// Метод очистки
void СControlTip::Clear(HDC hdc, RECT& paintArea)
{
    CConfig::backgroundColor.SelectColor(hdc);

    Rectangle(hdc, controlFramePos_X - 1, controlFramePos_Y - 1, controlFramePos_X + width + 2, controlFramePos_Y + height + 2);
}
// -----------------------------------------------------------------------------------

// Метод перерисовки
void СControlTip::Redraw()
{
    RECT rect{};

    rect.left = controlFramePos_X - 1;
    rect.top = controlFramePos_Y - 1;
    rect.right = rect.left + width + 2;
    rect.bottom = rect.top + height + 2;

    InvalidateRect(CConfig::Hwnd, &rect, FALSE);
}
// -----------------------------------------------------------------------------------


// ----------------------------- Класс всплывающей подсказки ------------------------

//Конструктор
CPopupTip::CPopupTip()
    :popupTipFont(0)
{
    //Шрифт Consolas
    LOGFONT logFont{};

    logFont.lfHeight = -30;
    logFont.lfWeight = 400;
    logFont.lfOutPrecision = 3;
    logFont.lfClipPrecision = 2;
    logFont.lfQuality = 1;
    logFont.lfPitchAndFamily = 49;
    wcscpy_s(logFont.lfFaceName, L"Consolas");

    popupTipFont = CreateFontIndirect(&logFont);
}
// -----------------------------------------------------------------------------------

// Метод отрисовки
void CPopupTip::Draw(HDC hdc, RECT& paintArea)
{
    const wchar_t* popupStr = L"E";

    SelectObject(hdc, popupTipFont);

    SetBkMode(hdc, TRANSPARENT);

    SetTextColor(hdc, CConfig::mainBrightColor.GetRGBColor());

    TextOut(hdc, popupTextPos_X, popupTextPos_Y, popupStr, static_cast<int>(wcslen(popupStr)));

    CConfig::paleCloudColor.SelectColor(hdc);

    const POINT popupTipFramePoints[5]{ {popupFramePos_X, popupFramePos_Y}, {popupFramePos_X + width, popupFramePos_Y}, {popupFramePos_X + width, popupFramePos_Y + height}, {popupFramePos_X, popupFramePos_Y + height}, {popupFramePos_X, popupFramePos_Y - 1} };

    Polyline(hdc, popupTipFramePoints, 5);
}
// -----------------------------------------------------------------------------------


// Метод очистки
void CPopupTip::Clear(HDC hdc, RECT& paintArea)
{
    CConfig::backgroundColor.SelectColor(hdc);

    Rectangle(hdc, popupFramePos_X - 1, popupFramePos_Y - 1, popupFramePos_X + width + 2, popupFramePos_Y + height + 2);
}
// -----------------------------------------------------------------------------------

// Метод перерисовки
void CPopupTip::Redraw()
{
    RECT rect{};

    rect.left = popupFramePos_X - 1;
    rect.top = popupFramePos_Y - 1;
    rect.right = rect.left + width + 2;
    rect.bottom = rect.top + height + 2;

    InvalidateRect(CConfig::Hwnd, &rect, FALSE);
}
// -----------------------------------------------------------------------------------
