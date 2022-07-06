#include "stdafx.h"
#include "BehabiorBrake.h"

void CBehaviorBrake::Update(void)
{
	if (m_pPlayer->m_fMaxSP > m_pPlayer->m_fSP)
		m_pPlayer->m_fSP += 0.4f;

	//this->KeyState();
	this->Physics();
	this->Animation();
}

void CBehaviorBrake::KeyState(void)
{

}

void CBehaviorBrake::Physics(void)
{	
	this->Gravity();

	if (!m_pAnimator->IsFlip())//L
	{
		m_pPlayer->m_fSpeed = 0.f;
		m_pPlayer->m_Rect.x += m_pPlayer->m_fMaxSpeed*fDeltaTime*0.2f;
	}
	else					  //R
	{
		m_pPlayer->m_fSpeed = 0.f;
		m_pPlayer->m_Rect.x -= m_pPlayer->m_fMaxSpeed*fDeltaTime*0.2f;
	}

	CBehaviorOnGround::Update();

	if (m_ePreState == STATE_RUN)
		if (m_pPlayer->m_fVelocity < 0.f)
			m_eState = STATE_FALL;
	
}

void CBehaviorBrake::Animation(void)
{
	if (!m_pAnimator->IsPlay())
	{	
		m_eState = STATE_IDLE;
		return;
	}

	if (m_pAnimator->GetPlayAniName()=="Momo_Brake")
		return;

	m_pAnimator->Play("Momo_Brake");
}
