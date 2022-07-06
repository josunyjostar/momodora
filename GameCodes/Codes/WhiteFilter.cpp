#include "stdafx.h"
#include "WhiteFilter.h"

void CWhiteFilter::Init(void)
{
	CRenderer* pRenderer = this->AddComponent<CRenderer>();
	pRenderer->SetLayer(LAYER_OBJECT);
	pRenderer->SetZOrder(0);

	m_pWhiteImage = CSpriteMgr::Inst().GetSprite("White")->pImage;
	m_fAlpha	= 255.f;
	m_fAccTime	= 0.f;
	m_fAlphaRate= 1.f;
}

void CWhiteFilter::Render(HDC _hBackDC)
{
	m_fAccTime += fDeltaTime*3.5f;

	m_fAlphaRate = sin(m_fAccTime);

	m_fAlpha = 255.f * m_fAlphaRate;

	m_pWhiteImage->AlphaBlend(_hBackDC,0,0,WINCX,WINCY,0,0,1,1,(BYTE)m_fAlpha);

	if(m_fAlpha < 3.5f)
		this->SetActive(false);
}

CWhiteFilter* CWhiteFilter::Create()
{
	CWhiteFilter* pWhiteFilter = CGameObject::Create<CWhiteFilter>();
	return pWhiteFilter;
}
