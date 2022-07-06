#include "stdafx.h"
#include "Stage1.h"

#include "TileCollider.h"
#include "Activator.h"
#include "Platform.h"

#include "Waterfall.h"
#include "WaterSurface.h"
#include "WaterSurface2.h"

#include "ItemDove.h"
#include "Imp.h"
#include "Sato.h"
#include "Crystal.h"
#include "MaxHP.h"

void CStage1::Init(void)
{
	const int ReSize = 3;

	CSceneMgr::Inst().SetGroundHeight(280*ReSize);

	CRenderMgr::Inst().SetBGASize(1023*ReSize, 320*ReSize);
	CRenderMgr::Inst().AddBGA("Stage1", 1023*ReSize, 320*ReSize, 0, 0, 0);
	CRenderMgr::Inst().AddBGA("Stage1_Back1", 768*ReSize, 256*ReSize, 0, 243, 4);
	CRenderMgr::Inst().AddBGA("Stage1_Back3_", WINCX, WINCY, 0, 0, 5);

	CFontMgr::Inst().Init();
	CFontMgr::Inst().SetName("MOMO");
	CFontMgr::Inst().SetCoin(0);
	CFontMgr::Inst().SetTime(600);

	CPlayer* pPlayer = CGameObject::Create<CPlayer>();
	pPlayer->SetPos(22*ReSize,277*ReSize); // 22 277
	CCamera::Inst().SetTarget(pPlayer);
	CGameObject::Create<CPlayerUI>()->SetPlayer(pPlayer);

	CInfoMgr::Inst().SaveInfo(pPlayer);
}

void CStage1::Ready_Object(void)
{
	const int ReSize = 3;

	CREATE_TILE(ReSize, -5  ,-25,5,305);
	CREATE_TILE(ReSize, 0  ,280,880,246);
	CREATE_TILE(ReSize, 880,280,143,8);
	CREATE_TILE(ReSize, 1021 ,-100,50,420);

	const int ObjCnt = 8;
	int i = 0;
	CGameObject* pObj[ObjCnt];

	pObj[i++] = CGameObject::Create<CPlatform>()->Ready_Object(TILE_S1_S,tPos(225.f,211.f),ReSize,2.5f);
	pObj[i++] = CGameObject::Create<CPlatform>()->Ready_Object(TILE_S1_S,tPos(397.f,212.f),ReSize,2.5f);
	pObj[i++] = CGameObject::Create<CPlatform>()->Ready_Object(TILE_S1_S,tPos(500.f,112.f),ReSize,2.5f,CPlatform::DIR_UD,0.2f,100.f);
	pObj[i++] = CGameObject::Create<CPlatform>()->Ready_Object(TILE_S1_M,tPos(700.f,110.f),ReSize,2.5f);
	pObj[i++] = CGameObject::Create<CPlatform>()->Ready_Object(TILE_S1_L,tPos(850.f,50.f),ReSize,2.5f);
	pObj[i++] = CGameObject::Create<CWaterSurface2>()->SetPos(ReSize*880,ReSize*301);
	pObj[i++] = CGameObject::Create<CWaterSurface>()->SetPos(ReSize*880,ReSize*304);
	pObj[i++] = CGameObject::Create<CWaterfall>()->SetPos(ReSize*993,ReSize*205);

	CGameObject::Create<CItemDove>()->SetPos(980*ReSize,45*ReSize);

	CGameObject::Create<CImp>()->SetPos(255*ReSize,211*ReSize);
	//CGameObject::Create<CImp>()->SetPos(415*ReSize,0);
	CGameObject::Create<CImp>()->SetPos(500.f*ReSize,-10*ReSize);
	CGameObject::Create<CImp>()->SetPos(970*ReSize,45*ReSize);
	CGameObject::Create<CSato>()->SetPos(850*ReSize,277*ReSize);

	CGameObject::Create<CMaxHP>()->SetPos(796*ReSize,102*ReSize);

	CGameObject::Create<CCrystal>()->SetPos(ReSize*100, ReSize*177);
	CGameObject::Create<CCrystal>()->SetPos(ReSize*130, ReSize*167);
	CGameObject::Create<CCrystal>()->SetPos(ReSize*160, ReSize*187);

	CGameObject::Create<CCrystal>()->SetPos(ReSize*300, ReSize*127);
	CGameObject::Create<CCrystal>()->SetPos(ReSize*330, ReSize*117);
	CGameObject::Create<CCrystal>()->SetPos(ReSize*360, ReSize*137);

	CGameObject::Create<CCrystal>()->SetPos(ReSize*600, ReSize*127);
	CGameObject::Create<CCrystal>()->SetPos(ReSize*630, ReSize*117);
	CGameObject::Create<CCrystal>()->SetPos(ReSize*660, ReSize*137);
	CGameObject::Create<CCrystal>()->SetPos(ReSize*690, ReSize*147);
	CGameObject::Create<CCrystal>()->SetPos(ReSize*720, ReSize*167);

	CGameObject::Create<CCrystal>()->SetPos(ReSize*420, ReSize*37);
	CGameObject::Create<CCrystal>()->SetPos(ReSize*450, ReSize*27);
	CGameObject::Create<CCrystal>()->SetPos(ReSize*480, ReSize*37);
	CGameObject::Create<CCrystal>()->SetPos(ReSize*510, ReSize*27);
	CGameObject::Create<CCrystal>()->SetPos(ReSize*540, ReSize*37);
	
	for (int i=0;i<ObjCnt;++i)
		CGameObject::Create<CActivator>()->SetTarget(pObj[i]);

	CNextStageTrigger* pTrigger = CGameObject::Create<CNextStageTrigger>();
	pTrigger->SetTrigger(tRect(ReSize*1010, ReSize*167,ReSize*5,ReSize*114,0.f,0.f),CSceneMgr::SCENE_STAGE_2);
	CSceneMgr::Inst().GetLoading()->Set_LoadingID(CLoading::LOADING_STAGE2);
	m_bReady = true;
}

void CStage1::Update(void)
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
		wsprintf(szFPS, L"Stage1 [FPS : %d]", FPS);
		FPS = 0;
	}
	SetWindowText(g_hWnd, szFPS);
#endif // _DEBUG
}

