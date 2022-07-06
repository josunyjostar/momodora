#include "stdafx.h"
#include "Crystal.h"

#include "Dove.h"

CCrystal::CCrystal(void)
:m_fDir(7.f)
,m_pAnimator(NULL)
,m_pCollider(NULL)
{

}

void CCrystal::Init(void)
{
	m_Tag = TAG_ITEM;
	
	m_Rect = tRect(0.f, 0.f, 30.f, 40.f, 0.5f, 0.5f);
#ifdef _DEBUG
	this->AddComponent<CRenderer>();
#endif

	m_pAnimator = this->AddComponent<CAnimator>();
	m_pAnimator->Play("Crystal2");
	m_pAnimator->SetZOrder(4);
	m_pAnimator->SetLayer(LAYER_OBJECT);
	m_pAnimator->SetReSize(true);
	m_pAnimator->SetPlaySpeed(1.f);

	m_pCollider = this->AddComponent<CCollider>();
	m_pCollider->SetColliderRect(tRect(tPos(),m_Rect.Size(),m_Rect.Offset()));

	if (rand()%2)
		m_fDir *= -1.f;
}

void CCrystal::Update(void)
{
	static float y  = 0.f;
	y += fDeltaTime*0.1f;

	m_Rect.y += m_fDir*sinf(y)*0.05f;

}
void CCrystal::Render(HDC _hBackDC)
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

void CCrystal::CollisionEnter(COL_INFO& _ColInfo)
{
	if(IsDynamicCast(CPlayer, _ColInfo.pObj) || IsDynamicCast(CDove, _ColInfo.pObj))
	{
		this->SetActive(false);
		CAniEffect::Create("Sparkle",false,false,255)->SetEffectSize(tRect(m_Rect.Pos(),tSize(96.f,96.f)));
		CFontMgr::Inst().AddCoin(1);		
	}
}
