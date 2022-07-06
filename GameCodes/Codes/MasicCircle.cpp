#include "stdafx.h"
#include "MasicCircle.h"

CMasicCircle::CMasicCircle(void)
:m_fLifeTime(0.f)
,m_fDelayTime(0.f)
,m_pAnimator(NULL)
{

}

void CMasicCircle::Ready_Object(const tRect& _Rect,const float& _fLifeTime)
{
	m_Tag = TAG_EFFECT;

	m_pAnimator = this->AddComponent<CAnimator>();
	m_pAnimator->SetZOrder(3);
	m_pAnimator->SetLayer(LAYER_OBJECT);

	if (_fLifeTime == 0.f)
		m_fLifeTime = m_pAnimator->GetAniPlayTime("MasicCircle2");
	else
		m_fLifeTime	= _fLifeTime+0.005f;

	m_pAnimator->Play("MasicCircle2");

	this->AddComponent<CRenderer>();

	m_Rect		 = _Rect;
	m_pAnimator->SetReSize(true);
	m_pAnimator->SetAlpha(true);
	m_fDelayTime = 0.f;
}

void CMasicCircle::Render(HDC _hBackDC)
{
	m_fDelayTime += fDeltaTime;

	if(m_fDelayTime > m_fLifeTime)
		this->SetActive(false);
	else
		m_pAnimator->SetAlphaVal((BYTE)(255.f* (m_fLifeTime-m_fDelayTime)/(m_fLifeTime)));	
}

void CMasicCircle::Create(const tRect& _Rect,const float& _fLifeTime /*= 0.f*/)
{
	CMasicCircle* pTemp = CGameObject::Create<CMasicCircle>();
	pTemp->Ready_Object(_Rect,_fLifeTime);
}
