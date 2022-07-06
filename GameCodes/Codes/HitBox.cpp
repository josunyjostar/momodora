#include "stdafx.h"
#include "HitBox.h"

#include "Unit.h"

CHitBox::CHitBox(void)
:m_pCollider(NULL)
,m_fDamage(0.f)
{

}

void CHitBox::Ready_Object(int _iTag,float _fDamage,const tRect& _ColRect)
{
	m_Tag = _iTag;

	m_pCollider = this->AddComponent<CCollider>();
	m_pCollider->SetColType(COL_RECT);
	m_pCollider->SetColliderRect(_ColRect);
	m_pCollider->SetTag(m_Tag);

	m_fDamage = _fDamage;

	this->AddComponent<CRenderer>();
}

void CHitBox::Init(void)
{
	m_Rect.SetPos(0.f,0.f);
}

void CHitBox::Render(HDC _hBackDC)
{
#ifdef _DEBUG
	if(DEBUG_MODE)
	{
		static HPEN hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255,0,0));
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

void CHitBox::CollisionEnter(COL_INFO& _ColInfo)
{
	if(IsDynamicCast(CUnit, _ColInfo.pObj))
		((CUnit*)_ColInfo.pObj)->Hit(m_fDamage);
}

CHitBox* CHitBox::Create(CObj* _pObj,int _iTag,float _fDamage,const tRect& _ColRect)
{
	CHitBox* pHitBox = CObjectMgr::Inst().Create<CHitBox>(_pObj);
	pHitBox->Ready_Object(_iTag,_fDamage,_ColRect);
	return pHitBox;
}
