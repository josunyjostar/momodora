#include "stdafx.h"
#include "RenderMgr.h"

CRenderMgr::CRenderMgr(void)
:m_hdc(NULL)
,m_hBackDC(NULL)
,m_hDBBitmap(NULL)
,m_iSize(0)
,m_iSortSize(0)
{
	memset(m_pBGAs,NULL,sizeof(m_pBGAs));
	memset(m_pRenderer,NULL,sizeof(m_pRenderer));
	memset(m_pSortRenderer,NULL,sizeof(m_pSortRenderer));
	memset(m_BGAPos,NULL,sizeof(m_BGAPos));

	this->Init();
}

CRenderMgr::~CRenderMgr(void)
{
	this->Release();

	if (m_hdc)
		ReleaseDC(g_hWnd,m_hdc);
	if (m_hBackDC)
		DeleteDC(m_hBackDC);
	if (m_hDBBitmap)
		DeleteObject(m_hDBBitmap);
}

void CRenderMgr::Init(void)
{
	m_hdc = GetDC(g_hWnd);
	m_hBackDC = CreateCompatibleDC(m_hdc);
	m_hDBBitmap = CreateCompatibleBitmap(m_hdc,WINCX,WINCY);
	SelectObject(m_hBackDC,m_hDBBitmap);

#ifdef _DEBUG
	SetTextColor(m_hBackDC, RGB(255,255,255));
	SetBkMode(m_hBackDC, TRANSPARENT);
#endif
}

void CRenderMgr::Release(void)
{
	this->SetBGASize(WINCX,WINCY);
	memset(m_pBGAs,NULL,sizeof(m_pBGAs));
	memset(m_pRenderer,NULL,sizeof(m_pRenderer));
	memset(m_pSortRenderer,NULL,sizeof(m_pSortRenderer));
	memset(m_BGAPos,NULL,sizeof(m_BGAPos));

	m_iSize = 0;
	m_iSortSize = 0;

	CCamera::Inst().SetTarget(NULL);
}

void CRenderMgr::Render(void)
{
	if((BGACX-WINCX > 0) && (BGACY-WINCY > 0))
	{
		for(int i = 0; i < MAX_BGA; ++i)
		{
			if(!m_pBGAs[i]) 
				continue;

#ifdef _DEBUG
			CSprite* pSprite = m_pBGAs[i]->GetComponent<CSprite>();
			const char* pName = pSprite->GetSpriteName();
#endif // _DEBUG
			static tRect rc = m_pBGAs[i]->GetRect();
			rc = m_pBGAs[i]->GetRect();

			rc.x = DRAWX*(BGACX-rc.cx)/(BGACX-WINCX) + m_BGAPos[i].x;
			rc.y = DRAWY*(BGACY-(rc.cy+m_BGAPos[i].y))/(BGACY-WINCY) + m_BGAPos[i].y;

			m_pBGAs[i]->SetRect(rc);
		}
	}

	for(int i =0; i < LAYER_TYPE_END; ++i)
	{
		this->Sort(i);

		for(int j =0; j < m_iSortSize ; ++j)
		{
#ifdef _DEBUG
			const char* pName = m_pSortRenderer[j]->GetRTTI()->GetClassName();
#endif // _DEBUG
			m_pSortRenderer[j]->Render(m_hBackDC);
		}
	}	

	InvalidateRect(g_hWnd,NULL,false);
}

void CRenderMgr::Paint(void)
{
	BitBlt(m_hdc,0,0,WINCX,WINCX,m_hBackDC,0,0,SRCCOPY);
}

void CRenderMgr::Sort(const int& _Layer)
{
	m_iSortSize = 0;

	for(int i = 0; i < m_iSize ; ++i)
	{
		if (!m_pRenderer[i])
			continue;

		if (m_pRenderer[i]->GetLayer() == _Layer)
			m_pSortRenderer[m_iSortSize++] = m_pRenderer[i];
	}

	//ZOrder Sort
	for (int i = 0; i < m_iSortSize - 1 ; ++i)
	{
		for(int j = i+1; j < m_iSortSize ; ++j)
		{
			if (m_pSortRenderer[i]->GetZOrder() < m_pSortRenderer[j]->GetZOrder())
			{
				CRenderer* pTemp = m_pSortRenderer[i];
				m_pSortRenderer[i] = m_pSortRenderer[j];
				m_pSortRenderer[j] = pTemp;
			}
		}
	}
}

CGameObject* CRenderMgr::AddBGA(char* _pName,const int& _ZOrder)
{
	for (int i = 0; i < MAX_BGA ; ++i)
	{
		if (m_pBGAs[i])
			continue;

		tSprite* pSprite = CSpriteMgr::Inst().GetSprite(_pName);
		m_pBGAs[i] = CObjectMgr::Inst().Create<CGameObject>();
		m_pBGAs[i]->SetRect(0.f,0.f,(float)pSprite->Width, (float)pSprite->Height,0.f,0.f);

		m_BGAPos[i].x = 0;
		m_BGAPos[i].y = 0;

		CSprite* pSpriteComponent = m_pBGAs[i]->AddComponent<CSprite>();
		pSpriteComponent->SetSprite(_pName);
		pSpriteComponent->SetLayer(LAYER_BGA);
		pSpriteComponent->SetZOrder(_ZOrder);
		
		return m_pBGAs[i];
	}
	return NULL;
}

CGameObject* CRenderMgr::AddBGA(char* _pName, int _BGACX, int _BGACY, int _DrawX, int _DrawY, int _ZOrder /*= 0*/)
{
	for (int i = 0; i < MAX_BGA ; ++i)
	{
		if (m_pBGAs[i])
			continue;

		m_pBGAs[i] = CObjectMgr::Inst().Create<CGameObject>();
		m_pBGAs[i]->SetRect(0.f,0.f,(float)_BGACX, (float)_BGACY,0.f,0.f);

		m_BGAPos[i].x = _DrawX;
		m_BGAPos[i].y = _DrawY;

		CSprite* pSpriteComponent = m_pBGAs[i]->AddComponent<CSprite>();
		pSpriteComponent->SetResize(true);
		pSpriteComponent->SetSprite(_pName);
		pSpriteComponent->SetLayer(LAYER_BGA);
		pSpriteComponent->SetZOrder(_ZOrder);

		return m_pBGAs[i];
	}
	return NULL;
}

void CRenderMgr::SetBGASize(int _BGACX,int _BGACY)
{
	BGACX = _BGACX;
	BGACY = _BGACY;
}

void CRenderMgr::ClearBGA(void)
{
	for(int i =0; i < MAX_BGA ; ++i)
	{
		if (m_pBGAs[i])
		{
			m_pBGAs[i]->SetActive(false);
			m_pBGAs[i] = NULL;
		}
	}
}

void CRenderMgr::AddRenderer(CRenderer* _pRenderer)
{

	for(int i=0; i < m_iSize ; ++i)
	{
		if (m_pRenderer[i])
			continue;

		m_pRenderer[i] = _pRenderer;
		return;
	}

	m_pRenderer[m_iSize++] = _pRenderer;
}

void CRenderMgr::DeleteRenderer(CRenderer* _pRenderer)
{
	for(int i=0; i < m_iSize ; ++i)
	{
		if (m_pRenderer[i] == _pRenderer)
		{
			m_pRenderer[i] = NULL;
			return;
		}
	}
}
