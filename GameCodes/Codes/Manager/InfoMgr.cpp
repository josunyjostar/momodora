#include "stdafx.h"
#include "InfoMgr.h"

#include "Dove.h"

CInfoMgr::CInfoMgr(void)
:m_fPlayerHP(0.f)
,m_fPlayerMAXHP(0.f)
,m_fPlayerSP(0.f)
,m_fPlayerMAXSP(0.f)
,m_iCoin(0)
,m_iTime(0)
,m_bDove(false)
{

}

void CInfoMgr::SaveInfo(CPlayer* pPlayer)
{
	m_fPlayerHP = pPlayer->GetHP();
	m_fPlayerMAXHP = pPlayer->GetMaxHP();
	m_fPlayerSP = pPlayer->GetSP();
	m_fPlayerMAXSP = pPlayer->GetMaxSP();

	m_iCoin = CFontMgr::Inst().GetCoin();
	m_iTime = CFontMgr::Inst().GetTime();
}

void CInfoMgr::LoadInfo(CPlayer* pPlayer)
{
	pPlayer->SetHP(m_fPlayerHP);
	pPlayer->SetMAXHP(m_fPlayerMAXHP);
	pPlayer->SetSP(m_fPlayerSP);
	pPlayer->SetMAXSP(m_fPlayerMAXSP);

	CFontMgr::Inst().Init();
	CFontMgr::Inst().SetName(CFontMgr::Inst().GetName());
	CFontMgr::Inst().SetCoin(m_iCoin);
	CFontMgr::Inst().SetTime(m_iTime);

	CCamera::Inst().SetTarget(pPlayer);
	CGameObject::Create<CPlayerUI>()->SetPlayer(pPlayer);

	if (m_bDove)
	{
		CDove* pDove = CGameObject::Create<CDove>();
		pDove->SetPos(pPlayer->GetPos()+tPos(0.f,-100.f));
		pDove->SetPlayer(pPlayer);
		pDove->SetMoveMode(CDove::MOVE_PLAYER_AROUND);
	}
}
