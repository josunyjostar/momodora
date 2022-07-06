#include "stdafx.h"
#include "BehabiorRun.h"

void CBehaviorRun::Update(void)
{
	if (m_pPlayer->m_fMaxSP > m_pPlayer->m_fSP)
		m_pPlayer->m_fSP += 0.5f;

	this->KeyState();
	this->Physics();
	this->Animation();
}

void CBehaviorRun::KeyState(void)
{
	if (m_pKey->Left(KEY_PUSH))
	{
		m_pAnimator->SetFlipX(true);

		if (m_pKey->Up(KEY_DOWN))
		{
			m_eState = STATE_JUMP;
			m_bDoubleJump = true;
			return;
		}
		else if (m_pKey->Roll(KEY_DOWN))
		{
			m_eState = STATE_ROLL;
			return;
		}
	}
	else if (m_pKey->Right(KEY_PUSH))
	{
		m_pAnimator->SetFlipX(false);

		if (m_pKey->Up(KEY_DOWN))
		{
			m_eState = STATE_JUMP;
			m_bDoubleJump = true;
			return;
		}
		else if (m_pKey->Roll(KEY_DOWN))
		{
			m_eState = STATE_ROLL;
			return;
		}
	}
	else if (m_pKey->Right(KEY_UP) || m_pKey->Left(KEY_UP))
	{
		if (abs(m_pPlayer->m_fSpeed) > 450.f)
		{
			m_eState = STATE_BRAKE;
			return;
		}

		m_eState = STATE_IDLE;
	}
}

void CBehaviorRun::Physics(void)
{

	if (m_pAnimator->IsFlip())//L
	{
		m_pPlayer->m_fSpeed -= m_pPlayer->m_fAccel*fDeltaTime;
		if(m_pPlayer->m_fSpeed < -m_pPlayer->m_fMaxSpeed) 
			m_pPlayer->m_fSpeed = -m_pPlayer->m_fMaxSpeed;
		m_pPlayer->m_Rect.x += m_pPlayer->m_fSpeed*fDeltaTime;
	}
	else					  //R
	{
		m_pPlayer->m_fSpeed += m_pPlayer->m_fAccel*fDeltaTime;

		if(m_pPlayer->m_fSpeed > m_pPlayer->m_fMaxSpeed) 
			m_pPlayer->m_fSpeed = m_pPlayer->m_fMaxSpeed;

		m_pPlayer->m_Rect.x += m_pPlayer->m_fSpeed*fDeltaTime;
	}

	this->Gravity();

	static float fVelocity = 0.f;
	fVelocity	= m_pPlayer->m_fVelocity;

	if(CCollisionMgr::Inst().WallColCheck(m_pPlayer->m_pCollider, GetVector(m_pPlayer->m_PrevPos, m_pPlayer->m_Rect.Pos())))
		m_pPlayer->m_fVelocity = 0.f;	
	else
	{
		if (m_pPlayer->m_fVelocity < -300.f)
			m_eState = STATE_FALL;
	}

	if (m_eState != STATE_RUN)
	{	
		if (STATE_JUMP == m_eState)
			m_pPlayer->m_fVelocity = 900.f;
		else if (STATE_FALL == m_eState)
			m_pPlayer->m_fVelocity = fVelocity;
	}
}

void CBehaviorRun::Animation(void)
{
	if (m_pAnimator->GetPlayAniName()=="Momo_Run_Start")
		return;
	else if (m_pAnimator->GetPlayAniName()=="Momo_Run")
		return;

	m_pAnimator->Play("Momo_Run_Start");
}
