#include "stdafx.h"
#include "BehabiorAttack_2.h"

void CBehaviorAttack_2::Update(void)
{
	this->KeyState();
	this->Physics();
	this->Animation();
}

void CBehaviorAttack_2::KeyState(void)
{
	if (m_pKey->Attack(KEY_DOWN))
		m_bNextAtk = true;
}

void CBehaviorAttack_2::Physics(void)
{
	if(3 < m_pAnimator->GetFrame())
	{
		if (!m_pAnimator->IsFlip())//L
			m_pPlayer->m_Rect.x += m_pPlayer->m_fMaxSpeed*fDeltaTime*0.07f;
		else					  //R
			m_pPlayer->m_Rect.x -= m_pPlayer->m_fMaxSpeed*fDeltaTime*0.07f;
	}
	else if (3 == m_pAnimator->GetFrame())
	{
		if (m_bAtkCol)
		{	
			m_bAtkCol = false;
			HITBOX(12,tRect(m_pPlayer->m_Rect.Pos()+tPos(((m_pAnimator->IsFlip())?-90.f:90.f),-50.f), tSize(155.f, 100.f)),0.21f);
		}
	}

	if (m_pEffect)
		m_pEffect->SetPos(m_pPlayer->m_Rect.Pos()+tPos(((m_pAnimator->IsFlip())?-85.f:85.f),-60.f));

	CBehaviorAttack::Physics();
}

void CBehaviorAttack_2::Animation(void)
{
	if (!m_pAnimator->IsPlay() && m_pAnimator->GetPlayAniName()=="Momo_Attack_02")
	{
		if (m_bNextAtk)
		{
			m_eState = STATE_ATK_3;
			m_bNextAtk = false;
		}
		else
		{	
			m_eState = STATE_IDLE;
			m_pPlayer->SetPos(m_pPlayer->m_Rect.Pos());
		}

		m_bCreateEffect = m_bAtkCol = true;
		m_pEffect = NULL;
		return;
	}

	if(4 == m_pAnimator->GetFrame() && m_bCreateEffect)
	{
		m_bCreateEffect  = false;
		bool bFilp = m_pAnimator->IsFlip();
		m_pEffect = CAniEffect::Create("Leaf_Attack_02",bFilp,false,255);
		m_pEffect->SetEffectSize(tRect(m_pPlayer->m_Rect.Pos()+tPos(((bFilp)?-70.f:70.f),-60.f),tSize(300.f,140.f)));
	}

	if (m_pAnimator->GetPlayAniName()=="Momo_Attack_02")
		return;

	m_pAnimator->Play("Momo_Attack_02");
}
