// Tamagochi.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Main.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TAMAGOCHI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TAMAGOCHI));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TAMAGOCHI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    //------------------------------------------ Цвет фона окна  ----------------------------------------
    wcex.hbrBackground  = CreateSolidBrush(RGB(97, 121, 107));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TAMAGOCHI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   RECT windowRect;
   windowRect.left = 0;
   windowRect.top = 0;
   windowRect.right = 800;
   windowRect.bottom = 600;

   AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, TRUE);

   //  ------------------------------------------- Создание окна -------------------------------------------
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, nullptr, nullptr, hInstance, nullptr);

   if (hWnd == 0)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

// ----------------------------- Очистка фона для перерисовки ----------------------------------------------
void ClearLegsBackground(HDC hdc, int pos_x, int pos_y)
{
    HPEN backgroundPen = CreatePen(PS_SOLID, 0, RGB(97, 121, 107));
    HBRUSH backgroundBrush = CreateSolidBrush(RGB(97, 121, 107));

    //Очищаем фон ног
    SelectObject(hdc, backgroundPen);
    SelectObject(hdc, backgroundBrush);
    //Левая нога
    Rectangle(hdc, pos_x + 14, pos_y + 38, pos_x + 20, pos_y + 46);

    //Правая нога
    Rectangle(hdc, pos_x + 24, pos_y + 38, pos_x + 30, pos_y + 46);
}

// ----------------------------- Очистка фона для перерисовки влево ----------------------------------------------
void ClearReverseLegsBackground(HDC hdc, int pos_x, int pos_y)
{
    HPEN backgroundPen = CreatePen(PS_SOLID, 0, RGB(97, 121, 107));
    HBRUSH backgroundBrush = CreateSolidBrush(RGB(97, 121, 107));

    //int reverseoffset = 48;
    int reverseoffset = 64;

    //Очищаем фон ног
    SelectObject(hdc, backgroundPen);
    SelectObject(hdc, backgroundBrush);
    //Левая нога
    Rectangle(hdc, pos_x + (reverseoffset - 14), pos_y + 38, pos_x + (reverseoffset - 20), pos_y + 46);

    //Правая нога
    Rectangle(hdc, pos_x + (reverseoffset - 24), pos_y + 38, pos_x + (reverseoffset - 30), pos_y + 46);
}

// ----------------------------- Отрисовка ног стоя ----------------------------------------------
void DrawStandingLegs(HDC hdc, int pos_x, int pos_y)
{
    HPEN characterPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
    HBRUSH characterBrush = CreateSolidBrush(RGB(0, 0, 0));

    ClearLegsBackground(hdc, pos_x, pos_y);

    //Рисуем ноги
    SelectObject(hdc, characterPen);
    SelectObject(hdc, characterBrush);

    //Левая нога
    Rectangle(hdc, pos_x + 14, pos_y + 38, pos_x + 17, pos_y + 46);
    Rectangle(hdc, pos_x + 17, pos_y + 44, pos_x + 20, pos_y + 46);

    //Правая нога
    Rectangle(hdc, pos_x + 24, pos_y + 38, pos_x + 27, pos_y + 46);
    Rectangle(hdc, pos_x + 27, pos_y + 44, pos_x + 30, pos_y + 46);
}

// ----------------------------- Отрисовка ног стоя влево ----------------------------------------------
void DrawReverseStandingLegs(HDC hdc, int pos_x, int pos_y)
{
    HPEN characterPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
    HBRUSH characterBrush = CreateSolidBrush(RGB(0, 0, 0));

    //int reverseoffset = 48;
    int reverseoffset = 64;

    ClearReverseLegsBackground(hdc, pos_x, pos_y);

    //Рисуем ноги
    SelectObject(hdc, characterPen);
    SelectObject(hdc, characterBrush);

    //Левая нога
    Rectangle(hdc, pos_x + (reverseoffset - 14), pos_y + 38, pos_x + (reverseoffset - 17), pos_y + 46);
    Rectangle(hdc, pos_x + (reverseoffset - 17), pos_y + 44, pos_x + (reverseoffset - 20), pos_y + 46);

    //Правая нога
    Rectangle(hdc, pos_x + (reverseoffset - 24), pos_y + 38, pos_x + (reverseoffset - 27), pos_y + 46);
    Rectangle(hdc, pos_x + (reverseoffset - 27), pos_y + 44, pos_x + (reverseoffset - 30), pos_y + 46);
}

