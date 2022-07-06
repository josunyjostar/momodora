#include "stdafx.h"
#include "BehabiorHit.h"

void CBehaviorHit::Update(void)
{
	//this->KeyState();
	this->Physics();
	this->Animation();
}

void CBehaviorHit::KeyState(void)
{

}

void CBehaviorHit::Physics(void)
{
	this->Gravity();

	tPos PrevPos = m_pPlayer->m_Rect.Pos();

	if(m_pAnimator->IsFlip()) 
		m_pPlayer->m_Rect.x += fDeltaTime*230.f;
	else
		m_pPlayer->m_Rect.x -= fDeltaTime*230.f;

	m_fRunTime += fDeltaTime;
	float p = pow(10.f, 5) / m_fRunTime;	

	m_pPlayer->AddPosX(sinf(p+10.f)*5.5f);
	m_pPlayer->AddPosY(cosf(p+5.f)*6.5f);

	m_bColWall = CCollisionMgr::Inst().WallColCheck(m_pPlayer->m_pCollider,GetVector(m_pPlayer->m_PrevPos, m_pPlayer->m_Rect.Pos()));

	if(m_bColWall)
	{
		m_bColWall = false;
		if(PrevPos.y > m_pPlayer->m_Rect.y)
			m_pPlayer->m_fVelocity = 0.f;
	}
}

void CBehaviorHit::Animation(void)
{
	if (!m_pAnimator->IsPlay())
	{	
		m_eState = STATE_FALL;
		m_pPlayer->m_pCollider->SetColliderRect(m_pPlayer->m_tOriColSize);
		m_fRunTime = 0.f;
	}

	if (m_pAnimator->GetPlayAniName()=="Momo_Hit")
		return;

	m_pAnimator->Play("Momo_Hit");
	m_pPlayer->m_bHitEffect = true;
}
