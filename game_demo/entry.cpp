//------------------------------
//      entry.cpp
//		10/16/2019       created
//		10/16/2019		 modified
//		by liuxi
//-------------------------------
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "Windowscodecs")
#include <windows.h>
#include "game.h"

using namespace game;

LRESULT __stdcall WndProcedure(HWND hWnd, unsigned message, WPARAM wParam, LPARAM lParam);
// functions
int __stdcall wWinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, wchar_t * lpCmdLine, int iCmdShow)
{
	SetProcessDPIAware();
	wchar_t name[] = L"D2DApp";
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = &WndProcedure;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = name;
	wcex.hIconSm = wcex.hIcon;
	if (!RegisterClassEx(&wcex))
	{
		return -1;
	}
	HWND hWnd = NULL;
	hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, name, L"d2dApp", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);
	long hResult = CoInitialize(NULL);
	//init_d2d(hWnd);
	Game::getSingleton()->initialize(hWnd);
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				break;
			}
		}
		if (!Game::getSingleton()->frame())
		{
			break;
		}
	}
	CoUninitialize();
	return msg.wParam;
}

LRESULT __stdcall WndProcedure(HWND hWnd, unsigned message, WPARAM wParam, LPARAM lParam)
{
	HDC hDC = NULL;
	PAINTSTRUCT ps;
	switch (message)
	{
	case WM_CREATE:
	{
		return 0;
	}
	case WM_DESTROY:
	{
		Game::destroySingleton();
		PostQuitMessage(0);
		return 0;
	}
	}
	return Game::getSingleton()->processEvent(hWnd, message, wParam, lParam);
}
