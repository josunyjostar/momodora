#include "stdafx.h"
#include "PlayerUI.h"
#include "Player.h"

CPlayerUI::CPlayerUI(void)
:m_pPlayer(NULL)
,m_pHPBarRootFrame(NULL)
,m_pHPBarBodyFrame(NULL)
,m_pHPBarHeadFrame(NULL)
,m_pSPBarRootFrame(NULL)
,m_pSPBarBodyFrame(NULL)
,m_pSPBarHeadFrame(NULL)
,m_pHPBack(NULL)
,m_pHPFront(NULL)
,m_pSPBack(NULL)
,m_pSPFront(NULL)
,m_pItemSlot(NULL)
,m_pRenderer(NULL)
,m_fHPBack_Pos(0.f)
,m_fSPBack_Pos(0.f)
{

}

void CPlayerUI::Init(void)
{
	m_Tag = TAG_UI;

	m_pHPBarRootFrame = CSpriteMgr::Inst().GetSprite("BarFrame_Root");
	m_pHPBarBodyFrame = CSpriteMgr::Inst().GetSprite("BarFrame_Body");
	m_pHPBarHeadFrame = CSpriteMgr::Inst().GetSprite("BarFrame_Head");
	m_pSPBarRootFrame = CSpriteMgr::Inst().GetSprite("BarFrame_Root");
	m_pSPBarBodyFrame = CSpriteMgr::Inst().GetSprite("BarFrame_Body");
	m_pSPBarHeadFrame = CSpriteMgr::Inst().GetSprite("BarFrame_Head");

	m_pHPBack	= CSpriteMgr::Inst().GetSprite("HPbar_Back");
	m_pHPFront	= CSpriteMgr::Inst().GetSprite("HPbar_Front");
	m_pSPBack	= CSpriteMgr::Inst().GetSprite("SPbar_Back");
	m_pSPFront	= CSpriteMgr::Inst().GetSprite("SPbar_Front");
	m_pItemSlot = CSpriteMgr::Inst().GetSprite("ItemUI");

	m_pRenderer = this->AddComponent<CRenderer>();
	m_pRenderer->SetLayer(LAYER_UI);
	m_pRenderer->SetZOrder(3);
}

void CPlayerUI::Update(void)
{
	if(m_fHPBack_Pos <= m_pPlayer->GetHP()) 
		m_fHPBack_Pos = (float)m_pPlayer->GetHP();
	else 
		m_fHPBack_Pos -= 50.f*fDeltaTime;

	if(m_fSPBack_Pos <= m_pPlayer->GetSP()) 
		m_fSPBack_Pos = (float)m_pPlayer->GetSP();
	else 
		m_fSPBack_Pos -= 100.f*fDeltaTime;

}

void CPlayerUI::Render(HDC _bBackDC)
{
	m_pItemSlot->Draw(_bBackDC,9,25,77,77);

	m_pHPBack->Draw(_bBackDC,105,25,(int)m_fHPBack_Pos,20);
	m_pHPFront->Draw(_bBackDC,105,25,(int)m_pPlayer->GetHP(),20);

	m_pHPBarRootFrame->Draw(_bBackDC,90,25,14,23);
	m_pHPBarBodyFrame->Draw(_bBackDC,104,25,(int)m_pPlayer->GetMaxHP(),23);
	m_pHPBarHeadFrame->Draw(_bBackDC,104+(int)m_pPlayer->GetMaxHP(),25,12,23);

	m_pSPBack->Draw(_bBackDC,105,52,(int)m_fSPBack_Pos,20);
	m_pSPFront->Draw(_bBackDC,105,52,(int)m_pPlayer->GetSP(),20);

	m_pSPBarRootFrame->Draw(_bBackDC,90,51,14,23);
	m_pSPBarBodyFrame->Draw(_bBackDC,104,51,(int)m_pPlayer->GetMaxSP(),23);
	m_pSPBarHeadFrame->Draw(_bBackDC,104+(int)m_pPlayer->GetMaxSP(),51,12,23);
}
