#include "stdafx.h"
#include "Stage3.h"

#include "Activator.h"
#include "Platform.h"
#include "TileCollider.h"
#include "MaxSP.h"
#include "Magnolia.h"
#include "Imp.h"
#include "Crystal.h"

void CStage3::Init(void)
{
	const int ReSize = 4;

	CSceneMgr::Inst().SetGroundHeight(184*ReSize);

	CRenderMgr::Inst().SetBGASize(1792*ReSize, 207*ReSize);
	CRenderMgr::Inst().AddBGA("Stage3", 1792*ReSize, 207*ReSize, 0, 0, 0);
	CRenderMgr::Inst().AddBGA("Stage1_Back3", WINCX, WINCY, 0, 0, 2);

	//시작위치 바닥
	CREATE_TILE(ReSize, 0  ,184,1792,23);

	CPlayer* pPlayer = CGameObject::Create<CPlayer>();
	pPlayer->SetPos(4*ReSize,135*ReSize);
	CInfoMgr::Inst().LoadInfo(pPlayer);
}

void CStage3::Ready_Object(void)
{
	const int ReSize = 4;

	CREATE_TILE(ReSize, 0 ,0,1792,24);  //천장

	//좌
	CREATE_TILE(ReSize, 0 ,0,48,72);
	CREATE_TILE(ReSize, -1 ,72,1,64);
	CREATE_TILE(ReSize, 0 ,136,48,71);
	//우
	CREATE_TILE(ReSize, 1744  ,0,48,72);
	CREATE_TILE(ReSize, 1744 ,136,48,71);

	//타일 7개
	CREATE_TILE(ReSize, 223 ,124,97,15);
	CREATE_TILE(ReSize, 447,99,97,15);
	CREATE_TILE(ReSize, 671,119,98,16);
	CREATE_TILE(ReSize, 849,98,97,15);
	CREATE_TILE(ReSize, 1023,82,98,15);
	CREATE_TILE(ReSize, 1247,104,98,15);
	CREATE_TILE(ReSize, 1471,128,97,15);
	//좌계단
	CREATE_TILE(ReSize, 48,136,9,9);
	CREATE_TILE(ReSize, 57,145,7,8);
	CREATE_TILE(ReSize, 64,153,8,8);
	CREATE_TILE(ReSize, 72,161,8,8);
	CREATE_TILE(ReSize, 80,169,8,8);
	CREATE_TILE(ReSize, 88,177,8,7);

	//우계단
	CREATE_TILE(ReSize, 1696,177,8,7);
	CREATE_TILE(ReSize, 1704,169,8,8);
	CREATE_TILE(ReSize, 1712,161,8,8);
	CREATE_TILE(ReSize, 1720,153,8,8);
	CREATE_TILE(ReSize, 1728,145,8,8);
	CREATE_TILE(ReSize, 1736,136,8,9);

	const int ObjCnt = 29;
	int i = 0;
	CGameObject* pObj[ObjCnt];

	pObj[i++] = CGameObject::Create<CMaxSP>()->SetPos(490*ReSize,91*ReSize);
	pObj[i++] =	CGameObject::Create<CPlatform>()->Ready_Object(TILE_S2_S,tPos(139.f,79.f),ReSize,2.5f,CPlatform::DIR_UD,1.6f,70);
	pObj[i++] =	CGameObject::Create<CPlatform>()->Ready_Object(TILE_S2_S,tPos(1164.f,80.f),ReSize,2.5f,CPlatform::DIR_UD,2.f,60);
	pObj[i++] = CGameObject::Create<CMagnolia>()->SetPos(493*ReSize,72*ReSize);
	pObj[i++] = CGameObject::Create<CMagnolia>()->SetPos(898*ReSize,78*ReSize);

	pObj[i++] = CGameObject::Create<CImp>()->SetPos(283*ReSize,123*ReSize);
	pObj[i++] = CGameObject::Create<CImp>()->SetPos(720*ReSize,183*ReSize);
	pObj[i++] = CGameObject::Create<CImp>()->SetPos(1255*ReSize,103*ReSize);
	pObj[i++] = CGameObject::Create<CImp>()->SetPos(1517*ReSize,127*ReSize);

	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*340, ReSize*91);
	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*360, ReSize*91);
	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*380, ReSize*91);
	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*400, ReSize*91);
	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*420, ReSize*91);

	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*560, ReSize*99);
	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*580, ReSize*99);
	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*600, ReSize*99);
	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*620, ReSize*99);
	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*640, ReSize*99);

	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*1355, ReSize*73);
	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*1375, ReSize*73);
	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*1395, ReSize*73);
	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*1415, ReSize*73);
	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*1435, ReSize*73);

	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*1583, ReSize*73);
	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*1603, ReSize*73);
	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*1623, ReSize*73);
	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*1643, ReSize*73);
	pObj[i++] = CGameObject::Create<CCrystal>()->SetPos(ReSize*1663, ReSize*73);

	for (int i=0;i<ObjCnt;++i)
		CGameObject::Create<CActivator>()->SetTarget(pObj[i]);

	CNextStageTrigger* pNextTigger  = CGameObject::Create<CNextStageTrigger>();
	pNextTigger->SetTrigger(tRect(ReSize*1790, ReSize*73,ReSize*5,ReSize*64,0.f,0.f),CSceneMgr::SCENE_STAGE_4);
	CSceneMgr::Inst().GetLoading()->Set_LoadingID(CLoading::LOADING_STAGE4);

	m_bReady = true;
}

void CStage3::Update(void)
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
		wsprintf(szFPS, L"Stage3 [FPS : %d]", FPS);
		FPS = 0;
	}
	SetWindowText(g_hWnd, szFPS);
#endif // _DEBUG
}