// ----------------------------- Отрисовка ног при первом шаге ----------------------------------------------
void DrawFirstStep(HDC hdc, int pos_x, int pos_y)
{
    HPEN characterPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
    HBRUSH characterBrush = CreateSolidBrush(RGB(0, 0, 0));

    ClearLegsBackground(hdc, pos_x, pos_y);

    //Рисуем ноги
    SelectObject(hdc, characterPen);
    SelectObject(hdc, characterBrush);

    //Левая нога обычно
    Rectangle(hdc, pos_x + 14, pos_y + 38, pos_x + 17, pos_y + 46);
    Rectangle(hdc, pos_x + 17, pos_y + 44, pos_x + 20, pos_y + 46);

    //Правая нога поднятая
    Rectangle(hdc, pos_x + 24, pos_y + 38 - 4, pos_x + 27, pos_y + 46 - 4);
    Rectangle(hdc, pos_x + 27, pos_y + 44 - 4, pos_x + 30, pos_y + 46 - 4);
}

// ----------------------------- Отрисовка ног при первом шаге влево ----------------------------------------------
void DrawReverseFirstStep(HDC hdc, int pos_x, int pos_y)
{
    HPEN characterPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
    HBRUSH characterBrush = CreateSolidBrush(RGB(0, 0, 0));

    //int reverseoffset = 48;
    int reverseoffset = 64;

    ClearReverseLegsBackground(hdc, pos_x, pos_y);

    //Рисуем ноги
    SelectObject(hdc, characterPen);
    SelectObject(hdc, characterBrush);

    //Левая нога обычно
    Rectangle(hdc, pos_x + (reverseoffset - 14), pos_y + 38, pos_x + (reverseoffset - 17), pos_y + 46);
    Rectangle(hdc, pos_x + (reverseoffset - 17), pos_y + 44, pos_x + (reverseoffset - 20), pos_y + 46);

    //Правая нога поднятая
    Rectangle(hdc, pos_x + (reverseoffset - 24), pos_y + 38 - 4, pos_x + (reverseoffset - 27), pos_y + 46 - 4);
    Rectangle(hdc, pos_x + (reverseoffset - 27), pos_y + 44 - 4, pos_x + (reverseoffset - 30), pos_y + 46 - 4);
}

// ----------------------------- Отрисовка ног при втором шаге ----------------------------------------------
void DrawSecondStep(HDC hdc, int pos_x, int pos_y)
{
    HPEN characterPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
    HBRUSH characterBrush = CreateSolidBrush(RGB(0, 0, 0));

    ClearLegsBackground(hdc, pos_x, pos_y);

    //Рисуем ноги
    SelectObject(hdc, characterPen);
    SelectObject(hdc, characterBrush);

    //Левая нога поднятая
    Rectangle(hdc, pos_x + 14, pos_y + 38 - 4, pos_x + 17, pos_y + 46 - 4);
    Rectangle(hdc, pos_x + 17, pos_y + 44 - 4, pos_x + 20, pos_y + 46 - 4);

    //Правая нога обычно
    Rectangle(hdc, pos_x + 24, pos_y + 38, pos_x + 27, pos_y + 46);
    Rectangle(hdc, pos_x + 27, pos_y + 44, pos_x + 30, pos_y + 46);
}

