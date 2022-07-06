#include "stdafx.h"
#include "Title.h"

#include "SceneMgr.h"
#include "Loading.h"
#include "Dove.h"
#include "BlackFilter.h"

CTitle::CTitle(void)
:m_pStartBt(NULL)
,m_pQuitBt(NULL)
,m_pLoadingFont(NULL)
,m_iIdx(0)
,m_pKey(&CKeyState::Inst())
,m_pSelectIcon(NULL)
{
	CImage *pImage;

	CTextureMgr*		pTextureMgr = &CTextureMgr::Inst();
	CAnimationMgr*		pAniMgr = &CAnimationMgr::Inst();
	CSpriteMgr*			pSpriteMgr = &CSpriteMgr::Inst();

	//Black
	pImage = pTextureMgr->AddTexture("Black",L"../../Resources/Filter/Black.png");
	pSpriteMgr->AddSprite(pImage,"Black",0,0,16,16,0,0,RENDER_ALPHA);

	//Font Alpha
	pImage = pTextureMgr->AddTexture("Font",L"../../Resources/Font.png");
	pAniMgr->AddAni(pImage,pImage,"Font",44,0,0,8,8,0,0,0,0,RENDER_ALPHA,true);

	CImage *pImageL,*pImageR;
	float*	pFrameDelay;
	//Dove
	pImageL = pTextureMgr->AddTexture("DoveL", L"../../Resources/Pet/DoveL.png");
	pImageR = pTextureMgr->AddTexture("DoveR", L"../../Resources/Pet/DoveR.png");

	pFrameDelay = new float[2];
	for(int i = 0; i < 2; ++i)
		pFrameDelay[i] = 0.07f;

	pAniMgr->AddAni(pImageL,pImageR,"Dove_Fly"	   ,2,0,29 ,23,29,0,0,0,0,RENDER_ALPHA,true,NULL,pFrameDelay);

	m_pLoading = CSceneMgr::Inst().GetLoading();
}

void CTitle::Init(void)
{
	if (m_pLoading->GetFinish())
		return;
	//fake
	m_pLoadingFont = CFontMgr::Inst().CreateAlPhaText("Now Loading...",10,tPos(float(WINCX/2)-600,float(WINCY/2)+330),
		CFont::FONT_ALPHA_INOUT,200.f,true);

	CGameObject::Create<CBlackFilter>();

	CFontMgr::Inst().CreateAlPhaText("M o m o d o r a",70,tPos(float(WINCX/2)-505,float(WINCY/2)-160),
		CFont::FONT_ALPHA_IN,20.f,true);

	CFontMgr::Inst().CreateAlPhaText("@2017 made by park je young",12,tPos(float(WINCX/2)-170,float(WINCY/2)+320),
		CFont::FONT_ALPHA_IN,20.f,true);

	m_pStartBt = CFontMgr::Inst().CreateAlPhaText("Start Game",20,tPos(float(WINCX/2)-100,float(WINCY/2)+100-40),
		CFont::FONT_ALPHA_IN,20.f,true);

	m_pQuitBt = CFontMgr::Inst().CreateAlPhaText("Quit Game",20,tPos(float(WINCX/2)-90,float(WINCY/2)+160-40),
		CFont::FONT_ALPHA_IN,20.f,true);

	m_pStartBt->SetX(float(WINCX/2)-150);
	m_pStartBt->GetComponent<CFont>()->SetFontSize(30);
	m_pStartBt->GetComponent<CFont>()->SetAlphaType(CFont::FONT_ALPHA_INOUT);
	m_pStartBt->GetComponent<CFont>()->SetAlphaRate(1.f);

	m_pSelectIcon = CGameObject::Create<CDove>();
	m_pSelectIcon->SetPos(tPos(float(WINCX/2)-200,float(WINCY/2)+65));
	m_pSelectIcon->GetComponent<CAnimator>()->SetLayer(LAYER_UI);
	m_pSelectIcon->SetMoveMode(CDove::MOVE_NONE);

	m_bRun = true;
}

void CTitle::Update(void)
{
	CScene::Update();

#ifdef _DEBUG
	static int FPS = 0;
	static DWORD dwFPS = GetTickCount();
	static TCHAR szFPS[64];
	++FPS;
	if(dwFPS + 1000 < GetTickCount())
	{
		dwFPS = GetTickCount();
		wsprintf(szFPS, L"Title [FPS : %d]", FPS);
		FPS = 0;
	}
	SetWindowText(g_hWnd, szFPS);
#endif // _DEBUG
	if (m_pLoading->GetFinish())
	{
		static bool bLoad = false;
		if (!bLoad)
		{
			bLoad = true;
			m_pLoadingFont->GetComponent<CFont>()->String("Loading Complete..");
			m_pLoading->Release();
		}

		switch(m_iIdx)
		{
		case BT_START:
			if (m_pKey->Down(KEY_DOWN))
			{	
				m_iIdx = 1;
				m_pStartBt->SetX(float(WINCX/2)-100);
				m_pStartBt->GetComponent<CFont>()->SetFontSize(20);
				m_pStartBt->GetComponent<CFont>()->SetAlphaType(CFont::FONT_ALPHA_NONE);

				m_pQuitBt->SetX(float(WINCX/2)-130);
				m_pQuitBt->GetComponent<CFont>()->SetFontSize(30);
				m_pQuitBt->GetComponent<CFont>()->SetAlphaType(CFont::FONT_ALPHA_INOUT);
				m_pQuitBt->GetComponent<CFont>()->SetAlphaRate(1.f);

				m_pSelectIcon->SetPos(tPos(float(WINCX/2)-170,float(WINCY/2)+125));
				break;
			}
			else if (m_pKey->IsDown(VK_RETURN))
			{
				CSceneMgr::Inst().GetLoading()->Set_LoadingID(CLoading::LOADING_STAGE1);
				CSceneMgr::Inst().SetScene(CSceneMgr::SCENE_STAGE_1);
			}
			break;
		case BT_QUIT:
			if (m_pKey->Up(KEY_DOWN))
			{	
				m_iIdx = 0;
				m_pQuitBt->SetX(float(WINCX/2)-90);
				m_pQuitBt->GetComponent<CFont>()->SetFontSize(20);
				m_pQuitBt->GetComponent<CFont>()->SetAlphaType(CFont::FONT_ALPHA_NONE);

				m_pStartBt->SetX(float(WINCX/2)-150);
				m_pStartBt->GetComponent<CFont>()->SetFontSize(30);
				m_pStartBt->GetComponent<CFont>()->SetAlphaType(CFont::FONT_ALPHA_INOUT);
				m_pStartBt->GetComponent<CFont>()->SetAlphaRate(1.f);

				m_pSelectIcon->SetPos(tPos(float(WINCX/2)-200,float(WINCY/2)+65));
				break;
			}
			else if (m_pKey->IsDown(VK_RETURN))
			{
				SendMessage(g_hWnd,WM_DESTROY,0,0);
			}
			break;
		}
	}	
}
