#include "stdafx.h"
#include "Knife.h"

CKnife::CKnife(void)
:m_fSpeed(950.f)
,m_pAnimator(NULL)
,m_pCollider(NULL)
,m_bFilp(false)
,m_fDamage(10.f)
{

}

void CKnife::Init(void)
{
	m_Tag = TAG_ENEMY;

	m_Rect = tRect(0.f, 0.f, 48.f, 48.f, 0.5f, 0.55f);

	m_pAnimator = this->AddComponent<CAnimator>();
	m_pAnimator->Play("Knife");
	m_pAnimator->SetReSize(true);
	
	m_pCollider = this->AddComponent<CCollider>();
	m_pCollider->SetColliderRect(tRect(tPos(),m_Rect.Size()-tSize(10.f,24.f),m_Rect.Offset()));

#ifdef _DEBUG
	this->AddComponent<CRenderer>();
#endif // _DEBUG

	this->AddComponent<CTimer>()->SetTimer(5.f);
}

void CKnife::Update(void)
{
	static tPos PrevPos = m_Rect.Pos();
	PrevPos = m_Rect.Pos();

	if (m_bFilp)
	{
		m_pAnimator->SetFlipX(true);
		m_Rect.x -= m_fSpeed * fDeltaTime;
	}
	else
	{	
		m_pAnimator->SetFlipX(false);
		m_Rect.x += m_fSpeed * fDeltaTime;
	}

	CCollisionMgr::Inst().WallColCheck(m_pCollider,GetVector(PrevPos,m_Rect.Pos()));
}

void CKnife::Render(HDC _hBackDC)
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

void CKnife::CollisionEnter(COL_INFO& _ColInfo)
{
	if (IsDynamicCast(CPlayer,_ColInfo.pObj))
	{
		if (((CPlayer*)_ColInfo.pObj)->GetCurBehavior() != "CBehaviorRoll")
		{
			((CPlayer*)_ColInfo.pObj)->Hit(m_fDamage);
			this->DeleteComponent<CTimer>();
			this->SetActive(false);
		}
	}
}
