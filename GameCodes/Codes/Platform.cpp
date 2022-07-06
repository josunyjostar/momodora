#include "stdafx.h"
#include "Platform.h"

CPlatform::CPlatform(void)
:m_pCollider(NULL)
,m_pSprite(NULL)
,m_pRenderer(NULL)
,m_PlatformSize()
,m_eMoveDir(DIR_NONE)
,m_fSpeed(1.f)
,m_fRangeS()
,m_fRangeE()
,m_fDir(1.f)
{


}

CGameObject* CPlatform::Ready_Object(TILE_TYPE _eType,const tPos& _Pos,int _iMapReSize,float _fTileSize,PF_DIR _eDir /*= DIR_NONE*/
									 ,float _fSpeed /*= 1.f*/,float _fRangeEnd)
{
	switch(_eType)
	{
	case TILE_S1_S:
		m_Rect.SetSize(48.f*_fTileSize, 16.f*_fTileSize);
		m_pSprite = CSpriteMgr::Inst().GetSprite("Tile1_Small");
		break;
	case TILE_S1_M:
		m_Rect.SetSize(127.f*_fTileSize, 16.f*_fTileSize);
		m_pSprite = CSpriteMgr::Inst().GetSprite("Tile1_Middle");
		break;
	case TILE_S1_L:
		m_Rect.SetSize(256.f*_fTileSize, 16.f*_fTileSize);
		m_pSprite = CSpriteMgr::Inst().GetSprite("Tile1_Large");
		break;
	case TILE_S2_S:
		m_Rect.SetSize(67.f*_fTileSize, 16.f*_fTileSize);
		m_pSprite = CSpriteMgr::Inst().GetSprite("Tile2_Small");
		break;
	}

	float x = _Pos.x*(float)_iMapReSize + m_Rect.Size().x * 0.5f;
	float y = _Pos.y*(float)_iMapReSize + m_Rect.Size().y * 0.5f;

	this->SetPos(x,y);
	m_PlatformSize = m_Rect.Size();

	m_pCollider = this->AddComponent<CCollider>();
	m_pCollider->SetColliderRect(m_PlatformSize);

	m_eMoveDir = _eDir;
	m_fRangeS = m_Rect.Pos();

	switch(m_eMoveDir)
	{
	case DIR_LR:
		m_fRangeE.x = m_Rect.x + _fRangeEnd*_iMapReSize;
		break;
	case DIR_UD:
		m_fRangeE.y = m_Rect.y + _fRangeEnd*_iMapReSize;
		break;
	case DIR_NONE:
		break;
	default:
		break;
	}

	return this;
}

void CPlatform::Init(void)
{
	m_Tag = TAG_PLATFORM;

	m_pRenderer = this->AddComponent<CRenderer>();
	m_pRenderer->SetLayer(LAYER_PLATFORM);
	m_pRenderer->SetZOrder(4);
}

void CPlatform::Update(void)
{
	static float fScarlar  = 0.f;
	static float f= 0.f;
	fScarlar += fDeltaTime*m_fSpeed*0.1f;

	switch(m_eMoveDir)
	{
	case DIR_NONE:
		return;
	case DIR_LR: 
		break;
	case DIR_UD:	
		f = (sinf(D2R(fScarlar*180.f-90.f))+1.f)*0.5f;
		m_Rect.y = m_fRangeS.y + ((m_fRangeE.y - m_fRangeS.y) * f);
		break;
	default:
		break;
	}
}

void CPlatform::Render(HDC _hBackDC)
{
	m_pSprite->Draw(_hBackDC,
		(int)(m_Rect.l() - (float)DRAWX),
		(int)(m_Rect.t() - (float)DRAWY),
		int(m_PlatformSize.x),
		int(m_PlatformSize.y));

#ifdef _DEBUG
	if(DEBUG_MODE)
	{
		static HPEN hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255,0,255));
		static HPEN hOldPen;
		static HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		static HBRUSH hOldBrush;

		hOldBrush = (HBRUSH)SelectObject(_hBackDC, hBrush);
		hOldPen = (HPEN)SelectObject(_hBackDC, hPen);

		tRect rc = m_pCollider->GetColRect();
		Rectangle(_hBackDC, 
			int(rc.L()) - DRAWX,
			int(rc.T()) - DRAWY,
			int(rc.R()) - DRAWX,
			int(rc.B()) - DRAWY);

		SelectObject(_hBackDC, hOldBrush);
		SelectObject(_hBackDC, hOldPen);
	}
#endif
}

