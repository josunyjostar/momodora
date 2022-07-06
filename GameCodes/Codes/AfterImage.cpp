#include "stdafx.h"
#include "AfterImage.h"

CAfterImage::CAfterImage(void)
:m_fLifeTime(0.f)
,m_fDelayTime(0.f)
,m_pImageName(NULL)
,m_pAni(NULL)
,m_bFlip(false)
,m_iFrame(0)
{

}

void CAfterImage::Init(char* _pImageName, bool _bFlip, int _iFrame, float _fLifeTime, tRect _Rect)
{
	m_Tag = TAG_EFFECT;

	this->AddComponent<CRenderer>();

	m_Rect		 = _Rect;
	m_pAni		 = CAnimationMgr::Inst().GetAni(_pImageName);
	m_pImageName = _pImageName;
	m_bFlip		 = _bFlip;
	m_iFrame	 = _iFrame;
	m_fLifeTime	 = _fLifeTime;
	m_fDelayTime = 0.f;

}

void CAfterImage::Render(HDC _hBackDC)
{
	m_fDelayTime += fDeltaTime;

	if(m_fDelayTime > m_fLifeTime)
		this->SetActive(false);
	else
		m_pAni->Draw(_hBackDC, m_bFlip, m_iFrame,
		m_Rect.L() - DRAWX,
		m_Rect.T() - DRAWY,
		(int)m_Rect.cx,
		(int)m_Rect.cy, (BYTE)(230.f * (m_fLifeTime-m_fDelayTime)/m_fLifeTime));
}

void CAfterImage::Create(char* _pImageName, bool _bFlip, int _iFrame, float _fLifeTime, tRect _Rect)
{
	CAfterImage* pTemp = CGameObject::Create<CAfterImage>();
	pTemp->Init(_pImageName,_bFlip,_iFrame,_fLifeTime,_Rect);
}
