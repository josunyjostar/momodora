#include "stdafx.h"
#include "SceneMgr.h"
#include "BlackFilter.h"
CSceneMgr::CSceneMgr(void)
:m_eCurScene(SCENE_TITLE)
,m_ePrevScene(SCENE_TITLE) 
,m_fGround_Hight(0.f)
{
	m_pCurScene[SCENE_TITLE]   = &m_Title;
	m_pCurScene[SCENE_STAGE_1] = &m_Stage1;
	m_pCurScene[SCENE_STAGE_2] = &m_Stage2;
	m_pCurScene[SCENE_STAGE_3] = &m_Stage3;
	m_pCurScene[SCENE_STAGE_4] = &m_Stage4;
	m_pCurScene[SCENE_ENDING]  = &m_Ending;

	this->SetScene(CSceneMgr::SCENE_TITLE);
}

void CSceneMgr::PrevScene(void)
{
	SetScene(m_ePrevScene);
}

void CSceneMgr::SetScene(SCENE_TYPE _eScene)
{
	m_ePrevScene = m_eCurScene;
	m_eCurScene  = _eScene;

	this->Release();

	CGameObject::Create<CBlackFilter>()->SetFilterMode(CBlackFilter::FM_OUT);

	m_Loading.Init();
	m_pCurScene[m_eCurScene]->SetRun(false);
	m_pCurScene[m_eCurScene]->Init();
}

void CSceneMgr::Update(void)
{
	if (CKeyState::Inst().IsDown('Q'))
		DEBUG_MODE = !DEBUG_MODE;

	m_pCurScene[m_eCurScene]->Update();
}

void CSceneMgr::Release(void)
{
	CCallBackMgr::Inst().Release();
	CRenderMgr::Inst().Release();
	CCollisionMgr::Inst().Release();
	CObjectMgr::Inst().Release();
}
