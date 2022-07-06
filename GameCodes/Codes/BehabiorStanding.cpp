#include "stdafx.h"
#include "BehabiorStanding.h"

void CBehaviorStanding::Update(void)
{
	if (m_pPlayer->m_fMaxSP > m_pPlayer->m_fSP)
		m_pPlayer->m_fSP += 0.9f;

	this->KeyState();
	this->Physics();
	this->Animation();
}

void CBehaviorStanding::KeyState(void)
{
	if (m_pKey->Left(KEY_PUSH))
	{
		m_pAnimator->SetFlipX(true);
		m_eState = STATE_RUN;
		return;
	}
	else if (m_pKey->Right(KEY_PUSH))
	{
		m_pAnimator->SetFlipX(false);
		m_eState = STATE_RUN;
		return;
	}
	else if (m_pKey->Roll(KEY_DOWN))
	{
		m_eState = STATE_ROLL;
		return;
	}
	else if (m_pKey->Up(KEY_DOWN))
	{
		m_eState = STATE_JUMP;
		m_bDoubleJump = true;
		return;
	}
	else if (m_pKey->Attack(KEY_DOWN))
	{
		m_eState = STATE_ATK_1;
		return;
	}

	if(m_pKey->m_CommandBuffer[0] == m_pKey->m_CommandBuffer[1] && 
		(m_pKey->Left(KEY_DOWN) || m_pKey->Right(KEY_DOWN)))
	{
		m_eState = STATE_DASH;

		if (m_pKey->m_iFirstKey == VK_LEFT)
			m_pAnimator->SetFlipX(true);
		else if (m_pKey->m_iFirstKey == VK_RIGHT)
			m_pAnimator->SetFlipX(false);

		m_pPlayer->AfterImage(0.09f,0.45f);
		m_pKey->ClearCommandBuffer();

		return;
	}

	if (m_pKey->IsDown(VK_TAB))
	{
		m_pPlayer->m_fVelocity += 800.f;
	}
}

void CBehaviorStanding::Physics(void)
{
	if (STATE_JUMP == m_eState)
	{	
		m_pPlayer->m_fVelocity = 900.f;
		return;
	}

	this->Gravity();

	m_pPlayer->m_fSpeed = 0.f;

	static tPos PrePos;
	PrePos = m_pPlayer->m_Rect.Pos();

	if(!CCollisionMgr::Inst().WallColCheck(m_pPlayer->m_pCollider, GetVector(m_pPlayer->m_PrevPos, m_pPlayer->m_Rect.Pos())))
	{
	}
	else if (PrePos.y != m_pPlayer->m_Rect.y)
	{
		if ( (m_pPlayer->m_fVelocity < 0.f && PrePos.y > m_pPlayer->m_Rect.y) 
			|| (m_pPlayer->m_fVelocity >= 0.f && PrePos.y < m_pPlayer->m_Rect.y) )
		{
			m_pPlayer->m_fVelocity = 0.f;
		}
	}
}

void CBehaviorStanding::Animation(void)
{
	if (m_pAnimator->GetPlayAniName()=="Momo_Idle")
		return;

	m_pAnimator->Play("Momo_Idle");

}
