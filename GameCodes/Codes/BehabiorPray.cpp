#include "stdafx.h"
#include "BehabiorPray.h"

#include "BlackFilter.h"
CBehaviorPray::CBehaviorPray(void)
:m_fRunTime(0.f)
,m_ePreState(PM_END)
,m_eState(TOPRAY)
,m_bNext(true)
{
	m_fpPRAY[TOPRAY] = &CBehaviorPray::ToPray;
	m_fpPRAY[PRAYING] = &CBehaviorPray::Praying;
	m_fpPRAY[ENDPRAY] = &CBehaviorPray::EndPray;
}

void CBehaviorPray::Update(void)
{
	//this->KeyState();
	//this->Physics();
	this->Animation();
}

void CBehaviorPray::KeyState(void)
{

}

void CBehaviorPray::Physics(void)
{

}

void CBehaviorPray::Animation(void)
{
	if (m_pAnimator->GetPlayAniName() == "Momo_ToPaying" && !m_pAnimator->IsPlay())
		m_eState = PRAYING;

	if (PRAYING == m_eState)
	{
		m_fRunTime += fDeltaTime;

		if (m_fRunTime > 4.f && m_eState == PRAYING)
		{
			m_bNext = false;

			CFontMgr::Inst().CreateAlPhaText("I Want to work",15,tPos(m_pPlayer->GetX()-110.f,m_pPlayer->GetY()-180.f),
				CFont::FONT_ALPHA_IN,20.f,false);

			CFontMgr::Inst().CreateAlPhaText("Please give me a chance",15,tPos(m_pPlayer->GetX()-180.f,m_pPlayer->GetY()-150.f),
				CFont::FONT_ALPHA_IN,20.f,false);

			CFontMgr::Inst().CreateAlPhaText("Press Enter To Quit",10,tPos(float(WINCX/2)-90,float(WINCY/2)+300),
				CFont::FONT_ALPHA_INOUT,20.f,true);

			m_eState = ENDPRAY;
		}
	}
	else if (m_eState == ENDPRAY)
	{
		 if (m_pKey->IsDown(VK_RETURN))
			SendMessage(g_hWnd,WM_DESTROY,0,0);
	}

	if (m_ePreState == m_eState)
		return;

	(this->*m_fpPRAY[m_eState])();

	m_ePreState = m_eState;
}

void CBehaviorPray::ToPray(void)
{
	m_pAnimator->Play("Momo_ToPaying");
	m_pAnimator->SetPlaySpeed(1.f);
}

void CBehaviorPray::Praying(void)
{
	CGameObject::Create<CBlackFilter>()->SetFilterMode(CBlackFilter::FM_IN);
	m_pAnimator->Play("Momo_Paying");

	CFontMgr::Inst().CreateAlPhaText("@2017 made by park je young",10,tPos(float(WINCX/2)-130,float(WINCY/2)+330),
		CFont::FONT_ALPHA_IN,20.f,true);
}

void CBehaviorPray::EndPray(void)
{
	m_pAnimator->Play("Momo_EndPaying");
}
