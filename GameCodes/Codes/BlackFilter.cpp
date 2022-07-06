#include "stdafx.h"
#include "BlackFilter.h"

CBlackFilter::ModeFunc CBlackFilter::m_fpModeFunc[] =
{
	&CBlackFilter::ModeIn,
	&CBlackFilter::ModeOut,
	&CBlackFilter::ModeNone,
	&CBlackFilter::ModeInOut
};

void CBlackFilter::Init(void)
{
	CRenderer* pRenderer = this->AddComponent<CRenderer>();
	pRenderer->SetLayer(LAYER_OBJECT);
	pRenderer->SetZOrder(2);

	m_pBlackImage = CSpriteMgr::Inst().GetSprite("Black")->pImage;
}

void CBlackFilter::Render(HDC _hBackDC)
{
	(this->*m_fpModeFunc[m_eMode])();

	m_pBlackImage->AlphaBlend(_hBackDC,0,0,WINCX,WINCY,0,0,1,1,(BYTE)m_fAlpha);
}
