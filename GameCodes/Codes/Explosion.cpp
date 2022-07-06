#include "stdafx.h"
#include "Explosion.h"
#include "WhiteFilter.h"

CExplosion::CExplosion(void)
:m_pAnimator(NULL)
,m_fDelayTime(0.f)
,m_fLifeTime(0.f)
,m_bFilter(true)
,m_iFrame(0)
{

}

void CExplosion::Ready_Object(const tPos& _Pos)
{
	static tSize EffectSize(356.f, 356.f);

	m_Tag	= TAG_EFFECT;
	m_Rect	= tRect(_Pos+tPos(0.f,-50.f),EffectSize);

	m_pAnimator = this->AddComponent<CAnimator>();
	m_pAnimator->SetLayer(LAYER_EFFECT);
	m_pAnimator->SetReSize(true);
	m_pAnimator->SetAlpha(false);

	m_pAnimator->Play("Explosion");

	this->AddComponent<CRenderer>();

	m_fDelayTime = 0.f;
	m_fLifeTime = m_pAnimator->GetAniPlayTime("Explosion");

}

void CExplosion::Update(void)
{
	m_iFrame = m_pAnimator->GetFrame();

	if (m_bFilter && 2 == m_iFrame)
	{
		m_bFilter = false;
		HITBOX(50,tRect(m_Rect.Pos(),m_Rect.Size()),m_fLifeTime);
		CWhiteFilter::Create();
	}
}

void CExplosion::Render(HDC _hBackDC)
{
	m_fDelayTime += fDeltaTime;

	if(m_fDelayTime > m_fLifeTime)
	{
		m_bFilter = true;
		this->SetActive(false);
	}
}

void CExplosion::Create(const tPos& _Pos)
{
	CGameObject::Create<CExplosion>()->Ready_Object(_Pos);
}
