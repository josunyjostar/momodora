#include "stdafx.h"
#include "BehabiorDash.h"

#include "BehaviorInAir.h"

void CBehaviorDash::Update(void)
{
	//this->KeyState();
	this->Physics();
	this->Animation();
}

void CBehaviorDash::KeyState(void)
{

}

void CBehaviorDash::Physics(void)
{
	if (!m_pAnimator->IsFlip())//L
		m_pPlayer->m_Rect.x += m_fDashSpeed*fDeltaTime;
	else					  //R
		m_pPlayer->m_Rect.x -= m_fDashSpeed*fDeltaTime;

	CBehaviorOnGround::Update();
}

void CBehaviorDash::Animation(void)
{
	static float fDelayTime = 0.f;
	fDelayTime += fDeltaTime;

	if (m_fTime < fDelayTime)
	{
		fDelayTime = 0.f;

		if (m_pAnimator->GetPlayAniName() == "Momo_Dash")
		{	
			CBehavior* pPreBehavior = m_qBehavior.back();

			if (IsDynamicCast(CBehaviorInAir,pPreBehavior))
				m_eState = STATE_DASH_END_AIR;
			else
				m_eState = STATE_DASH_END;

			m_pPlayer->m_pCollider->SetColliderRect(m_pPlayer->m_tOriColSize);
			return;
		}
	}

	if (m_pAnimator->GetPlayAniName()=="Momo_Dash_Start")
		return;
	else if (m_pAnimator->GetPlayAniName()=="Momo_Dash")
		return;

	m_pAnimator->Play("Momo_Dash_Start");
	m_pPlayer->m_pCollider->SetColliderRect(tSize(48.f,80.f));
	
}
