#include "stdafx.h"
#include "Font.h"

void CFont::Hide(void)
{
	m_iLayer = LAYER_BGA;
	m_iZOrder = 5;
}

void CFont::Init(void)
{
	m_iLayer = LAYER_UI;
	m_pFont = CAnimationMgr::Inst().GetAni("Font");
}

void CFont::Release(void)
{
	delete[] m_pIndex;
	m_pIndex = NULL;
}

void CFont::Render(HDC _hbackDC)
{
	if (!m_pIndex)
		return;

	tRect rc = m_pGameObject->GetRect();

	static float f =0.f;

	switch(m_eAlphaType)
	{
	case FONT_ALPHA_IN:
		m_fFontAlpha += 70.f*fDeltaTime;
		if (m_fFontAlpha > 250.f)
			m_fFontAlpha = 250.f;
		break;
	case FONT_ALPHA_OUT:
		m_fFontAlpha -= 70.f*fDeltaTime;
		if (m_fFontAlpha < 5.f)
			this->SetActive(false);
		break;
	case FONT_ALPHA_INOUT:
		m_fAccTime += fDeltaTime*m_fRate;
		f = (sinf(D2R(m_fAccTime*180.f-90.f))+1.f)*0.5f;
		m_fFontAlpha = 10.f + (255.f- 10.f) * f;
		break;
	case FONT_ALPHA_NONE:
		m_fFontAlpha = 240.f;
		break;
	}

	for(int i=0; i < m_iSize ; ++i)
	{
		if (m_bUIFont)
		{
			m_pFont->pImageR->AlphaBlend(_hbackDC,
				rc.L() + m_iFontSize*i,
				rc.T(),
				m_iFontSize,
				m_iFontSize,
				m_pFont->pFramePos[m_pIndex[i]].x,
				m_pFont->pFramePos[m_pIndex[i]].y,
				m_pFont->iWidth,
				m_pFont->iHeight,
				(BYTE)(m_fFontAlpha));
		}
		else 
		{
			m_pFont->pImageR->AlphaBlend(_hbackDC,
				rc.L() + m_iFontSize*i - DRAWX,
				rc.T() - DRAWY,
				m_iFontSize,
				m_iFontSize,
				m_pFont->pFramePos[m_pIndex[i]].x,
				m_pFont->pFramePos[m_pIndex[i]].y,
				m_pFont->iWidth,
				m_pFont->iHeight,
				(BYTE)(m_fFontAlpha));
		}	
	}
}

void CFont::Numeric(int _iNumber)
{
	if (_iNumber <= 0)
	{
		this->Numeric(0,1);
		return;
	}

	int n = 0;
	int t = _iNumber;

	while(t)
	{
		t /= 10;
		++n;
	}

	this->Numeric(_iNumber,n);

}

void CFont::Numeric(int _iNumber ,int _iSize)
{
	this->ReSize(_iSize);

	for (int i=0; i < m_iSize ; ++i)
	{
		int p = (int)pow(10.f,m_iSize - i -1); //*p - num of place
		int n = _iNumber/p;
		_iNumber -= p*n;

		m_pIndex[i] = n;
	}
}

void CFont::String(char* _pString)
{
	this->String(_pString,strlen(_pString));
}

void CFont::String(char* _pString, int _iStrlen)
{
	this->ReSize(_iStrlen);

	for (int i = 0; i < m_iSize ; ++i)
	{
		if ('0' <= _pString[i] && '9' >= _pString[i])
			m_pIndex[i] = _pString[i] - '0';
		else if('a' <= _pString[i] && 'z' >= _pString[i])
			m_pIndex[i] = _pString[i] - 'a' + 10;
		else if('A' <= _pString[i] && 'Z' >= _pString[i])
			m_pIndex[i] = _pString[i] - 'A' + 10;
		else if('@' == _pString[i])
			m_pIndex[i] = 36;
		else if('*' == _pString[i])
			m_pIndex[i] = 37;
		else if(' ' == _pString[i])
			m_pIndex[i] = 39;
		else if('-' == _pString[i])
			m_pIndex[i] = 40;
		else if('.' == _pString[i])
			m_pIndex[i] = 38;
		else if('!' == _pString[i])
			m_pIndex[i] = 43;
		else m_pIndex[i] = 0;
	}
}

void CFont::ReSize(int _iSize)
{
	if (m_iSize != _iSize)
	{
		this->Release();

		m_iSize = _iSize;
		m_pIndex = new int[m_iSize];
	}
}
