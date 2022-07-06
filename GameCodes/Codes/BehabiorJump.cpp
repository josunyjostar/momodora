#include "stdafx.h"
#include "BehabiorJump.h"

void CBehaviorJump::Update(void)
{
	this->KeyState();
	this->Physics();
	this->Animation();	
}

void CBehaviorJump::KeyState(void)
{
	static const float fMaxSpeed = 400.f;

	if (!m_pKey->Left())
	{	
		m_pAnimator->SetFlipX(true);

		m_pPlayer->m_fSpeed -= m_pPlayer->m_fAccel*fDeltaTime;

		if(m_pPlayer->m_fSpeed < -fMaxSpeed) 
			m_pPlayer->m_fSpeed =  -fMaxSpeed;

		m_pPlayer->m_Rect.x += m_pPlayer->m_fSpeed*fDeltaTime;
	}
	else if(!m_pKey->Right())
	{	
		m_pAnimator->SetFlipX(false);

		m_pPlayer->m_fSpeed += m_pPlayer->m_fAccel*fDeltaTime;

		if(m_pPlayer->m_fSpeed > fMaxSpeed) 
			m_pPlayer->m_fSpeed = fMaxSpeed;

		m_pPlayer->m_Rect.x += m_pPlayer->m_fSpeed*fDeltaTime;
	}

	this->DoubleJump();
}

void CBehaviorJump::Physics(void)
{
	this->Gravity();

	m_bColWall = CCollisionMgr::Inst().WallColCheck(m_pPlayer->m_pCollider, GetVector(m_pPlayer->m_PrevPos, m_pPlayer->m_Rect.Pos()));

	if (m_bColWall)
	{
		m_eState = STATE_FALL;
		m_bColWall = false;
	}
	else if (m_pPlayer->m_fVelocity < 100.f)
		m_eState = STATE_FALL;

}

void CBehaviorJump::Animation(void)
{
	if (m_pAnimator->GetPlayAniName()=="Momo_Jump")
		return;

	m_pAnimator->Play("Momo_Jump");
}
