#include "stdafx.h"
#include "MaxHP.h"

CMaxHP::CMaxHP(void)
:m_pSprite(NULL)
,m_pCollider(NULL)
{

}

void CMaxHP::Init(void)
{
	m_Tag = TAG_ITEM;
	
	m_Rect = tRect(0.f, 0.f, 40.f, 40.f, 0.5f, 0.5f);

#ifdef _DEBUG
	this->AddComponent<CRenderer>();
#endif // _DEBUG

	m_pSprite	= this->AddComponent<CSprite>();
	m_pSprite->SetSprite("MaxHP");
	m_pSprite->SetResize(true);

	m_pCollider = this->AddComponent<CCollider>();
	m_pCollider->SetColliderRect(tRect(tPos(),m_Rect.Size(),m_Rect.Offset()));
}

void CMaxHP::Update(void)
{
	static float y  = 0.f;
	y += fDeltaTime*18.f;//speed

	m_Rect.y += sinf(y)*0.3f;//Range
}

void CMaxHP::Render(HDC _hBackDC)
{
#ifdef _DEBUG
	if (DEBUG_MODE)
	{
		static HPEN hPen = (HPEN)CreatePen(PS_SOLID, 1, COLLIDER_COLOR);
		static HPEN hOldPen;
		static HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		static HBRUSH hOldBrush;

		hOldBrush = (HBRUSH)SelectObject(_hBackDC, hBrush);
		hOldPen = (HPEN)SelectObject(_hBackDC, hPen);
		tRect rc =m_pCollider->GetColRect();
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

void CMaxHP::CollisionEnter(COL_INFO& _ColInfo)
{
	if(IsDynamicCast(CPlayer, _ColInfo.pObj))
	{
		this->SetActive(false);
		((CPlayer*)_ColInfo.pObj)->AddMAXHP(15);
		((CPlayer*)_ColInfo.pObj)->SetHP(((CPlayer*)_ColInfo.pObj)->GetMaxHP());
	}
}
