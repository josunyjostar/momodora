#include "stdafx.h"
#include "BehabiorAttack.h"

void CBehaviorAttack_1::Update(void)
{
	this->KeyState();
	this->Physics();
	this->Animation();
}

void CBehaviorAttack_1::KeyState(void)
{
	
}

void CBehaviorAttack_1::Physics(void)
{
	
}

void CBehaviorAttack_1::Animation(void)
{
	if (!m_pAnimator->IsPlay())
	{
		m_eState = STATE_IDLE;
		m_bEffect = true;
		return;
	}

	if(m_pAnimator->GetFrame() == 5 && m_bEffect)
	{
		m_bEffect = false;
		bool bFilp = m_pAnimator->IsFlip();
		CEffect* pEffect = CEffect::Create("Leaf_Attack_01", true, bFilp, 0.16f, false, 255);
		pEffect->SetEffectSize(tRect(m_pPlayer->m_Rect.Pos()+tPos(((bFilp)?-90.f:90.f),-60.f),tSize(288.f,140.f)));
	}

	if (m_pAnimator->GetPlayAniName()=="Momo_Attack_01")
		return;

	m_pAnimator->Play("Momo_Attack_01");
}
