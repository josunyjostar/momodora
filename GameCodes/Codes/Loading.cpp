#include "stdafx.h"
#include "Loading.h"

#include "SceneMgr.h"

unsigned int	__stdcall ImgLoadThread(void* pArg)
{
	CLoading*		pLoading = (CLoading*)pArg;

	EnterCriticalSection(&pLoading->GetCrt());

	switch(pLoading->Get_LoadingID())
	{
	case CLoading::LOADING_TITLE:
		pLoading->ResourceLoad();
		break;
	case CLoading::LOADING_STAGE1:
		{
			CScene* pScene = CSceneMgr::Inst().GetScene(CSceneMgr::SCENE_STAGE_1);
			pScene->Ready_Object();
		}
		break;
	case CLoading::LOADING_STAGE2:
		{
			CScene* pScene = CSceneMgr::Inst().GetScene(CSceneMgr::SCENE_STAGE_2);
			pScene->Ready_Object();
		}
		break;
	case CLoading::LOADING_STAGE3:
		{
			CScene* pScene = CSceneMgr::Inst().GetScene(CSceneMgr::SCENE_STAGE_3);
			pScene->Ready_Object();
		}
		break;
	case CLoading::LOADING_STAGE4:
		{
			CScene* pScene = CSceneMgr::Inst().GetScene(CSceneMgr::SCENE_STAGE_4);
			pScene->Ready_Object();
		}
		break;
	case CLoading::LOADING_ENDING:
		{
			CScene* pScene = CSceneMgr::Inst().GetScene(CSceneMgr::SCENE_ENDING);
			pScene->Ready_Object();
		}
		break;
	}	

	LeaveCriticalSection(&pLoading->GetCrt());

	return 0;
}

void CLoading::Set_LoadingID(LOADINGID _ID)
{
	m_LoadingID = _ID; 
}

HRESULT CLoading::Init(void)
{
	InitializeCriticalSection(&m_Crt);

	m_hThread = (HANDLE)_beginthreadex(0, 0, ImgLoadThread, this, 0, NULL);

	return S_OK;
}

void CLoading::Release(void)
{
	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);
	DeleteCriticalSection(&m_Crt);
}

void CLoading::ResourceLoad(void)
{
	if(m_bFinish)
		return;

	CTextureMgr::Inst().Init();
	m_bFinish = true;
}
