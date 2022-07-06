#include "stdafx.h"
#include "WaterSurface2.h"

CWaterSurface2::CWaterSurface2(void)
:m_pAnimator(NULL)
{

}

void CWaterSurface2::Init(void)
{
	m_Rect = tRect(0.f, 0.f , 795.f ,30.f ,0.5f,0.5f);

	m_pAnimator = this->AddComponent<CAnimator>();
	m_pAnimator->Play("WaterSurface2");
	m_pAnimator->SetZOrder(2);
	m_pAnimator->SetLayer(LAYER_BGA);
	m_pAnimator->SetReSize(true);
	m_pAnimator->SetPlaySpeed(0.3f);
}