// ----------------------------- Отрисовка ног при втором шаге влево --------------------------------------------
void DrawReverseSecondStep(HDC hdc, int pos_x, int pos_y)
{
    HPEN characterPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
    HBRUSH characterBrush = CreateSolidBrush(RGB(0, 0, 0));

    //int reverseoffset = 48;
    int reverseoffset = 64;

    ClearReverseLegsBackground(hdc, pos_x, pos_y);

    //Рисуем ноги
    SelectObject(hdc, characterPen);
    SelectObject(hdc, characterBrush);

    //Левая нога поднятая
    Rectangle(hdc, pos_x + (reverseoffset - 14), pos_y + 38 - 4, pos_x + (reverseoffset - 17), pos_y + 46 - 4);
    Rectangle(hdc, pos_x + (reverseoffset - 17), pos_y + 44 - 4, pos_x + (reverseoffset - 20), pos_y + 46 - 4);

    //Правая нога обычно
    Rectangle(hdc, pos_x + (reverseoffset  - 24), pos_y + 38, pos_x + (reverseoffset - 27), pos_y + 46);
    Rectangle(hdc, pos_x + (reverseoffset  - 27), pos_y + 44, pos_x + (reverseoffset - 30), pos_y + 46);
}

// ----------------------------- Отрисовка зрачка при стоклновении влево ------------------------------------------
void DrawReverseEye(HDC hdc, int pos_x, int pos_y)
{
    HPEN characterPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
    HBRUSH characterBrush = CreateSolidBrush(RGB(0, 0, 0));

    //int reverseoffset = 48;
    int reverseoffset = 64;
    
    SelectObject(hdc, characterPen);
    SelectObject(hdc, characterBrush);

    //Зрачок при столкновении
    Rectangle(hdc, pos_x + (reverseoffset - 30), pos_y + 4, pos_x + (reverseoffset - 31), pos_y + 7);
}

// ----------------------------- Отрисовка зрачка при стоклновении ------------------------------------------
void DrawEye(HDC hdc, int pos_x, int pos_y)
{
    HPEN characterPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
    HBRUSH characterBrush = CreateSolidBrush(RGB(0, 0, 0));

    SelectObject(hdc, characterPen);
    SelectObject(hdc, characterBrush);

    //Зрачок при столкновении
    Rectangle(hdc, pos_x + 30, pos_y + 4, pos_x + 31, pos_y + 7);
}

// ----------------------------- Отрисовка тела в обычном состоянии ----------------------------------------
void DrawStaticDino(HDC hdc, int pos_x, int pos_y)
{
    HPEN characterPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
    HBRUSH characterBrush = CreateSolidBrush(RGB(0, 0, 0));

    HPEN backgroundPen = CreatePen(PS_SOLID, 0, RGB(97, 121, 107));
    HBRUSH backgroundBrush = CreateSolidBrush(RGB(97, 121, 107));

    SelectObject(hdc, characterPen);
    SelectObject(hdc, characterBrush);

    //Тело
    Rectangle(hdc, pos_x + 13, pos_y + 38, pos_x + 33, pos_y + 17);

    //Лапки
    Rectangle(hdc, pos_x + 33, pos_y + 22, pos_x + 38, pos_y + 26);

    //Хвост
    Rectangle(hdc, pos_x + 2, pos_y + 15, pos_x + 13, pos_y + 38);

    //Фоновые пропуски
    SelectObject(hdc, backgroundPen);
    SelectObject(hdc, backgroundBrush);

    //Лапки
    Rectangle(hdc, pos_x + 33, pos_y + 24, pos_x + 36, pos_y + 26);
    
    //Хвост
    Rectangle(hdc, pos_x + 6, pos_y + 14, pos_x + 8, pos_y + 18);
    Rectangle(hdc, pos_x + 2, pos_y + 14, pos_x + 3, pos_y + 18);
    Rectangle(hdc, pos_x + 8, pos_y + 22, pos_x + 10, pos_y + 25);

    //Тело спереди
    Rectangle(hdc, pos_x + 32, pos_y + 33, pos_x + 35, pos_y + 36);
    Rectangle(hdc, pos_x + 30, pos_y + 35, pos_x + 35, pos_y + 38);
    Rectangle(hdc, pos_x + 28, pos_y + 37, pos_x + 35, pos_y + 41);

    //Тело сзади
    Rectangle(hdc, pos_x + 2, pos_y + 30, pos_x + 4, pos_y + 32);
    Rectangle(hdc, pos_x + 2, pos_y + 32, pos_x + 6, pos_y + 34);
    Rectangle(hdc, pos_x + 2, pos_y + 34, pos_x + 8, pos_y + 36);
    Rectangle(hdc, pos_x + 2, pos_y + 36, pos_x + 11, pos_y + 38);


    //На спине
    Rectangle(hdc, pos_x + 8, pos_y + 15, pos_x + 20, pos_y + 19);
    Rectangle(hdc, pos_x + 8, pos_y + 19, pos_x + 18, pos_y + 21);
    Rectangle(hdc, pos_x + 8, pos_y + 21, pos_x + 16, pos_y + 23);
    Rectangle(hdc, pos_x + 8, pos_y + 23, pos_x + 14, pos_y + 25);
}

