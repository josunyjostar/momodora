#include "stdafx.h"
#include "WaterSurface.h"

CWaterSurface::CWaterSurface(void)
:m_pAnimator(NULL)
{

}

void CWaterSurface::Init(void)
{
	m_Rect = tRect(0.f, 0.f , 795.f ,25.f ,0.5f,0.5f);

	m_pAnimator = this->AddComponent<CAnimator>();
	m_pAnimator->Play("WaterSurface");
	m_pAnimator->SetZOrder(1);
	m_pAnimator->SetLayer(LAYER_BGA);
	m_pAnimator->SetReSize(true);
	m_pAnimator->SetPlaySpeed(0.25f);
}
