#include "stdafx.h"
#include "BehabiorRunR.h"

void CBehaviorRunR::Update(void)
{
	//this->KeyState();
	this->Physics();
	this->Animation();
}

void CBehaviorRunR::KeyState(void)
{

}

void CBehaviorRunR::Physics(void)
{
	m_pPlayer->m_Rect.x += 300.f*fDeltaTime;
}

void CBehaviorRunR::Animation(void)
{
	if (m_pAnimator->GetPlayAniName()=="Momo_Run_Start")
		return;
	else if (m_pAnimator->GetPlayAniName()=="Momo_Run")
		return;

	m_pAnimator->Play("Momo_Run_Start");
	m_pAnimator->SetFlipX(false);
	m_pAnimator->SetPlaySpeed(0.7f);
}
