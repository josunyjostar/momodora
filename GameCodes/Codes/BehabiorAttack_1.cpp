#include "stdafx.h"
#include "BehabiorAttack_1.h"

void CBehaviorAttack_1::Update(void)
{
	this->KeyState();
	this->Physics();
	this->Animation();
}

void CBehaviorAttack_1::KeyState(void)
{
	if (m_pKey->Attack(KEY_DOWN))
		m_bNextAtk = true;
}

void CBehaviorAttack_1::Physics(void)
{
	if (m_bAtkCol && 3 == m_pAnimator->GetFrame())
	{	
		m_bAtkCol = false;
		HITBOX(10,tRect(m_pPlayer->m_Rect.Pos()+tPos(((m_pAnimator->IsFlip())?-85.f:85.f),-50.f), tSize(160.f, 100.f)),0.2f);
	}

	if (m_pEffect)
		m_pEffect->SetPos(m_pPlayer->m_Rect.Pos()+tPos(((m_pAnimator->IsFlip())?-85.f:85.f),-60.f));

	CBehaviorAttack::Physics();
}

void CBehaviorAttack_1::Animation(void)
{
	if (!m_pAnimator->IsPlay())
	{
		if (m_bNextAtk)
		{
			m_bNextAtk = false;
			m_eState = STATE_ATK_2;
		}
		else
			m_eState = STATE_IDLE;

		m_bCreateEffect = m_bAtkCol = true;
		m_pEffect = NULL;

		return;
	}

	if(m_pAnimator->GetFrame() == 4 && m_bCreateEffect)
	{
		m_bCreateEffect = false;
		bool bFilp = m_pAnimator->IsFlip();
		m_pEffect = CAniEffect::Create("Leaf_Attack_01",bFilp,false,255);
		m_pEffect->SetEffectSize(tRect(m_pPlayer->m_Rect.Pos()+tPos(((bFilp)?-90.f:90.f),-60.f),tSize(288.f,140.f)));
	}

	if (m_pAnimator->GetPlayAniName()=="Momo_Attack_01")
		return;

	m_pAnimator->Play("Momo_Attack_01");
}
