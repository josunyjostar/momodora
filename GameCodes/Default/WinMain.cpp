// SHOOTING_GAME.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//
#include "stdafx.h"
#include "WinMain.h"
#include "SceneMgr.h"

BOOL				InitInstance(HINSTANCE, int,LPCTSTR);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LPCTSTR lpcszTitle = L"MOMODORA";

	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= NULL;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= lpcszTitle;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));
	RegisterClassEx(&wcex);

	if (!InitInstance (hInstance, nCmdShow,lpcszTitle))
		return FALSE;

	MSG msg;
	msg.message = WM_NULL;

	srand(unsigned(time(NULL)));

	DWORD dwPrevTime;
	DWORD dwCurrentTime;
	dwPrevTime = dwCurrentTime = GetTickCount();

	CSceneMgr&	m_SceneMgr = CSceneMgr::Inst();
	fDeltaTime = 0.016f;

	static TCHAR szTitle[64];
	wsprintf(szTitle, L"Momodora 모작 :지원자 박제영");
	SetWindowText(g_hWnd, szTitle);

	while (msg.message != WM_QUIT)
	{
		dwCurrentTime = GetTickCount();

		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if (dwPrevTime < dwCurrentTime)
		{
			dwPrevTime = dwCurrentTime;
			m_SceneMgr.Update();
		}
	}

	m_SceneMgr.Release();

	return (int) msg.wParam;
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow, LPCTSTR lpcszTitle)
{
	
	HWND hWnd;
	RECT rc = {0,0,WINCX,WINCY};
	AdjustWindowRect(&rc,WS_OVERLAPPEDWINDOW,false);
	g_hInst = hInstance; 

	hWnd = CreateWindow(lpcszTitle, lpcszTitle, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
		400, 200, rc.right - rc.left , rc.bottom - rc.top , NULL, (HMENU)NULL, hInstance, NULL);

	if (!hWnd)
	  return FALSE;

	g_hWnd	= hWnd;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static PAINTSTRUCT ps;

	switch (message)
	{
	case WM_PAINT:
		BeginPaint(hWnd, &ps);

		CRenderMgr::Inst().Paint();

		EndPaint(hWnd, &ps);
		break;
	case WM_SIZING:{
		RECT* r = (RECT*)lParam;

		if (r->right - r->left < WINCX + 16){
			if (wParam == WMSZ_LEFT || wParam == WMSZ_BOTTOMLEFT || wParam == WMSZ_TOPLEFT) 
				r->left = r->right - WINCX - 16;
			if (wParam == WMSZ_RIGHT || wParam == WMSZ_BOTTOMRIGHT || wParam == WMSZ_TOPRIGHT) 
				r->right = r->left + WINCX + 16;
		}
		//Win X MaxSize
		if (r->right - r->left > WINCX + 16){
			if (wParam == WMSZ_LEFT || wParam == WMSZ_BOTTOMLEFT || wParam == WMSZ_TOPLEFT) 
				r->left = r->right - WINCX - 16;
			if (wParam == WMSZ_RIGHT || wParam == WMSZ_BOTTOMRIGHT || wParam == WMSZ_TOPRIGHT) 
				r->right = r->left + WINCX + 16;
		}

		//Win Y tSize Limit
		//Win Y MinSize
		if (r->bottom - r->top < WINCY + 39){
			if (wParam == WMSZ_TOP || wParam == WMSZ_TOPRIGHT || wParam == WMSZ_TOPLEFT)
				r->top = r->bottom - WINCY - 39;
			if (wParam == WMSZ_BOTTOM || wParam == WMSZ_BOTTOMRIGHT || wParam == WMSZ_BOTTOMLEFT)
				r->bottom = r->top + WINCY + 39;
		}
		//Win Y MaxSize
		if (r->bottom - r->top > WINCY + 39){
			if (wParam == WMSZ_TOP || wParam == WMSZ_TOPRIGHT || wParam == WMSZ_TOPLEFT) 
				r->top = r->bottom - WINCY - 39;
			if (wParam == WMSZ_BOTTOM || wParam == WMSZ_BOTTOMRIGHT || wParam == WMSZ_BOTTOMLEFT) 
				r->bottom = r->top + WINCY + 39;
		}

		break;
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

