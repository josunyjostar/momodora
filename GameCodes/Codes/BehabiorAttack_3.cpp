#include "stdafx.h"
#include "BehabiorAttack_3.h"

void CBehaviorAttack_3::Update(void)
{
	this->KeyState();
	this->Physics();
	this->Animation();
}

void CBehaviorAttack_3::KeyState(void)
{
	if (m_pKey->Roll(KEY_DOWN))
	{	
		m_eState = STATE_ROLL;
		m_pEffect->SetActive(false);
		m_pEffect = NULL;
	}
}

void CBehaviorAttack_3::Physics(void)
{
	if (m_eState == STATE_ROLL)
		return;

	if(m_pAnimator->GetFrame() < 6)
	{
		if (!m_pAnimator->IsFlip())//L
			m_pPlayer->m_Rect.x += m_pPlayer->m_fMaxSpeed*fDeltaTime*0.08f;
		else					  //R
			m_pPlayer->m_Rect.x -= m_pPlayer->m_fMaxSpeed*fDeltaTime*0.08f;

		if (m_pAnimator->GetFrame() == 5 && m_bAtkCol)
		{	
			m_bAtkCol = false;
			HITBOX(15,tRect(m_pPlayer->m_Rect.Pos()+tPos(((m_pAnimator->IsFlip())?-88.f:88.f),-50.f), tSize(160.f, 100.f)),0.35f);
		}
	}

	if (m_pEffect)
		m_pEffect->SetPos(m_pPlayer->m_Rect.Pos()+tPos(((m_pAnimator->IsFlip())?-85.f:85.f),-60.f));


	CBehaviorAttack::Physics();
}

void CBehaviorAttack_3::Animation(void)
{
	if (m_eState == STATE_ROLL)
		return;

	if (!m_pAnimator->IsPlay() && m_pAnimator->GetPlayAniName()=="Momo_Attack_03")
	{
		m_eState = STATE_IDLE;
		m_pPlayer->SetPos(m_pPlayer->m_Rect.Pos());

		m_bAtkCol = true;
		m_pEffect = NULL;
		return;
	}

	if (m_pAnimator->GetPlayAniName()=="Momo_Attack_03")
		return;

	m_pAnimator->Play("Momo_Attack_03");
	bool bFilp = m_pAnimator->IsFlip();
	m_pEffect = CAniEffect::Create("Leaf_Attack_03",bFilp,false,255);
	m_pEffect->SetEffectSize(tRect(m_pPlayer->m_Rect.Pos()+tPos(((bFilp)?-110.f:110.f),-60.f),tSize(300.f,140.f)));
}
