#ifndef define_h__
#define define_h__

#define	CALL_CONV __stdcall
#define PURE = 0
#define SAFE_DELETE(p) if(p){delete p; p=NULL;}
#define MSG_BOX(text) MessageBox(NULL, TEXT(text), NULL, MB_OK)

#define MIN(__VAL1,__VAL2) ((__VAL1<__VAL2)?__VAL1:__VAL2)
#define MAX(__VAL1,__VAL2) ((__VAL1>__VAL2)?__VAL1:__VAL2)
#define SQR(__VAL)		   ((__VAL)*(__VAL))

const int INIT_VAL	= 16843009;
const float PI		= atan(1.f)*4.f;//45° * 4
const float M_E     =  2.71828182845904523536f;

extern HWND			g_hWnd;
extern HINSTANCE	g_hInst;
extern float		fDeltaTime;
extern const float  GRAVITY;

extern float		RESIZE;
extern int			WINCX;
extern int			WINCY;
extern int			BGACX;
extern int			BGACY;
extern int			DRAWX;
extern int			DRAWY;

extern bool			DEBUG_MODE;

extern COLORREF TRANSPARENT_COLOR;
extern COLORREF COLLIDER_COLOR;

//TODO :        아직 하지 않은 일.
//FIXME:        오동작을 일으킨다고 알려진 코드.
//HACK :        아름답지 않은 해결책
//XXX  :        위험! 여기 큰 문제가 있다.
//Textmate :    ESC

#endif // define_h__
