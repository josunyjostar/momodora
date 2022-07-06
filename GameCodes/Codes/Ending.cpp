#include "stdafx.h"
#include "Ending.h"

#include "SceneMgr.h"
#include "Loading.h"

#include "TileCollider.h"
#include "BlackFilter.h"
#include "PlayerBehaviorCtrlTrigger.h"

void CEnding::Init(void)
{
	const int ReSize = 4;

	CRenderMgr::Inst().SetBGASize(415*ReSize, 463*ReSize);
	CRenderMgr::Inst().AddBGA("StageEnding", 415*ReSize, 463*ReSize, 0, 0, 0);

	CREATE_TILE(ReSize,	0,440,416,23);

	CPlayer* pPlayer = CGameObject::Create<CPlayer>();
	pPlayer->SetPos(1*ReSize,438*ReSize);
	CInfoMgr::Inst().LoadInfo(pPlayer);
	CFontMgr::Inst().Hide();
	CObjectMgr::Inst().Release<CPlayerUI>();

	CGameObject::Create<CPlayerBehaviorCtrlTigger>()->SetTrigger(tRect(ReSize*0, ReSize*323,ReSize*10,ReSize*117,0.f,0.f),STATE_RUNR);
	CGameObject::Create<CPlayerBehaviorCtrlTigger>()->SetTrigger(tRect(ReSize*205, ReSize*391,ReSize*6,ReSize*49,0.f,0.f),STATE_PRAY);

	m_bRun = true;
	m_bReady = true;
}

void CEnding::Update(void)
{
	if (m_bReady)
	{
		CSceneMgr::Inst().GetLoading()->Release();
		m_bReady = !m_bReady;
		m_bRun = true;
	}

	CScene::Update();
}