// ----------------------------- Отрисовка тела в обычном состоянии влево ----------------------------------
void DrawReverseStaticDino(HDC hdc, int pos_x, int pos_y)
{
    HPEN characterPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
    HBRUSH characterBrush = CreateSolidBrush(RGB(0, 0, 0));

    HPEN backgroundPen = CreatePen(PS_SOLID, 0, RGB(97, 121, 107));
    HBRUSH backgroundBrush = CreateSolidBrush(RGB(97, 121, 107));

    int reverseoffset = 48;

    SelectObject(hdc, characterPen);
    SelectObject(hdc, characterBrush);

    //Тело
    Rectangle(hdc, pos_x + (reverseoffset - 13), pos_y + 38, pos_x + (reverseoffset - 33), pos_y + 17);

    //Лапки
    Rectangle(hdc, pos_x + (reverseoffset - 33), pos_y + 22, pos_x + (reverseoffset - 38), pos_y + 26);

    //Хвост
    Rectangle(hdc, pos_x + (reverseoffset - 2), pos_y + 15, pos_x + (reverseoffset - 13), pos_y + 38);

    //Фоновые пропуски
    SelectObject(hdc, backgroundPen);
    SelectObject(hdc, backgroundBrush);

    //Лапки
    Rectangle(hdc, pos_x + (reverseoffset - 33), pos_y + 24, pos_x + (reverseoffset - 36), pos_y + 26);

    //Хвост
    Rectangle(hdc, pos_x + (reverseoffset - 6), pos_y + 14, pos_x + (reverseoffset - 8), pos_y + 18);
    Rectangle(hdc, pos_x + (reverseoffset - 2), pos_y + 14, pos_x + (reverseoffset - 3), pos_y + 18);
    Rectangle(hdc, pos_x + (reverseoffset - 8), pos_y + 22, pos_x + (reverseoffset - 10), pos_y + 25);

    //Тело спереди
    Rectangle(hdc, pos_x + (reverseoffset - 32), pos_y + 33, pos_x + (reverseoffset - 35), pos_y + 36);
    Rectangle(hdc, pos_x + (reverseoffset - 30), pos_y + 35, pos_x + (reverseoffset - 35), pos_y + 38);
    Rectangle(hdc, pos_x + (reverseoffset - 28), pos_y + 37, pos_x + (reverseoffset - 35), pos_y + 41);

    //Тело сзади
    Rectangle(hdc, pos_x + (reverseoffset - 2), pos_y + 32, pos_x + (reverseoffset - 6), pos_y + 34);
    Rectangle(hdc, pos_x + (reverseoffset - 2), pos_y + 34, pos_x + (reverseoffset - 8), pos_y + 36);
    Rectangle(hdc, pos_x + (reverseoffset - 2), pos_y + 30, pos_x + (reverseoffset - 4), pos_y + 32);
    Rectangle(hdc, pos_x + (reverseoffset - 2), pos_y + 36, pos_x + (reverseoffset - 11), pos_y + 38);


    //На спине
    Rectangle(hdc, pos_x + (reverseoffset - 8), pos_y + 15, pos_x + (reverseoffset - 20), pos_y + 19);
    Rectangle(hdc, pos_x + (reverseoffset - 8), pos_y + 19, pos_x + (reverseoffset - 18), pos_y + 21);
    Rectangle(hdc, pos_x + (reverseoffset - 8), pos_y + 21, pos_x + (reverseoffset - 16), pos_y + 23);
    Rectangle(hdc, pos_x + (reverseoffset - 8), pos_y + 23, pos_x + (reverseoffset - 14), pos_y + 25);
}

