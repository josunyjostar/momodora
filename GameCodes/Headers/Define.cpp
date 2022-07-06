#include "stdafx.h"
#include "Define.h"

HWND			g_hWnd;
HINSTANCE		g_hInst;

float			fDeltaTime;

float	RESIZE  = 0.f;

int		WINCX	= 1280;
int		WINCY	= 720;
int		BGACX	= 1280;
int		BGACY	= 720;

//int		WINCX	= 800;
//int		WINCY	= 600;
//int		BGACX	= 800;
//int		BGACY	= 600;

int		DRAWX	= 0;
int		DRAWY	= 0;

const float  GRAVITY  = 2350.f;

bool		 DEBUG_MODE = false;

COLORREF TRANSPARENT_COLOR	= RGB(255, 0, 255);
COLORREF COLLIDER_COLOR		= RGB(255, 0, 127);
