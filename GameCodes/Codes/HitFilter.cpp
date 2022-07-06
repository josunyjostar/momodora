#include "stdafx.h"
#include "HitFilter.h"

CHitFilter::CHitFilter(void)
:m_pWhiteImage(NULL)
,m_pRedImage(NULL)
,m_fAlpha(0.f)
,m_fAccTime(0.f)
,m_eMode(FM_HIT)
{

}

void CHitFilter::Init(void)
{
	CRenderer* pRenderer = this->AddComponent<CRenderer>();
	pRenderer->SetLayer(LAYER_OBJECT);
	pRenderer->SetZOrder(2);

	m_pWhiteImage = CSpriteMgr::Inst().GetSprite("White")->pImage;
	m_pRedImage = CSpriteMgr::Inst().GetSprite("Red")->pImage;
}

void CHitFilter::Render(HDC _hBackDC)
{
	static bool bChange = false;

	switch(m_eMode)
	{
	case FM_WHITE:
		m_pWhiteImage->StretchBlt(_hBackDC,0,0,WINCX,WINCY,0,0,1,1);
		break;
	case FM_HIT:
		if (bChange)
		{
			bChange = !bChange;
			m_pRedImage->StretchBlt(_hBackDC,0,0,WINCX,WINCY,0,0,1,1);
		}
		else
		{
			bChange = !bChange;
			m_pWhiteImage->StretchBlt(_hBackDC,0,0,WINCX,WINCY,0,0,1,1);
		}
		break;
	case FM_RED:
		m_pRedImage->StretchBlt(_hBackDC,0,0,WINCX,WINCY,0,0,1,1);
		break;
	}
}
