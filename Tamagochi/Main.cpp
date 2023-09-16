// Tamagochi.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Main.h"

#define MAX_LOADSTRING 100

// Global Variables:

//Добавленные глобальные переменные
CEngine Engine;

//Переменные для двойной буферизации изображения (пока не нужны)
HDC FrameDC = 0;
HBITMAP FrameBitmap = 0;
int FrameDCWidth = 0;
int FrameDCHeight = 0;
//------------------------------------------------------


HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

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
	if (!InitInstance(hInstance, nCmdShow))
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

	return (int)msg.wParam;
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

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TAMAGOCHI));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	//------------------------------------------ Цвет фона окна  ----------------------------------------
	wcex.hbrBackground = CConfig::backgroundColor.brush;
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_TAMAGOCHI);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

	RECT windowRect{ 0 };
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

	Engine.InitEngine(hWnd);  //---------------------------- - Инициализация начальных данных----------------------------------------------

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
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
		HDC hdc; //Изначально был в программе, вынес его из секции case
		PAINTSTRUCT ps;

		hdc = BeginPaint(hWnd, &ps);
		//  ------------------------------------------------------------------------------- Рисование графики -----------------------------------------------------
		// TODO: Add any drawing code that uses hdc here...

		//--------------------------- Код для двойной буферизации изображения, если изображение при отрисовке мигает (пока не нужно) (нужна дополнительная очистка фона)
		
		RECT rect;
		GetClientRect(hWnd, &rect); //Получаем прямоугольник клиентской области окна для перерисовки

		int frameDCWidth = rect.right - rect.left;
		int frameDCHeight = rect.bottom - rect.top;

		if (frameDCWidth != FrameDCWidth && frameDCHeight != FrameDCHeight) //если размеры клиентской области окна изменились, то создаём новые объекты FrameDC и FrameBitmap
		{
			if (FrameBitmap != 0)
				DeleteObject(FrameBitmap); //Перед созданием новых объектов удаляем старые, если не равны 0

			if (FrameDC != 0)
				DeleteObject(FrameDC);

			FrameDCWidth = frameDCWidth;
			FrameDCHeight = frameDCHeight;

			FrameDC = CreateCompatibleDC(hdc);
			FrameBitmap = CreateCompatibleBitmap(hdc, FrameDCWidth, FrameDCHeight);

			SelectObject(FrameDC, FrameBitmap);

			CConfig::backgroundColor.SelectColor(FrameDC);
			Rectangle(FrameDC, rect.left, rect.top, rect.right, rect.bottom);
		}

		//Engine.DrawFrame(hdc, ps.rcPaint); //Заменили отрисовку с помощью hdc на FrameDC
		
		Engine.DrawFrame(FrameDC, ps.rcPaint); //Заменили отрисовку с помощью hdc на FrameDC
		BitBlt(hdc, 0, 0, FrameDCWidth, FrameDCHeight, FrameDC, 0, 0, SRCCOPY); //Использется для копирования в hdc из FrameDC, в который мы отрисовываем изображение первоначально

		EndPaint(hWnd, &ps);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN: //Обработка нажатия клавиш
	{
		switch (wParam)
		{
		case VK_LEFT:
			return Engine.OnKey(EKeyType::LeftKey, true);

		case VK_RIGHT:
			return Engine.OnKey(EKeyType::RightKey, true);

		case VK_DOWN:
			return Engine.OnKey(EKeyType::DownKey, true);

		case VK_UP:
			return Engine.OnKey(EKeyType::UpKey, true);

		case VK_SPACE:
			return Engine.OnKey(EKeyType::SpaceKey, true);
		}
		break;
	}

	case WM_KEYUP: //Обработка отжатия клавиш
	{
		switch (wParam)
		{
		case VK_LEFT:
			return Engine.OnKey(EKeyType::LeftKey, false);

		case VK_RIGHT:
			return Engine.OnKey(EKeyType::RightKey, false);

		case VK_DOWN:
			return Engine.OnKey(EKeyType::DownKey, false);

		case VK_UP:
			return Engine.OnKey(EKeyType::UpKey, false);

		case VK_SPACE:
			return Engine.OnKey(EKeyType::SpaceKey, false);
		}
		break;
	}


	case WM_TIMER:
	{
		if (wParam == Engine.TimerId)
		{
			return Engine.OnTimer();
		}
	}
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
