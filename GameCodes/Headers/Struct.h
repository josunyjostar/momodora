#ifndef struct_h__
#define struct_h__

typedef struct tagPoint
{
	float x;
	float y;

	struct tagPoint operator-() const								{return struct tagPoint(-x, -y);}
	struct tagPoint operator+(const struct tagPoint& _tPoint) const {return struct tagPoint(x+_tPoint.x, y+_tPoint.y);}
	struct tagPoint operator-(const struct tagPoint& _tPoint) const {return struct tagPoint(x-_tPoint.x, y-_tPoint.y);}
	struct tagPoint operator*(float _f) const 						{return struct tagPoint(x*_f,y*_f);}
	struct tagPoint operator/(float _f) const 						{return struct tagPoint(x/_f,y/_f);}
	struct tagPoint& operator+=(const struct tagPoint& _tPoint)		{x+=_tPoint.x;y+=_tPoint.y;return *this;}
	struct tagPoint& operator-=(const struct tagPoint& _tPoint)		{x-=_tPoint.x;y-=_tPoint.y;return *this;}
	struct tagPoint& operator*=(float _f)							{x*=_f;y*=_f;return *this;}
	struct tagPoint& operator/=(float _f)							{x/=_f;y/=_f;return *this;}
	bool operator==(const struct tagPoint& _tPoint) const			{return (_tPoint.x == x && _tPoint.y == y);}
	bool operator!=(const struct tagPoint& _tPoint) const			{return (_tPoint.x != x || _tPoint.y != y);}
	bool operator<(const struct tagPoint& _tPoint) const			{return x < _tPoint.x && y < _tPoint.y;}

	explicit tagPoint():x(0.f), y(0.f) {}
	explicit tagPoint(float _x, float _y):x(_x), y(_y) {}
}tPos, tSize, tOffset, tVector, tVertex;

typedef struct tagRect
{
	float x;	//tPos
	float y;
	float cx;	//tSize
	float cy;
	float ox;	//tOffset	[Min : 0.f & Max : 1.f]
	float oy;

	float	l()	const {return x-cx*ox;}			
	float	r()	const {return x+cx*(1.f-ox);}	
	float	t()	const {return y-cy*oy;}			
	float	b()	const {return y+cy*(1.f-oy);}	

	//Use WinAPI
	LONG	L()	const {return LONG(x-cx*ox);}
	LONG	R()	const {return LONG(x+cx*(1.f-ox));}
	LONG	T()	const {return LONG(y-cy*oy);}
	LONG	B()	const {return LONG(y+cy*(1.f-oy));}

	//Line
	struct tagPoint SP() const {return struct tagPoint(l(), t());}
	struct tagPoint EP() const {return struct tagPoint(r(), b());}

	//tVertex
	struct tagPoint LT() const {return struct tagPoint(l(), t());}
	struct tagPoint RT() const {return struct tagPoint(r(), t());}
	struct tagPoint LB() const {return struct tagPoint(l(), b());}
	struct tagPoint RB() const {return struct tagPoint(r(), b());}

	//tagLine ¤±
	struct tagRect LLine() const {return struct tagRect(LT(), tSize(0.f, cy), tOffset(0.f, 0.f));}
	struct tagRect RLine() const {return struct tagRect(RT(), tSize(0.f, cy), tOffset(0.f, 0.f));}
	struct tagRect TLine() const {return struct tagRect(LT(), tSize(cx, 0), tOffset(0.f, 0.f));}
	struct tagRect BLine() const {return struct tagRect(LB(), tSize(cx, 0), tOffset(0.f, 0.f));}

	//Utils
	struct tagPoint Center() const					{return struct tagPoint((l()+r())*0.5f,(t()+b())*0.5f);}
	struct tagPoint Pos() const 					{return struct tagPoint(x,y);}
	struct tagPoint Size() const 					{return struct tagPoint(cx,cy);}
	struct tagPoint Offset() const					{return struct tagPoint(ox,oy);}
	void SetPos(const struct tagPoint& _Pos)		{x=_Pos.x;y=_Pos.y;}
	void SetPos(float _x, float _y)					{x=_x;y=_y;}
	void SetSize(const struct tagPoint& _Size)		{cx=_Size.x;cy=_Size.y;}
	void SetSize(float _cx, float _cy)				{cx=_cx;cy=_cy;}
	void SetOffset(const struct tagPoint& _Offset)	{ox=_Offset.x;oy=_Offset.y;}
	void SetOffset(float _ox, float _oy)			{ox=_ox;oy=_oy;}

	//tRect Move
	struct tagRect operator+(const struct tagPoint& _Pos) const 	{return struct tagRect(x+_Pos.x, y+_Pos.y,cx,cy,ox,oy);}
	struct tagRect operator-(const struct tagPoint& _Pos) const 	{return struct tagRect(x-_Pos.x, y-_Pos.y,cx,cy,ox,oy);}
	struct tagRect& operator+=(const struct tagPoint& _Pos)			{x+=_Pos.x;y+=_Pos.y;return *this;}
	struct tagRect& operator-=(const struct tagPoint& _Pos)			{x-=_Pos.x;y-=_Pos.y;return *this;}

	//RectReSize
	struct tagRect operator*(float _f) const 	{return struct tagRect(x,y,cx*_f,cy*_f,ox,oy);}
	struct tagRect operator/(float _f) const 	{return struct tagRect(x,y,cx/_f,cy/_f,ox,oy);}
	struct tagRect& operator*=(float _f)		{cx*=_f;cy*=_f;return *this;}
	struct tagRect& operator/=(float _f)		{cx/=_f;cy/=_f;return *this;}

	explicit tagRect():x(0.f), y(0.f), cx(0.f), cy(0.f), ox(0.5f), oy(0.5f) {}
	explicit tagRect(const struct tagPoint& _Pos, const struct tagPoint& _Size, const struct tagPoint& _Offset = struct tagPoint(0.5f, 0.5f))
		:x(_Pos.x), y(_Pos.y), cx(_Size.x), cy(_Size.y), ox(_Offset.x), oy(_Offset.y) {}
	explicit tagRect(float _x, float _y, float _cx, float _cy, float _ox = 0.5f, float _oy = 0.5f)
		:x(_x), y(_y), cx(_cx), cy(_cy), ox(_ox), oy(_oy) {}
}tRect, tLine;

