#include "stdafx.h"
#include "BehabiorAttack_InAir.h"

void CBehaviorAttack_InAir::Update(void)
{
	this->KeyState();
	this->Physics();
	this->Animation();
}

void CBehaviorAttack_InAir::KeyState(void)
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

void CBehaviorAttack_InAir::Physics(void)
{
	this->Gravity();

	tPos PrevPos = m_pPlayer->m_Rect.Pos();

	bool bFlip = m_pAnimator->IsFlip();

	if(3 == m_pAnimator->GetFrame() && m_bAtkCol)
	{	
		m_bAtkCol = false;
		HITBOX(m_fAtkPower,tRect(m_pPlayer->m_Rect.Pos()+tPos(((bFlip)?-90.f:90.f),-50.f), tSize(155.f, 100.f)),0.2f);
	}

	if (m_pEffect)
		m_pEffect->SetPos(m_pPlayer->m_Rect.Pos()+tPos(((bFlip)?-83.f:83.f),-30.f));

	if(CCollisionMgr::Inst().WallColCheck(m_pPlayer->m_pCollider,GetVector(m_pPlayer->m_PrevPos, m_pPlayer->m_Rect.Pos())))
	{
		if(PrevPos.y > m_pPlayer->m_Rect.y)
		{
			if(PrevPos.y > m_pPlayer->m_Rect.y) 
			{	
				m_eState = STATE_IDLE;
				m_pEffect = NULL;
				m_bAtkCol = true;
			}

			m_pPlayer->m_fVelocity = 0.f;
		}
	}
}

void CBehaviorAttack_InAir::Animation(void)
{
	if(m_eState == STATE_IDLE)
		return;
	if (!m_pAnimator->IsPlay() && m_pAnimator->GetPlayAniName()=="Momo_Attack_InAir")
	{
		m_eState = STATE_FALL;
		m_pPlayer->SetPos(m_pPlayer->m_Rect.Pos());
		m_pEffect = NULL;
		m_bAtkCol = true;
		return;
	}

	if (m_pAnimator->GetPlayAniName()=="Momo_Attack_InAir")
		return;

	m_pAnimator->Play("Momo_Attack_InAir");

	bool bFilp = m_pAnimator->IsFlip();
	m_pEffect = CAniEffect::Create("Leaf_Attack_InAir",bFilp,false,255);
	m_pEffect->SetEffectSize(tRect(m_pPlayer->m_Rect.Pos()+tPos(((bFilp)?-77.f:74.f),-40.f),tSize(288.f,140.f)));
}