// ----------------------------- Отрисовка головы влево -----------------------------------------------------
void DrawHead(HDC hdc, int pos_x, int pos_y)
{
    HPEN characterPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
    HBRUSH characterBrush = CreateSolidBrush(RGB(0, 0, 0));

    HPEN backgroundPen = CreatePen(PS_SOLID, 0, RGB(97, 121, 107));
    HBRUSH backgroundBrush = CreateSolidBrush(RGB(97, 121, 107));

    SelectObject(hdc, characterPen);
    SelectObject(hdc, characterBrush);

    //Голова
    Rectangle(hdc, pos_x + 25, pos_y + 2, pos_x + 46, pos_y + 17);

    SelectObject(hdc, backgroundPen);
    SelectObject(hdc, backgroundBrush);

    //Голова
    Rectangle(hdc, pos_x + 36, pos_y + 12, pos_x + 46, pos_y + 14);
    Rectangle(hdc, pos_x + 43, pos_y + 14, pos_x + 46, pos_y + 17);
    Rectangle(hdc, pos_x + 25, pos_y + 1, pos_x + 27, pos_y + 3);
    Rectangle(hdc, pos_x + 45, pos_y + 1, pos_x + 47, pos_y + 3);

    //Глаз
    Rectangle(hdc, pos_x + 29, pos_y + 4, pos_x + 32, pos_y + 7);
}

// ----------------------------- Отрисовка головы ---------------------------------------------------------
void DrawReverseHead(HDC hdc, int pos_x, int pos_y)
{
    HPEN characterPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
    HBRUSH characterBrush = CreateSolidBrush(RGB(0, 0, 0));

    HPEN backgroundPen = CreatePen(PS_SOLID, 0, RGB(97, 121, 107));
    HBRUSH backgroundBrush = CreateSolidBrush(RGB(97, 121, 107));

    int reverseoffset = 64;

    SelectObject(hdc, characterPen);
    SelectObject(hdc, characterBrush);

    //Голова
    Rectangle(hdc, pos_x + (reverseoffset - 25), pos_y + 2, pos_x + (reverseoffset - 46), pos_y + 17);

    SelectObject(hdc, backgroundPen);
    SelectObject(hdc, backgroundBrush);

    //Голова
    Rectangle(hdc, pos_x + (reverseoffset - 36), pos_y + 12, pos_x + (reverseoffset - 46), pos_y + 14);
    Rectangle(hdc, pos_x + (reverseoffset - 43), pos_y + 14, pos_x + (reverseoffset - 46), pos_y + 17);
    Rectangle(hdc, pos_x + (reverseoffset - 25), pos_y + 1, pos_x + (reverseoffset - 27), pos_y + 3);
    Rectangle(hdc, pos_x + (reverseoffset - 45), pos_y + 1, pos_x + (reverseoffset - 47), pos_y + 3);

    //Глаз
    Rectangle(hdc, pos_x + (reverseoffset - 29), pos_y + 4, pos_x + (reverseoffset - 32), pos_y + 7);
}

