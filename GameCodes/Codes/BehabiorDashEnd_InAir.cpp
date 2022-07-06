#include "stdafx.h"
#include "BehabiorDashEnd_InAir.h"

void CBehaviorDashEndInAir::Update(void)
{
	this->KeyState();
	this->Physics();
	this->Animation();
}

void CBehaviorDashEndInAir::KeyState(void)
{
	static const float fMaxSpeed = 500.f;

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
}

void CBehaviorDashEndInAir::Physics(void)
{
	this->Gravity();

	tPos PrevPos = m_pPlayer->m_Rect.Pos();
	m_bColWall = CCollisionMgr::Inst().WallColCheck(m_pPlayer->m_pCollider,GetVector(m_pPlayer->m_PrevPos, m_pPlayer->m_Rect.Pos()));

	if(m_bColWall)
	{
		m_bColWall = false;
		if(PrevPos.y > m_pPlayer->m_Rect.y)
		{
			if(PrevPos.y > m_pPlayer->m_Rect.y) 
				m_eState = STATE_IDLE;
		}
	}
}

void CBehaviorDashEndInAir::Animation(void)
{
	if (m_pAnimator->GetPlayAniName()=="Momo_Dash_End_InAir")
		return;

	m_pAnimator->Play("Momo_Dash_End_InAir");
}
