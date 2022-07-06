#include "stdafx.h"
#include "BehabiorFall.h"

void CBehaviorFall::Update(void)
{
	this->KeyState();
	this->Physics();
	this->Animation();
}

void CBehaviorFall::KeyState(void)
{
	static const float fMaxSpeed = 450.f;

	if (m_pKey->Attack(KEY_DOWN))
	{
		CBehavior* pPreAction = m_qBehavior.back();
		if (pPreAction->GetRTTI()->GetClassName() == "CBehaviorJump")
		{
			m_eState = STATE_ATK_INAIR;
			return;
		}
	}
	else if (!m_pKey->Left())
	{	
		m_pAnimator->SetFlipX(true);

		this->DoubleJump();

		m_pPlayer->m_fSpeed -= m_pPlayer->m_fAccel*fDeltaTime;
		if(m_pPlayer->m_fSpeed < -fMaxSpeed) 
			m_pPlayer->m_fSpeed =  -fMaxSpeed;
		m_pPlayer->m_Rect.x += m_pPlayer->m_fSpeed*fDeltaTime;
	}
	else if(!m_pKey->Right())
	{	
		m_pAnimator->SetFlipX(false);

		this->DoubleJump();
	
		m_pPlayer->m_fSpeed += m_pPlayer->m_fAccel*fDeltaTime;
		if(m_pPlayer->m_fSpeed > fMaxSpeed) 
			m_pPlayer->m_fSpeed = fMaxSpeed;
		m_pPlayer->m_Rect.x += m_pPlayer->m_fSpeed*fDeltaTime;
	}

	if(m_pKey->m_CommandBuffer[0] == m_pKey->m_CommandBuffer[1] && 
		(m_pKey->Left(KEY_DOWN) || m_pKey->Right(KEY_DOWN)))
	{
		m_eState = STATE_DASH;

		if (m_pKey->m_iFirstKey == VK_LEFT)
			m_pAnimator->SetFlipX(true);
		else if (m_pKey->m_iFirstKey == VK_RIGHT)
			m_pAnimator->SetFlipX(false);

		m_pPlayer->AfterImage(0.08f,0.37f);
		m_pKey->ClearCommandBuffer();

		return;
	}

	this->DoubleJump();
}

void CBehaviorFall::Physics(void)
{
	if (m_eState != STATE_FALL)
		return;

	this->Gravity();

	tPos PrevPos = m_pPlayer->m_Rect.Pos();
	m_bColWall = CCollisionMgr::Inst().WallColCheck(m_pPlayer->m_pCollider,GetVector(m_pPlayer->m_PrevPos, m_pPlayer->m_Rect.Pos()));

	if(m_bColWall)
	{
		m_bColWall = false;
		if(PrevPos.y > m_pPlayer->m_Rect.y)
		{
			m_eState = STATE_IDLE;
			m_pPlayer->m_fVelocity = 0.f;
		}
	}
}

void CBehaviorFall::Animation(void)
{
	if (m_pAnimator->GetPlayAniName()=="Momo_Fall_Start")
		return;
	if (m_pAnimator->GetPlayAniName()=="Momo_Fall")
		return;

	if(m_eState == STATE_ATK_INAIR)
		return;

	m_pAnimator->Play("Momo_Fall_Start");
}
