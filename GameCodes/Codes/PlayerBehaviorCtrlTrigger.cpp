#include "stdafx.h"
#include "PlayerBehaviorCtrlTrigger.h"

void CPlayerBehaviorCtrlTigger::SetTrigger(const tRect& _tRect,PLAYER_STATE _eState)
{
	m_Tag = TAG_PLATFORM;

	m_pTrigger = this->AddComponent<CTrigger>();
	m_pTrigger->SetColliderRect(_tRect);

	m_eStare = _eState;

#ifdef _DEBUG
	this->AddComponent<CRenderer>();
#endif
}

void CPlayerBehaviorCtrlTigger::Render(HDC _hBackDC)
{
#ifdef _DEBUG
	if(DEBUG_MODE)
	{
		static HPEN hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0,0,255));
		static HPEN hOldPen;
		static HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		static HBRUSH hOldBrush;

		hOldBrush = (HBRUSH)SelectObject(_hBackDC, hBrush);
		hOldPen = (HPEN)SelectObject(_hBackDC, hPen);
		tRect rc = m_pTrigger->GetColRect();
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

void CPlayerBehaviorCtrlTigger::TriggerEnter(CGameObject* _ColObj)
{
	if (IsDynamicCast(CPlayer,_ColObj))
	{
		((CPlayer*)_ColObj)->SetBehavior(m_eStare);
	}
}
