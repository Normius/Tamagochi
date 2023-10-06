#pragma once

#include <string>
#include <fstream>

#include "Config.h"

// ----------------------------- Класс панели очков ------------------------
class CScoreboard
{
public:
    CScoreboard();
    void Draw(HDC hdc, RECT& paintArea);
    void Clear(HDC hdc, RECT& paintArea);
    void Redraw();
    void UpdateHighScore();

private:
    void MakeFont();
    void WriteHighScoreToFile();
    void ReadHighScoreFromFile();

    //Настройки для шрифта Consolas
    static constexpr int currentScorePos_X = 665;
    static constexpr int currentAndHighScorePos_Y = 15;
    static constexpr int currentScoreWidth = 110;
    static constexpr int currentScoreHeight = 47;
    static constexpr int spaceBetweenScores = 150;
    static constexpr int spaceBetweenHighAndScores = 100;
    static constexpr int highScorePos_X = currentScorePos_X - spaceBetweenScores;
    static constexpr int highPos_X = highScorePos_X - spaceBetweenHighAndScores;

    HFONT ScoreFont;
    bool showHighScore;
    std::wstring currentScoreStr, highScoreStr;
    std::fstream fs;
    static const std::string filePath;
    wchar_t buff[32];
};
// -----------------------------------------------------------------------------------


// ----------------------------- Класс подсказки по управлению ------------------------
class СControlTip
{
public:
    СControlTip();
    void Draw(HDC hdc, RECT& paintArea);
    void Redraw();
    void Clear(HDC hdc, RECT& paintArea);
    
private:
    //Настройки для шрифта Consolas
    static constexpr int controlFramePos_X = 25;
    static constexpr int controlFramePos_Y = 25;
    static constexpr int controlTextPos_X = 30;
    static constexpr int controlTextPos_Y = 30;
    static constexpr int frameWidth = 360;
    static constexpr int frameHeight = 136;
    static constexpr int verticalSpaceBetweenStr = 20;
    static constexpr int startTextPos_X = 191;
    static constexpr int startTextPos_Y = 170;
    static constexpr int startTextWidth = 420;
    static constexpr int startTextHeight = 22;

    HFONT сontrolTipFont;
};
// -----------------------------------------------------------------------------------

// ----------------------------- Класс подсказки по управлению ------------------------
class CPopupTip
{
public:
    CPopupTip();
    void Draw(HDC hdc, RECT& paintArea);
    void Redraw();
    void Clear(HDC hdc, RECT& paintArea);

private:
    //Настройки для шрифта Consolas
    static constexpr int popupTextPos_X = 390;
    static constexpr int popupTextPos_Y = 200;
    static constexpr int popupFramePos_X = 384;
    static constexpr int popupFramePos_Y = 204;
    static constexpr int width = 30;
    static constexpr int height = 30;

    HFONT popupTipFont;
};
// -----------------------------------------------------------------------------------