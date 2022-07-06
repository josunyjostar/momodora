#include "stdafx.h"
#include "Stage4.h"

#include "TileCollider.h"
#include "Platform.h"

#include "Fennel.h"
#include "Door.h"

void CStage4::Init(void)
{
	const int ReSize = 3;

	CSceneMgr::Inst().SetGroundHeight(424*ReSize);

	CRenderMgr::Inst().SetBGASize(1024*ReSize, 463*ReSize);
	CRenderMgr::Inst().AddBGA("Stage4", 1024*ReSize, 463*ReSize, 0, 0, 0);

	//시작위치 바닥
	CREATE_TILE(ReSize,	0,136,80,16);

	CPlayer* pPlayer = CGameObject::Create<CPlayer>();
	pPlayer->SetPos(5*ReSize,130*ReSize);//5 130 //658 420
	CInfoMgr::Inst().LoadInfo(pPlayer);
}

void CStage4::Ready_Object(void)
{
	const int ReSize = 3;

	//시작 문
	CREATE_TILE(ReSize, -1 ,72,1,64);

	//천장 
	CREATE_TILE(ReSize, 0,0,48,72);
	CREATE_TILE(ReSize, 0,0,864,40);
	CREATE_TILE(ReSize, 832,0,32,72);
	CREATE_TILE(ReSize, 832,40,192,32);
	
	//우 벽
	CREATE_TILE(ReSize, 800,136,224,96);
	CREATE_TILE(ReSize, 816,232,208,48);
	CREATE_TILE(ReSize, 928,280,96,48);
	CREATE_TILE(ReSize, 361,544,104,16);

	//좌벽
	CREATE_TILE(ReSize,	0,152,48,311);
	//바닥
	CREATE_TILE(ReSize,	896,392,128,32);
	CREATE_TILE(ReSize,	48,424,976,39);

	//발판 순서는 위->아래
	CREATE_TILE(ReSize,	128,200,128,16);
	CREATE_TILE(ReSize,	64,264,48,16);
	CREATE_TILE(ReSize,	80,328,112,16);
	CREATE_TILE(ReSize,	224,360,80,16);

	//가장 오른쪽 길막 
	CREATE_TILE(ReSize,	1024,328,1,64);

	CDoor* pDoor = CGameObject::Create<CDoor>();
	pDoor->SetOriPos(tPos(905*ReSize,336*ReSize));
	CFennel* pFennel = CGameObject::Create<CFennel>();
	pFennel->SetPos(758*ReSize,403*ReSize);
	pFennel->SetDoor(pDoor);
	
	CNextStageTrigger* pNextTrigger = CGameObject::Create<CNextStageTrigger>();
	pNextTrigger->SetTrigger(tRect(ReSize*1014, ReSize*328,ReSize*4,ReSize*64,0.f,0.f),CSceneMgr::SCENE_ENDING);
	CSceneMgr::Inst().GetLoading()->Set_LoadingID(CLoading::LOADING_ENDING);

	m_bReady = true;
}

void CStage4::Update(void)
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
		wsprintf(szFPS, L"Stage4 [FPS : %d]", FPS);
		FPS = 0;
	}
	SetWindowText(g_hWnd, szFPS);
#endif // _DEBUG
}