typedef struct floatRect
{
	float l;
	float r;
	float t;
	float b;

	struct tagPoint LT() const {return struct tagPoint(l, t);}
	struct tagPoint RT() const {return struct tagPoint(r, t);}
	struct tagPoint LB() const {return struct tagPoint(l, b);}
	struct tagPoint RB() const {return struct tagPoint(r, b);}

	tLine LLine() const {return tLine(LB(), LT());}
	tLine RLine() const {return tLine(RT(), RB());}
	tLine TLine() const {return tLine(LT(), RT());}
	tLine BLine() const {return tLine(RB(), LB());}

	float w() const {return r-l;}
	float h() const {return b-t;}
	struct tagPoint Center() const {return struct tagPoint(l+(r-l)*0.5f, t+(b-t)*0.5f);}

	floatRect():l(0.f), r(0.f), t(0.f), b(0.f) {}
	floatRect(const struct tagRect& _tRect):l(_tRect.l()), r(_tRect.r()), t(_tRect.t()), b(_tRect.b()) {}
	floatRect(float _l, float _r, float _t, float _b):l(_l), r(_r), t(_t), b(_b) {}
}fRect;

typedef struct tagFramePos
{
	int x,y;
	explicit tagFramePos(void):x(0),y(0){}
	explicit tagFramePos(int _x, int _y):x(_x),y(_y){}
}tFramePos;

enum RENDERING_TYPE
{ RENDER_NORMAL, RENDER_TRANSPARENT, RENDER_ALPHA };

