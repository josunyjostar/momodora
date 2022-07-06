#include "stdafx.h"
#include "BehabiorRoll.h"

void CBehaviorRoll::Update(void)
{
	//this->KeyState();
	this->Physics();
	this->Animation();
}

void CBehaviorRoll::KeyState(void)
{

}

void CBehaviorRoll::Physics(void)
{
	this->Gravity();

	if (!m_pAnimator->IsFlip())//L
		m_pPlayer->m_Rect.x += m_pPlayer->m_fMaxSpeed*fDeltaTime;
	else					  //R
		m_pPlayer->m_Rect.x -= m_pPlayer->m_fMaxSpeed*fDeltaTime;

	static float fPrevPosY = m_pPlayer->m_Rect.Pos().y;
	fPrevPosY = m_pPlayer->m_Rect.Pos().y;

	if (CCollisionMgr::Inst().WallColCheck(m_pPlayer->m_pCollider, GetVector(m_pPlayer->m_PrevPos, m_pPlayer->m_Rect.Pos())))
	{
		if (fPrevPosY != m_pPlayer->m_Rect.y)
		{
			if(m_pPlayer->m_fVelocity < -700.f && fPrevPosY > m_pPlayer->m_Rect.y)	
			{
				m_eState = STATE_FALL;
				m_pPlayer->m_pCollider->SetColliderRect(m_pPlayer->m_tOriColSize);
				m_pPlayer->m_fVelocity = 0.f;
			}
		}
	}
}

void CBehaviorRoll::Animation(void)
{
	if (!m_pAnimator->IsPlay())
	{	
		if (m_pPlayer->m_fVelocity > 200.f)
			m_eState = STATE_IDLE;
		else
			m_eState = STATE_FALL;

		m_pPlayer->m_pCollider->SetColliderRect(m_pPlayer->m_tOriColSize);
		return;
	}

	if (m_pAnimator->GetPlayAniName()=="Momo_Roll")
		return;

	m_pAnimator->Play("Momo_Roll");
	m_pPlayer->m_pCollider->SetColliderRect(tSize(40.f,48.f));
}
