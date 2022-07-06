#include "stdafx.h"
#include "AnimationMgr.h"

void CAnimationMgr::AddAni(CImage* _LTexture, CImage* _RTexture, char* _pName, int _MaxFrame, 
						  int _StartX, int _StartY, int _Width, int _Height, int _OX, int _OY, int _NullWidth, int _NullHeight, 
						  int _RenderingType, bool _bRepeat, char* _pNextAni, float* _FrameDelay)
{
	if(!_LTexture) 
		return;
	tAni** dpAni = &m_mapAnimation[_pName];
	if(*dpAni) 
		return;
	if(!_FrameDelay) 
	{
		_FrameDelay = new float[_MaxFrame];
		for(int i = 0; i < _MaxFrame; ++i)
			_FrameDelay[i] = 0.04f;
	}

	tFramePos* pFramePos = new tFramePos[_MaxFrame];

	int x = _StartX;
	int y = _StartY;
	int n = 0;
	int width = _LTexture->GetWidth() - (_Width + _NullWidth) + 1;

	for(int i = 0; i < _MaxFrame; ++i)
	{
		x = _StartX + _Width*(i-n) + _NullWidth*(i-n);

		if(width < x) 
		{
			n = i;
			y += _Height+_NullHeight;	
			x = _StartX;
		}

		pFramePos[i].x = x;
		pFramePos[i].y = y;
	}

	*dpAni = new tAni(_LTexture, _RTexture, _pName, _MaxFrame, pFramePos, _Width, _Height, _OX, _OY,
		_RenderingType, _bRepeat, _pNextAni, _FrameDelay);
}

void CAnimationMgr::Release(void)
{
	map<char*, tAni*>::iterator Iter	 = m_mapAnimation.begin();
	map<char*, tAni*>::iterator Iter_end = m_mapAnimation.end();

	while(Iter != Iter_end)
	{
		SAFE_DELETE(Iter->second);
		++Iter;
	}

	m_mapAnimation.clear();
}