typedef struct tagSprite
{
	char*	pName;
	CImage*	pImage;
	HDC		m_hBackDC;
	HDC		m_hAlphaDC;
	HBITMAP	m_hDBBitmap;
	HBITMAP m_hAlphaBitmap;
	BLENDFUNCTION m_bf;

	int		X;
	int		Y;
	int		Width;
	int		Height;
	int		OX;
	int		OY;

	int		RenderingType;

	void Culling(int& _X, int& _Y, int& _CX, int& _CY, float& _TX, float& _TY, float& _TCX, float& _TCY)
	{
		this;

		_TX = (float)X;
		_TY = (float)Y;
		_TCX = 0.f;
		_TCY = 0.f;
		float ReSizeX = (float)Width/(float)_CX;
		float ReSizeY = (float)Height/(float)_CY;

		if(_X < OX) 
		{
			_TX -= (_X-OX)*ReSizeX;
			_CX += (_X-OX);
			_X = OX;
		}

		if( _X + _CX - OX > WINCX)
		{
			_TCX = (_CX - (WINCX - (_X-OX)))*ReSizeX;
			_CX = WINCX - (_X-OX);
		}

		if(_Y < OY) 
		{
			_TY -= (_Y-OY)*ReSizeY;
			_CY += (_Y-OY);
			_Y = OY;
		}

		if( _Y + _CY - OY > WINCY)
		{
			_TCY = (_CY - (WINCY - (_Y-OY)))*ReSizeY;
			_CY = WINCY - (_Y-OY);
		}
	}

	void Draw(HDC _hDC, int _X, int _Y, int _CX, int _CY)
	{
		float TX, TY, TCX, TCY;
		this->Culling(_X, _Y, _CX, _CY, TX, TY, TCX, TCY);
		int DrawCX = (int)(Width-TX-TCX+X), DrawCY = (int)(Height-TY-TCY+Y);
		switch(RenderingType) {
		case RENDER_NORMAL:		pImage->StretchBlt(_hDC,_X,_Y,_CX,_CY,(int)TX,(int)TY,DrawCX,DrawCY); break;
		case RENDER_TRANSPARENT:pImage->TransparentBlt(_hDC,_X,_Y,_CX,_CY,(int)TX,(int)TY,DrawCX,DrawCY,TRANSPARENT_COLOR); break;
		case RENDER_ALPHA:		pImage->AlphaBlend(_hDC,_X,_Y,_CX,_CY,(int)TX,(int)TY,DrawCX,DrawCY); break;
		}
	}

	void Draw(HDC _hDC, int _X, int _Y)
	{
		float TX, TY, TCX, TCY;
		int CX=Width, CY=Height;
		this->Culling(_X, _Y, CX, CY, TX, TY, TCX, TCY);
		int DrawCX = (int)(Width-TX-TCX+X), DrawCY = (int)(Height-TY-TCY+Y);
		switch(RenderingType) {
		case RENDER_NORMAL:		pImage->StretchBlt(_hDC,_X-OX,_Y-OY,CX,CY,(int)TX,(int)TY,DrawCX,DrawCY); break;
		case RENDER_TRANSPARENT:pImage->TransparentBlt(_hDC,_X-OX,_Y-OY,CX,CY,(int)TX,(int)TY,DrawCX,DrawCY,TRANSPARENT_COLOR); break;
		case RENDER_ALPHA:		pImage->AlphaBlend(_hDC,_X-OX,_Y-OY,CX,CY,(int)TX,(int)TY,DrawCX,DrawCY); break;
		}
	}

	void Draw(HDC _hDC, int _X, int _Y, int _CX, int _CY, BYTE _Alpha)
	{
		float TX, TY, TCX, TCY;
		this->Culling(_X, _Y, _CX, _CY, TX, TY, TCX, TCY);
		int DrawCX = (int)(Width-TX-TCX+X), DrawCY = (int)(Height-TY-TCY+Y);

		pImage->AlphaBlend(_hDC,_X,_Y,_CX,_CY,(int)TX,(int)TY,DrawCX,DrawCY,_Alpha);
	}

	void Draw(HDC _hDC, int _X, int _Y, BYTE _Alpha) 
	{
		float TX, TY, TCX, TCY;
		int CX=Width, CY=Height;
		this->Culling(_X, _Y, CX, CY, TX, TY, TCX, TCY);
		int DrawCX = (int)(Width-TX-TCX+X), DrawCY = (int)(Height-TY-TCY+Y);
	
		pImage->AlphaBlend(_hDC,_X-OX,_Y-OY,(int)CX,(int)CY,(int)TX,(int)TY,DrawCX,DrawCY,_Alpha);
		
	}

	explicit tagSprite(CImage* _Texture, char* _pName, int _X, int _Y, int _Width, int _Height, int _OX, int _OY, int _RenderingType)
		:pImage(_Texture), pName(_pName), X(_X), Y(_Y), Width(_Width), Height(_Height), OX(_OX), OY(_OY), RenderingType(_RenderingType)
	{
		HDC hdc = GetDC(g_hWnd);
		m_hBackDC = CreateCompatibleDC(hdc);
		m_hAlphaDC = CreateCompatibleDC(hdc);
		m_hDBBitmap = CreateCompatibleBitmap(hdc, Width, Height);
		m_hAlphaBitmap = CreateCompatibleBitmap(hdc, Width, Height);
		SelectObject(m_hBackDC, m_hDBBitmap);
		SelectObject(m_hAlphaDC, m_hAlphaBitmap);

		m_bf.BlendOp = AC_SRC_OVER;
		m_bf.BlendFlags = 0;
		m_bf.AlphaFormat = 0;
	}
	~tagSprite()
	{
		DeleteDC(m_hBackDC);
		DeleteDC(m_hAlphaDC);
		DeleteObject(m_hDBBitmap);
		DeleteObject(m_hAlphaBitmap);
	}
}tSprite;