// ----------------------------- Отрисовка тела в присяде -------------------------------------------------
void DrawCrawlingDino(HDC hdc, int pos_x, int pos_y)
{
    HPEN characterPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
    HBRUSH characterBrush = CreateSolidBrush(RGB(0, 0, 0));

    HPEN backgroundPen = CreatePen(PS_SOLID, 0, RGB(97, 121, 107));
    HBRUSH backgroundBrush = CreateSolidBrush(RGB(97, 121, 107));

    SelectObject(hdc, characterPen);
    SelectObject(hdc, characterBrush);

    //Тело
    Rectangle(hdc, pos_x + 2, pos_y + 1, pos_x + 41, pos_y + 20);

    //Лапы
    Rectangle(hdc, pos_x + 34, pos_y + 20, pos_x + 36, pos_y + 24);
    Rectangle(hdc, pos_x + 35, pos_y + 22, pos_x + 38, pos_y + 24);

    //Рисуем пропуски фоновые
    SelectObject(hdc, backgroundPen);
    SelectObject(hdc, backgroundBrush);

    //Тело спереди
    Rectangle(hdc, pos_x + 38, pos_y + 16, pos_x + 41, pos_y + 18);
    Rectangle(hdc, pos_x + 36, pos_y + 18, pos_x + 41, pos_y + 20);

    //Тело сзади
    Rectangle(hdc, pos_x + 2, pos_y + 10, pos_x + 4, pos_y + 12);
    Rectangle(hdc, pos_x + 2, pos_y + 12, pos_x + 6, pos_y + 14);
    Rectangle(hdc, pos_x + 2, pos_y + 14, pos_x + 8, pos_y + 16);
    Rectangle(hdc, pos_x + 2, pos_y + 16, pos_x + 10, pos_y + 18);
    Rectangle(hdc, pos_x + 2, pos_y + 18, pos_x + 12, pos_y + 20);

    //На спине
    Rectangle(hdc, pos_x + 4, pos_y + 0, pos_x + 41, pos_y + 3);
    Rectangle(hdc, pos_x + 5, pos_y + 2, pos_x + 18, pos_y + 4);
    Rectangle(hdc, pos_x + 7, pos_y + 4, pos_x + 16, pos_y + 5);

    Rectangle(hdc, pos_x + 36, pos_y + 2, pos_x + 41, pos_y + 4);
    Rectangle(hdc, pos_x + 38, pos_y + 4, pos_x + 41, pos_y + 5);
}

