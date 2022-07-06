#include "stdafx.h"
#include "NextStageTrigger.h"

#include "InfoMgr.h"

void CNextStageTrigger::SetTrigger(const tRect& _tRect,CSceneMgr::SCENE_TYPE _eScene)
{
	m_Tag = TAG_PLATFORM;

	m_pTrigger = this->AddComponent<CTrigger>();
	m_pTrigger->SetColliderRect(_tRect);

	m_eScene = _eScene;

#ifdef _DEBUG
	this->AddComponent<CRenderer>();
#endif
}

void CNextStageTrigger::Render(HDC _hBackDC)
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

void CNextStageTrigger::TriggerEnter(CGameObject* _ColObj)
{
	if (IsDynamicCast(CPlayer,_ColObj))
	{
		CInfoMgr::Inst().SaveInfo((CPlayer*)_ColObj);
		CSceneMgr::Inst().SetScene(m_eScene);
	}
}
