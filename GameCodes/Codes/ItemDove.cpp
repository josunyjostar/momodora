#include "stdafx.h"
#include "ItemDove.h"

#include "Dove.h"

CItemDove::CItemDove(void)
:m_pAnimator(NULL)
,m_pSprite(NULL)
,m_pCollider(NULL)
{

}

void CItemDove::Init(void)
{
	m_Tag = TAG_ITEM;
	
	m_Rect = tRect(0.f, 0.f, 40.f, 42.f, 0.01f, 0.6f);

	this->AddComponent<CRenderer>();
	m_pSprite	= CSpriteMgr::Inst().GetSprite("Nest");

	m_pAnimator = this->AddComponent<CAnimator>();
	m_pAnimator->Play("ItemDove");
	m_pAnimator->SetZOrder(4);
	m_pAnimator->SetLayer(LAYER_OBJECT);
	m_pAnimator->SetReSize(true);
	m_pAnimator->SetPlaySpeed(0.4f);

	m_pCollider = this->AddComponent<CCollider>();
	m_pCollider->SetColliderRect(tRect(tPos(),m_Rect.Size(),m_Rect.Offset()));
}

void CItemDove::Render(HDC _hBackDC)
{
	m_pSprite->Draw(_hBackDC,
		int(m_Rect.Pos().x - DRAWX),
		int(m_Rect.Pos().y - DRAWY),
		40,
		20
		);

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

void CItemDove::CollisionEnter(COL_INFO& _ColInfo)
{
	if(IsDynamicCast(CPlayer, _ColInfo.pObj))
	{
		this->SetActive(false);

		CDove* pDove = CGameObject::Create<CDove>();
		pDove->SetPos(_ColInfo.pObj->GetPos()+tPos(0.f,-200.f));
		pDove->SetPlayer(_ColInfo.pObj);
		pDove->SetMoveMode(CDove::MOVE_PLAYER_AROUND);
		CInfoMgr::Inst().m_bDove = true;
	}
}