// ----------------------------- Отрисовка тела в присяде влево -------------------------------------------------
void DrawReverseCrawlingDino(HDC hdc, int pos_x, int pos_y)
{
    HPEN characterPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
    HBRUSH characterBrush = CreateSolidBrush(RGB(0, 0, 0));

    HPEN backgroundPen = CreatePen(PS_SOLID, 0, RGB(97, 121, 107));
    HBRUSH backgroundBrush = CreateSolidBrush(RGB(97, 121, 107));

    int reverseoffset = 64;

    SelectObject(hdc, characterPen);
    SelectObject(hdc, characterBrush);

    //Тело
    Rectangle(hdc, pos_x + (reverseoffset - 2), pos_y + 1, pos_x + (reverseoffset - 41), pos_y + 20);

    //Лапы
    Rectangle(hdc, pos_x + (reverseoffset - 34), pos_y + 20, pos_x + (reverseoffset - 36), pos_y + 24);
    Rectangle(hdc, pos_x + (reverseoffset - 35), pos_y + 22, pos_x + (reverseoffset - 38), pos_y + 24);

    //Рисуем пропуски фоновые
    SelectObject(hdc, backgroundPen);
    SelectObject(hdc, backgroundBrush);

    //Тело спереди
    Rectangle(hdc, pos_x + (reverseoffset - 38), pos_y + 16, pos_x + (reverseoffset - 41), pos_y + 18);
    Rectangle(hdc, pos_x + (reverseoffset - 36), pos_y + 18, pos_x + (reverseoffset - 41), pos_y + 20);

    //Тело сзади
    Rectangle(hdc, pos_x + (reverseoffset - 2), pos_y + 10, pos_x + (reverseoffset  - 4), pos_y + 12);
    Rectangle(hdc, pos_x + (reverseoffset - 2), pos_y + 12, pos_x + (reverseoffset  - 6), pos_y + 14);
    Rectangle(hdc, pos_x + (reverseoffset - 2), pos_y + 14, pos_x + (reverseoffset  - 8), pos_y + 16);
    Rectangle(hdc, pos_x + (reverseoffset - 2), pos_y + 16, pos_x + (reverseoffset  - 10), pos_y + 18);
    Rectangle(hdc, pos_x + (reverseoffset - 2), pos_y + 18, pos_x + (reverseoffset  - 12), pos_y + 20);

    //На спине
    Rectangle(hdc, pos_x + (reverseoffset  - 4), pos_y + 0, pos_x + (reverseoffset - 41), pos_y + 3);
    Rectangle(hdc, pos_x + (reverseoffset  - 5), pos_y + 2, pos_x + (reverseoffset - 18), pos_y + 4);
    Rectangle(hdc, pos_x + (reverseoffset  - 7), pos_y + 4, pos_x + (reverseoffset - 16), pos_y + 5);

    Rectangle(hdc, pos_x + (reverseoffset  - 36), pos_y + 2, pos_x + (reverseoffset - 41), pos_y + 4);
    Rectangle(hdc, pos_x + (reverseoffset  - 38), pos_y + 4, pos_x + (reverseoffset - 41), pos_y + 5);
}

// ----------------------------- Отрисовка кадра -----------------------------------------------------------
void DrawFrame(HDC hdc)
{// Отрисовка экрана игры
    int pos_X = 0;
    int pos_Y = 0;

    //Драко стоит (влево)
    //DrawReverseStaticDino(hdc, pos_X, pos_Y);
    //DrawReverseHead(hdc, pos_X, pos_Y);
    //DrawReverseStandingLegs(hdc, pos_X, pos_Y);
    //DrawReverseFirstStep(hdc, pos_X, pos_Y);
    //DrawReverseSecondStep(hdc, pos_X, pos_Y);

    //Драко стоит (вправо)
    //DrawStaticDino(hdc, pos_X, pos_Y);
    //DrawHead(hdc, pos_X, pos_Y);
    //DrawStandingLegs(hdc, pos_X, pos_Y);
    //DrawFirstStep(hdc, pos_X + 50, pos_Y);
    //DrawSecondStep(hdc, pos_X + 50, pos_Y);

    //Драко в присяде (вправо)
    //DrawCrawlingDino(hdc, pos_X, pos_Y);
    //DrawHead(hdc, pos_X + 16, pos_Y);     //Смещаем отрисовку головы для приседа
    //DrawStandingLegs(hdc, pos_X, pos_Y - 18);  //Смещаем отрисовку ног для приседа
    //DrawFirstStep(hdc, pos_X, pos_Y - 18);
    //DrawSecondStep(hdc, pos_X, pos_Y - 18);

    //DrawReverseCrawlingDino(hdc, pos_X, pos_Y + 50);
    //DrawReverseHead(hdc, pos_X - 16, pos_Y + 50);
    //DrawReverseStandingLegs(hdc, pos_X, pos_Y - 18 + 50);
    //DrawReverseFirstStep(hdc, pos_X, pos_Y - 18 + 50);
    //DrawReverseSecondStep(hdc, pos_X, pos_Y - 18 + 50);

    bool collision = false;
    if (collision == true)
    { 
        DrawEye(hdc, pos_X, pos_Y);
    }
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;

        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        //  ------------------------------------------------------------------------------- Рисование графики -----------------------------------------------------
        // TODO: Add any drawing code that uses hdc here...

        DrawFrame(hdc);

        EndPaint(hWnd, &ps);
    }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
