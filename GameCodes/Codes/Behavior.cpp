#include "stdafx.h"
#include "Behavior.h"

#include "Behavior_Header.inl"

CBehavior::CBehavior(void)
:m_ColMgr(CCollisionMgr::Inst())
{
	m_fpANI[STATE_IDLE] = &CBehavior::Ani_Idel;
	m_fpANI[STATE_RUN]  = &CBehavior::Ani_Run;
	m_fpANI[STATE_ROLL] = &CBehavior::Ani_Roll;
	m_fpANI[STATE_BRAKE] = &CBehavior::Ani_Brake;
	m_fpANI[STATE_JUMP] = &CBehavior::Ani_Jump;
	m_fpANI[STATE_FALL] = &CBehavior::Ani_Fall;
	m_fpANI[STATE_DASH] = &CBehavior::Ani_Dash;
	m_fpANI[STATE_DASH_END] = &CBehavior::Ani_Dash_End;
	m_fpANI[STATE_DASH_END_AIR] = &CBehavior::Ani_Dash_End_Air;
	m_fpANI[STATE_ATK_1] = &CBehavior::Ani_Atk_1;
	m_fpANI[STATE_ATK_2] = &CBehavior::Ani_Atk_2;
	m_fpANI[STATE_ATK_3] = &CBehavior::Ani_Atk_3;
	m_fpANI[STATE_ATK_INAIR] = &CBehavior::Ani_Atk_InAir;
	m_fpANI[STATE_HIT] = &CBehavior::Ani_Hit;
	m_fpANI[STATE_PRAY] = &CBehavior::Ani_Pray;
	m_fpANI[STATE_RUNR] = &CBehavior::Ani_RunR;
}

CBehaviorStanding		CBehavior::Standing;
CBehaviorRun			CBehavior::Run;
CBehaviorBrake			CBehavior::Brake;
CBehaviorRoll			CBehavior::Roll;
CBehaviorJump			CBehavior::Jump;
CBehaviorFall			CBehavior::Fall;
CBehaviorDash			CBehavior::Dash;
CBehaviorDashEnd		CBehavior::DashEnd;
CBehaviorDashEndInAir	CBehavior::DashEnd_InAir;
CBehaviorAttack_1		CBehavior::Atk_1;
CBehaviorAttack_2		CBehavior::Atk_2;
CBehaviorAttack_3		CBehavior::Atk_3;
CBehaviorAttack_InAir	CBehavior::Atk_InAir;
CBehaviorHit			CBehavior::Hit;
CBehaviorPray			CBehavior::Pray;
CBehaviorRunR			CBehavior::RunR;

CAnimator*	CBehavior::m_pAnimator=NULL;
CPlayer*	CBehavior::m_pPlayer=NULL;
CKeyState*	CBehavior::m_pKey=&CKeyState::Inst();

bool		CBehavior::m_bDoubleJump=true;

PLAYER_STATE		CBehavior::m_ePreState=STATE_FALL;
PLAYER_STATE		CBehavior::m_eState=STATE_FALL;
queue<CBehavior*>	CBehavior::m_qBehavior;

void CBehavior::BehaviorTransiton(void)
{
	if (m_ePreState == m_eState)
		return;

	m_qBehavior.push(m_pPlayer->Behavior);

	(this->*m_fpANI[m_eState])();

	m_ePreState = m_eState;

	if(m_qBehavior.size() > 20)
	{
		for (int i=0;i<10;++i)
			m_qBehavior.pop();
	}
}

void CBehavior::Gravity(void)
{
	m_pPlayer->m_fVelocity -= GRAVITY * fDeltaTime;
	m_pPlayer->m_Rect.y	-= m_pPlayer->m_fVelocity * fDeltaTime;
}

void CBehavior::DoubleJump(void)
{
	if(m_pKey->Up(KEY_DOWN) && m_bDoubleJump)
	{
		m_bDoubleJump = false;
		m_eState = STATE_JUMP;
		m_pPlayer->m_fVelocity = 200.f;
		m_pPlayer->m_fVelocity += 400.f;
	}
}

void CBehavior::Ani_Idel(void)
{
	m_pPlayer->Behavior = &this->Standing;
}

void CBehavior::Ani_Run(void)
{
	m_pPlayer->Behavior = &this->Run;
}

void CBehavior::Ani_Roll(void)
{
	m_pPlayer->m_fSP -= 30.f;
	if (m_pPlayer->m_fSP < 0.f)
	{	
		m_pPlayer->m_fSP = 0.f;
		m_eState = m_ePreState;
		return;
	}
	m_pPlayer->Behavior = &this->Roll;
}

void CBehavior::Ani_Brake(void)
{
	m_pPlayer->Behavior = &this->Brake;
}

void CBehavior::Ani_Jump(void)
{
	m_pPlayer->m_fSP -= 10.f;

	if (m_pPlayer->m_fSP < 0.f)
	{	
		m_pPlayer->m_fSP = 0.f;
		m_eState = m_ePreState;
		return;
	}

	m_pPlayer->Behavior = &this->Jump;
}

void CBehavior::Ani_Fall(void)
{
	m_pPlayer->Behavior = &this->Fall;
}

void CBehavior::Ani_Dash(void)
{
	m_pPlayer->m_fSP -= 15.f;

	if (m_pPlayer->m_fSP < 0.f)
	{	
		m_pPlayer->m_fSP = 0.f;
		m_eState = m_ePreState;
		return;
	}

	m_pPlayer->Behavior = &this->Dash;
}

void CBehavior::Ani_Dash_End(void)
{
	m_pPlayer->Behavior = &this->DashEnd;
}

void CBehavior::Ani_Dash_End_Air(void)
{
	m_pPlayer->Behavior = &this->DashEnd_InAir;
}

void CBehavior::Ani_Atk_1(void)
{
	m_pPlayer->Behavior = &this->Atk_1;
}

void CBehavior::Ani_Atk_2(void)
{
	m_pPlayer->Behavior = &this->Atk_2;
}

void CBehavior::Ani_Atk_3(void)
{
	m_pPlayer->Behavior = &this->Atk_3;
}

void CBehavior::Ani_Atk_InAir(void)
{
	m_pPlayer->Behavior = &this->Atk_InAir;
}

void CBehavior::Ani_Hit(void)
{
	m_pPlayer->Behavior = &this->Hit;
}

void CBehavior::Ani_Pray(void)
{
	m_pPlayer->Behavior = &this->Pray;
}

void CBehavior::Ani_RunR(void)
{
	m_pPlayer->Behavior = &this->RunR;
}

