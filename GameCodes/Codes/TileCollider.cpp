#include "stdafx.h"
#include "TileCollider.h"

void CTileCollider::Init(tRect _tCollRect, COL_TYPE _ColType)
{
	m_Tag = TAG_PLATFORM;

	this->AddComponent<CRenderer>();

	m_Rect = _tCollRect;
	m_pCollider = this->AddComponent<CCollider>();
	m_pCollider->SetColliderRect(tRect(tPos(),m_Rect.Size(),m_Rect.Offset()));
	m_pCollider->SetColType(_ColType);
}

void CTileCollider::Render(HDC _hbackDC)
{
#ifdef _DEBUG
	if(DEBUG_MODE)
	{
		if(!m_pCollider)
			return;

		static HPEN hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255,0,255));
		static HPEN hOldPen;
		static HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		static HBRUSH hOldBrush;

		hOldBrush = (HBRUSH)SelectObject(_hbackDC, hBrush);
		hOldPen = (HPEN)SelectObject(_hbackDC, hPen);

		tRect rc = m_pCollider->GetColRect();

		if(m_pCollider->GetColType() == COL_RECT) {
			Rectangle(_hbackDC, 
				int(rc.L()) - DRAWX,
				int(rc.T()) - DRAWY,
				int(rc.R()) - DRAWX,
				int(rc.B()) - DRAWY);
		}
		else {
			MoveToEx(_hbackDC, int(rc.L()) - DRAWX, int(rc.T()) - DRAWY, NULL);
			LineTo(_hbackDC, int(rc.R()) - DRAWX, int(rc.B()) - DRAWY);
		}

		SelectObject(_hbackDC, hOldBrush);
		SelectObject(_hbackDC, hOldPen);
	}
#endif
}
