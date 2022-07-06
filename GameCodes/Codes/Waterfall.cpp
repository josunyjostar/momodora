#include "stdafx.h"
#include "Waterfall.h"

CWaterfall::CWaterfall(void)
:m_pAnimator(NULL)
{

}

void CWaterfall::Init(void)
{
	m_Rect = tRect(0.f, 0.f , 210.f ,720.f ,0.5f,0.5f);

	m_pAnimator = this->AddComponent<CAnimator>();
	m_pAnimator->Play("Waterfall");
	m_pAnimator->SetZOrder(3);
	m_pAnimator->SetLayer(LAYER_BGA);
	m_pAnimator->SetReSize(true);
	m_pAnimator->SetPlaySpeed(1.5f);
}
