#include "stdafx.h"
#include "Stage2.h"

#include "TileCollider.h"
#include "Activator.h"
#include "Platform.h"

#include "Imp.h"
#include "Sato.h"
#include "MaxHP.h"
#include "Crystal.h"

void CStage2::Init(void)
{
	const int ReSize = 3;

	CSceneMgr::Inst().SetGroundHeight(640*ReSize);

	CRenderMgr::Inst().SetBGASize(506*ReSize, 706*ReSize);
	CRenderMgr::Inst().AddBGA("Stage2", 506*ReSize, 706*ReSize, 0, 0, 0);
	CRenderMgr::Inst().AddBGA("Stage2_Back1", WINCX, 100*5, 0, 1400, 1);
	CRenderMgr::Inst().AddBGA("Stage1_Back3", WINCX, 850, 0, 0, 2);

	CPlayer* pPlayer = CGameObject::Create<CPlayer>();
	pPlayer->SetPos(7*ReSize,639*ReSize);
	CInfoMgr::Inst().LoadInfo(pPlayer);
}

void CStage2::Ready_Object(void)
{
	const int ReSize = 3;

	CREATE_TILE(ReSize, -1 ,0,1,640);

	CREATE_TILE(ReSize, 64 ,168,32,344);
	CREATE_TILE(ReSize, 0  ,640,560,66);
	CREATE_TILE(ReSize, 96 ,176,410,31);
	CREATE_TILE(ReSize, 465,207,42,366);
	CREATE_TILE(ReSize, 462,560,3 ,13);

	//5°³ ³­°£
	CREATE_TILE(ReSize, 96,494,87 ,16);
	CREATE_TILE(ReSize, 96,381,121 ,16);
	CREATE_TILE(ReSize, 339,321,126,16);
	CREATE_TILE(ReSize, 347,441,118,16);
	CREATE_TILE(ReSize, 361,544,104,16);
	//
	CREATE_TILE(ReSize, 506,573,5 ,67);

	const int ObjCnt = 17;
	int i = 0;
	CGameObject* pObj[ObjCnt];

	pObj[i++] = CGameObject::Create<CSato>()->SetPos(464*ReSize,706*ReSize);
	pObj[i++] = CGameObject::Create<CImp>()->SetPos(449*ReSize,526*ReSize);
	pObj[i++] = CGameObject::Create<CImp>()->SetPos(112*ReSize,359*ReSize);
	pObj[i++] = CGameObject::Create<CImp>()->SetPos(106*ReSize,475*ReSize);
	pObj[i++] = CGameObject::Create<CMaxHP>()->SetPos(403*ReSize,313*ReSize);

	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*107, ReSize*445);
	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*137, ReSize*435);
	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*167, ReSize*445);
	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*197, ReSize*435);

	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*107, ReSize*283);
	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*137, ReSize*293);
	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*167, ReSize*283);
	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*197, ReSize*293);

	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*346, ReSize*374);
	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*376, ReSize*364);
	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*406, ReSize*374);
	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*436, ReSize*364);

	for (int i=0;i<ObjCnt;++i)
		CGameObject::Create<CActivator>()->SetTarget(pObj[i]);

	CGameObject::Create<CPlatform>()->Ready_Object(TILE_S2_S,tPos(255.f,250.f),ReSize,2.5f,CPlatform::DIR_UD,0.9f,318.f);

	CNextStageTrigger* pNextTrigger = CGameObject::Create<CNextStageTrigger>();
	pNextTrigger->SetTrigger(tRect(ReSize*503, ReSize*574,ReSize*5,ReSize*66,0.f,0.f),CSceneMgr::SCENE_STAGE_3);
	CSceneMgr::Inst().GetLoading()->Set_LoadingID(CLoading::LOADING_STAGE3);

	m_bReady = true;
}

void CStage2::Update(void)
{
	if (m_bReady)
	{
		CSceneMgr::Inst().GetLoading()->Release();
		m_bReady = !m_bReady;
		m_bRun = true;
	}

	CScene::Update();

#ifdef _DEBUG
	static int FPS = 0;
	static DWORD dwFPS = GetTickCount();
	static TCHAR szFPS[64];
	++FPS;
	if(dwFPS + 1000 < GetTickCount())
	{
		dwFPS = GetTickCount();
		wsprintf(szFPS, L"Stage2 [FPS : %d]", FPS);
		FPS = 0;
	}
	SetWindowText(g_hWnd, szFPS);
#endif // _DEBUG
}

