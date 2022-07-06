#include "stdafx.h"
#include "Door.h"

CDoor::CDoor(void)
:m_pSprite(NULL)
,m_pCollider(NULL)
,m_bUnlock(false)
,m_bAlphaVal(255.f)
,m_OriPos()
{

}

void CDoor::Init(void)
{
	m_Tag = TAG_PLATFORM;

	m_Rect = tRect(0.f, 0.f, 16.f*3, 112.f*3, 0.5f, 0.5f);

#ifdef _DEBUG
	this->AddComponent<CRenderer>();
#endif // _DEBUG

	m_pSprite	= this->AddComponent<CSprite>();
	m_pSprite->SetSprite("Door");
	m_pSprite->SetResize(true);
	m_pSprite->SetLayer(LAYER_OBJECT);
	m_pSprite->SetZOrder(3);
	m_pSprite->SetAlpha(true);

	m_pCollider = this->AddComponent<CCollider>();
	m_pCollider->SetColliderRect(tRect(tPos(),m_Rect.Size(),m_Rect.Offset()));

	m_bAlphaVal = 255.f;
	m_OriPos = m_Rect.Pos();
}

void CDoor::Update(void)
{
	if (m_bUnlock)
	{
		static float fRunTime = 0.f;
		fRunTime += fDeltaTime;

		float p = pow(30.f, 10) / fRunTime;	

		m_Rect.x = m_OriPos.x + sinf(p)*1.9f;
		m_Rect.y = m_OriPos.y + cosf(p-fRunTime)*1.4f;

		m_bAlphaVal -= 150.f*fDeltaTime;

		m_pSprite->SetAlphaVal((BYTE)(m_bAlphaVal));	

		if (m_bAlphaVal < 12.f)
			this->SetActive(false);
	}
}

void CDoor::Render(HDC _hBackDC)
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
