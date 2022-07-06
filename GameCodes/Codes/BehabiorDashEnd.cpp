#include "stdafx.h"
#include "BehabiorDashEnd.h"

void CBehaviorDashEnd::Update(void)
{
	this->KeyState();
	this->Physics();
	this->Animation();
}

void CBehaviorDashEnd::KeyState(void)
{
	if (!m_pKey->Left())
	{	
		m_pAnimator->SetFlipX(true);
		m_pPlayer->m_Rect.x += -500.f*fDeltaTime;
	}
	else if(!m_pKey->Right())
	{	
		m_pAnimator->SetFlipX(false);
		m_pPlayer->m_Rect.x += 500.f*fDeltaTime;
	}
}

void CBehaviorDashEnd::Physics(void)
{
	this->Gravity();

	if(!CCollisionMgr::Inst().WallColCheck(m_pPlayer->m_pCollider, GetVector(m_pPlayer->m_PrevPos, m_pPlayer->m_Rect.Pos())))
	{
		if(m_pPlayer->m_PrevPos.y < m_pPlayer->m_Rect.y)
		{
			m_eState = STATE_DASH_END_AIR;
			m_pPlayer->m_fVelocity = 0.f;
		}
	}
}

void CBehaviorDashEnd::Animation(void)
{
	if (!m_pAnimator->IsPlay())
	{	
		if (m_eState != STATE_DASH_END_AIR)
		{	
			m_eState = STATE_IDLE;
			m_pPlayer->SetPos(m_pPlayer->m_Rect.Pos());
		}
		return;
	}

	if (m_pAnimator->GetPlayAniName()=="Momo_Dash_End")
		return;

	m_pAnimator->Play("Momo_Dash_End");
}