typedef struct tAnimation
{
	char*		pName;
	CImage*		pImageL;
	CImage*		pImageR;
	int			iImageW;

	HDC			m_hBackDC;
	HDC			m_hAlphaDC;
	HBITMAP		m_hDBBitmap;
	HBITMAP		m_hAlphaBitmap;
	BLENDFUNCTION m_bf;

	int			iMaxFrame;
	tFramePos*	pFramePos;
	float*		pFrameDelay;
	int			iWidth;
	int			iHeight;
	int			iOX;
	int			iOY;

	int			RenderingType;

	bool		bRepeat;
	char*		pNextAni;

	void Draw(HDC _hDC, bool _bFlip, int _iFrame, int _X, int _Y, int _CX, int _CY) 
	{
		switch(RenderingType) 
		{
		case RENDER_NORMAL:		
			if(_bFlip) 
			{
				pImageL->StretchBlt(_hDC,_X,_Y,_CX,_CY,
					iImageW - iWidth - pFramePos[_iFrame].x,pFramePos[_iFrame].y,
					iWidth,iHeight);
			}
			else 
			{
				pImageR->StretchBlt(_hDC,_X,_Y,_CX,_CY,
					pFramePos[_iFrame].x,pFramePos[_iFrame].y,
					iWidth,iHeight);
			}
			break;

		case RENDER_TRANSPARENT:
			if(_bFlip) 
			{
				pImageL->TransparentBlt(_hDC,_X,_Y,_CX,_CY,
					iImageW - iWidth - pFramePos[_iFrame].x,pFramePos[_iFrame].y,
					iWidth,iHeight,TRANSPARENT_COLOR);
			}
			else 
			{
				pImageR->TransparentBlt(_hDC,_X,_Y,_CX,_CY,
					pFramePos[_iFrame].x,pFramePos[_iFrame].y,
					iWidth,iHeight,TRANSPARENT_COLOR);
			}
			break;

		case RENDER_ALPHA:
			if(_bFlip) 
			{
				pImageL->AlphaBlend(_hDC,_X,_Y,_CX,_CY,
					iImageW - iWidth - pFramePos[_iFrame].x,pFramePos[_iFrame].y,
					iWidth,iHeight);
			}
			else 
			{
				pImageR->AlphaBlend(_hDC,_X,_Y,_CX,_CY,
					pFramePos[_iFrame].x,pFramePos[_iFrame].y,
					iWidth,iHeight);
			}
			break;
		}
	}

	void Draw(HDC _hDC, bool _bFlip, int _iFrame, int _X, int _Y) 
	{
		switch(RenderingType) 
		{
		case RENDER_NORMAL:		
			if(_bFlip) 
			{
				pImageL->StretchBlt(_hDC,_X+iOX-iWidth,_Y-iOY,iWidth,iHeight,
					iImageW - iWidth - pFramePos[_iFrame].x,pFramePos[_iFrame].y,
					iWidth,iHeight);
			}
			else 
			{
				pImageR->StretchBlt(_hDC,_X-iOX,_Y-iOY,iWidth,iHeight,
					pFramePos[_iFrame].x,pFramePos[_iFrame].y,
					iWidth,iHeight);
			}
			break;

		case RENDER_TRANSPARENT:
			if(_bFlip) 
			{
				pImageL->TransparentBlt(_hDC,_X+iOX-iWidth,_Y-iOY,iWidth,iHeight,
					iImageW - iWidth - pFramePos[_iFrame].x,pFramePos[_iFrame].y,
					iWidth,iHeight,TRANSPARENT_COLOR);
			}
			else 
			{
				pImageR->TransparentBlt(_hDC,_X-iOX,_Y-iOY,iWidth,iHeight,
					pFramePos[_iFrame].x,pFramePos[_iFrame].y,
					iWidth,iHeight,TRANSPARENT_COLOR);
			}
			break;

		case RENDER_ALPHA:
			if(_bFlip)
			{
				pImageL->AlphaBlend(_hDC,_X+iOX-iWidth,_Y-iOY,iWidth,iHeight,
					iImageW - iWidth - pFramePos[_iFrame].x,pFramePos[_iFrame].y,
					iWidth,iHeight);
			}
			else 
			{
				pImageR->AlphaBlend(_hDC,_X-iOX,_Y-iOY,iWidth,iHeight,
					pFramePos[_iFrame].x,pFramePos[_iFrame].y,
					iWidth,iHeight);
			}
			break;
		}
	}

	void Draw(HDC _hDC, bool _bFlip, int _iFrame, int _X, int _Y, int _CX, int _CY, BYTE _Alpha)
	{
		int TX, TY;

		TX = ((_bFlip)?iImageW - iWidth - pFramePos[_iFrame].x:pFramePos[_iFrame].x);
		TY = pFramePos[_iFrame].y;

		((_bFlip)?pImageL:pImageR)->AlphaBlend(_hDC,_X,_Y,_CX,_CY,TX,TY,iWidth,iHeight,_Alpha);
	}

	void Draw(HDC _hDC, bool _bFlip, int _iFrame, int _X, int _Y, BYTE _Alpha) 
	{
		int TX, TY;
		int DX, DY;
		TX = ((_bFlip)?iImageW - iWidth - pFramePos[_iFrame].x:pFramePos[_iFrame].x);
		TY = pFramePos[_iFrame].y;
		DX = ((_bFlip)?_X+iOX-iWidth:_X-iOX);
		DY = _Y-iOY;

		((_bFlip)?pImageL:pImageR)->AlphaBlend(_hDC,DX,DY,iWidth,iHeight,TX,TY,iWidth,iHeight,_Alpha);
	}

	explicit tAnimation(CImage* _LTexture, CImage* _RTexture, char* _pName, int _MaxFrame, tFramePos* _pFramePos, int _Width, int _Height, int _OX, int _OY, int _RenderingType, bool _bRepeat, char* _pNextAni, float* _FrameDelay)
		:pImageL	(_LTexture),
		pImageR		(_RTexture),
		pName		(_pName),
		iMaxFrame	(_MaxFrame),
		pFramePos	(_pFramePos),
		iWidth		(_Width),
		iHeight		(_Height),
		iOX			(_OX),
		iOY			(_OY),
		pFrameDelay	(_FrameDelay),
		RenderingType(_RenderingType),
		bRepeat		(_bRepeat),
		pNextAni	(_pNextAni)
	{
		iImageW = pImageL->GetWidth();
		HDC hdc = GetDC(g_hWnd);
		m_hBackDC = CreateCompatibleDC(hdc);
		m_hAlphaDC = CreateCompatibleDC(hdc);
		m_hDBBitmap = CreateCompatibleBitmap(hdc, iWidth, iHeight);
		m_hAlphaBitmap = CreateCompatibleBitmap(hdc, iWidth, iHeight);
		SelectObject(m_hBackDC, m_hDBBitmap);
		SelectObject(m_hAlphaDC, m_hAlphaBitmap);

		m_bf.BlendOp = AC_SRC_OVER;
		m_bf.BlendFlags = 0;		
		m_bf.AlphaFormat = 0;
	}

	~tAnimation()
	{
		DeleteDC(m_hBackDC);
		DeleteDC(m_hAlphaDC);
		DeleteObject(m_hDBBitmap);
		DeleteObject(m_hAlphaBitmap);
		SAFE_DELETE(pFramePos);
		SAFE_DELETE(pFrameDelay);
	}
}tAni;

class CGameObject;

typedef struct tagCollision_Info 
{
	CGameObject* pObj;
	tPos Pos;
	tVector Vec;

	struct tagCollision_Info():pObj(NULL), Pos(0.f, 0.f), Vec(0.f, 0.f) {}
	struct tagCollision_Info(CGameObject* _pObj):pObj(_pObj), Pos(0.f, 0.f), Vec(0.f, 0.f) {}
}COL_INFO;


#endif // struct_h__
