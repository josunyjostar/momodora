#include "stdafx.h"
#include "FontMgr.h"
#include "BlackFilter.h"

CFontMgr::CFontMgr(void)
:m_pNameUI(NULL)
,m_pTimeUI(NULL)
,m_pCoinUI(NULL)
,m_pStarUI(NULL)
,m_szName(NULL)
,m_pTimeTxtUI(NULL)
,m_iCoin(0)
,m_iTime(0)
,m_fDelay(0.f)
,m_bStop(true)
{
}

void CFontMgr::Hide(void)
{
	m_pNameUI->Hide();
	m_pTimeUI->Hide();
	m_pCoinUI->Hide();
	m_pStarUI->Hide();
	m_pTimeTxtUI->Hide();
}

void CFontMgr::SetName(char* _pName)
{
	m_szName = _pName;
	m_pNameUI->String(_pName);
}

void CFontMgr::SetCoin(int _iCoin)
{
	m_iCoin = _iCoin;
	m_pCoinUI->Numeric(_iCoin,3);
}

void CFontMgr::SetTime(int _iTime)
{
	m_iTime = _iTime;
	m_pTimeUI->Numeric(_iTime,3);
	m_bStop = false;
}


void CFontMgr::Init(void)
{
	//Name
	CGameObject* pObj = CGameObject::Create<CGameObject>();
	pObj->SetPos(10.f,5.f);
	m_pNameUI = pObj->AddComponent<CFont>();
	m_pNameUI->SetFontSize(20);
	m_pNameUI->SetAlphaType(CFont::FONT_ALPHA_NONE);

	//*
	pObj = CGameObject::Create<CGameObject>();
	pObj->SetPos(90.f,77.f);
	m_pStarUI = pObj->AddComponent<CFont>();
	m_pStarUI->SetFontSize(25);
	m_pStarUI->String("*");
	m_pStarUI->SetAlphaType(CFont::FONT_ALPHA_NONE);

	//COIN
	pObj = CGameObject::Create<CGameObject>();
	pObj->SetPos(120.f,82.f);
	m_pCoinUI = pObj->AddComponent<CFont>();
	m_pCoinUI->SetFontSize(20);
	m_pCoinUI->Numeric(0,3);
	m_pCoinUI->SetAlphaType(CFont::FONT_ALPHA_NONE);


	//Time
	pObj = CGameObject::Create<CGameObject>();
	pObj->SetPos((float)WINCX-((float)WINCX *0.07f),10.f);
	m_pTimeTxtUI = pObj->AddComponent<CFont>();
	m_pTimeTxtUI->SetFontSize(20);
	m_pTimeTxtUI->String("Time");
	m_pTimeTxtUI->SetAlphaType(CFont::FONT_ALPHA_NONE);

	//Time num
	pObj = CGameObject::Create<CGameObject>();
	pObj->SetPos((float)WINCX-((float)WINCX *0.06f),30.f);
	m_pTimeUI = pObj->AddComponent<CFont>();
	m_pTimeUI->SetFontSize(20);
	m_pTimeUI->Numeric(0,3);
	m_pTimeUI->SetAlphaType(CFont::FONT_ALPHA_NONE);

	m_iCoin		= 0;
	m_iTime		= 0;
	m_fDelay	= 0.f;
	m_bStop		= true;
}

void CFontMgr::Update(void)
{
	if (m_bStop)
		return;

	if (m_iTime > 0)
	{
		m_fDelay += fDeltaTime;

		if (m_fDelay >= 1.f)
		{
			m_fDelay = 0.f;
			this->AddTime(-1);
			
			if (m_iTime <= 0)
			{
				m_bStop = true;
				CBlackFilter* pFilter = CGameObject::Create<CBlackFilter>();
				pFilter->SetFilterMode(CBlackFilter::FM_IN);
				this->CreateAlPhaText("YOU DIED",50,tPos(float(WINCX/2)-205,float(WINCY/2)-75),CFont::FONT_ALPHA_IN,90.f,true);
			}
		}
	}
}

CGameObject* CFontMgr::CreateText(char* _pString, int _iFontSize, const tPos& _tPos, bool _bUI /*= false*/)
{
	CGameObject* pObj = CGameObject::Create<CGameObject>();
	pObj->SetPos(_tPos);
	CFont* pTemp = pObj->AddComponent<CFont>();
	pTemp->SetFontSize(_iFontSize);
	pTemp->String(_pString);

	if (!_bUI)
	{
		pTemp->SetUI(false);
		pTemp->SetLayer(LAYER_EFFECT);
	}
	else 
	{
		pTemp->SetUI(true);
		pTemp->SetLayer(LAYER_UI);
	}

	return pObj;
}

CGameObject* CFontMgr::CreateText(int _iNumber, int _iFontSize, const tPos& _tPos, bool _bUI /*= false*/)
{
	CGameObject* pObj = CGameObject::Create<CGameObject>();
	pObj->SetPos(_tPos);
	CFont* pTemp = pObj->AddComponent<CFont>();
	pTemp->SetFontSize(_iFontSize);
	pTemp->Numeric(_iNumber);

	if (!_bUI)
	{
		pTemp->SetUI(false);
		pTemp->SetLayer(LAYER_EFFECT);
	}

	return pObj;
}

CGameObject* CFontMgr::CreateAlPhaText(char* _pString, int _iFontSize, const tPos& _tPos,CFont::FONT_ALPHA_TYPE _eType,
									 float _fInitAlpha,bool _bUI /*= false*/)
{
	CGameObject* pObj = CGameObject::Create<CGameObject>();
	pObj->SetPos(_tPos);
	CFont* pTemp = pObj->AddComponent<CFont>();
	pTemp->SetFontSize(_iFontSize);
	pTemp->String(_pString);
	pTemp->SetAlphaType(_eType);
	pTemp->SetFontAlpha(_fInitAlpha);

	if (!_bUI)
	{
		pTemp->SetUI(false);
		pTemp->SetLayer(LAYER_EFFECT);
	}
	else 
	{
		pTemp->SetUI(true);
		pTemp->SetLayer(LAYER_UI);
	}

	return pObj;
}

void CFontMgr::AddTime(int _iTime)
{
	m_iTime += _iTime;
	m_pTimeUI->Numeric(m_iTime,3);
	m_bStop = false;

}

void CFontMgr::AddCoin(int _iCoin)
{
	m_iCoin += _iCoin;
	m_pCoinUI->Numeric(m_iCoin,3);
}
