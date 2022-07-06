#include "stdafx.h"
#include "Activator.h"

CActivator::CActivator(void)
:m_pCollider(NULL)
,m_pTarget(NULL)
,m_ColSize(0.f,0.f)
{
	
}

void CActivator::Init(void)
{
	m_Tag = TAG_ENEMY;

#ifdef _DEBUG
	this->AddComponent<CRenderer>();
#endif // _DEBUG
	m_pCollider  = this->AddComponent<CCollider>();
	m_pCollider->SetColliderRect(tRect(tPos(0.f,0.f), m_ColSize));
}

void CActivator::Update(void)
{
	if (m_pTarget)
		this->SetPos(m_pTarget->GetPos());
}
void CActivator::Render(HDC _hBackDC)
{
#ifdef _DEBUG
	if (DEBUG_MODE)
	{
		static HPEN hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(236,105,65));
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