#include "stdafx.h"
#include "Magnolia.h"
#include "Magnolia.inl"

CMagnolia::CMagnolia(void)
:m_bFilp(false)
,m_bAtkCol(true)
,m_fSpeed(0.f)
,m_fAccel(1500.f)
,m_iHitCnt(0)
,m_fResetTime(0.f)
,m_HitPos()
{
	m_fpAI[AI_IDLE]		 = &CMagnolia::State_Idle;
	m_fpAI[AI_HIT]		 = &CMagnolia::State_Hit;
	m_fpAI[AI_READY_ATK] = &CMagnolia::State_Ready_Atk;
	m_fpAI[AI_ATK_1]	 = &CMagnolia::State_Atk_1;
	m_fpAI[AI_JUMP]		 = &CMagnolia::State_Jump;
	m_fpAI[AI_FALL]		 = &CMagnolia::State_Fall;
	m_fpAI[AI_DEAD]		 = &CMagnolia::State_Dead;
}

void CMagnolia::Hit(const float& _fDamage)
{
	if (m_iState == AI_DEAD)
		return;
	else if (m_iState == AI_READY_ATK)
		return;

	++m_iHitCnt;
	m_fResetTime = 0.f;
	m_iState = AI_HIT;
	m_fHP	-= _fDamage;
	m_HitPos = m_Rect.Pos();

	CAniEffect::Create("HitEffect",m_bFilp,true,255)->SetEffectSize(tRect(m_Rect.Pos()+tPos((m_bFilp?3.f:-3.f),-77.f),tSize(196.f,196.f)));

	if (m_fHP < 0)
	{
		m_pAnimator->SetAlpha(true);
		m_fHP = 0;
		m_iState = AI_DEAD;
		CAniEffect::Create("Bomb",false,true,255)->SetEffectSize(tRect(tPos(m_Rect.x,m_Rect.y-60.f),tSize(276.f,256.f)));
		return;
	}

	if (m_iHitCnt > rand()%3+3)
	{
		m_iState = AI_READY_ATK;
		m_iHitCnt = 0;
		return;
	}
}

void CMagnolia::Init(void)
{
	m_Tag		= TAG_ENEMY;
	m_Rect		= tRect(0.f, 0.f, 128.f, 128.f, 0.5f, 1.f);
	m_OriSize	= m_Rect.Size();
	m_Atk1Size	= tSize(128.f*1.9f, 128.f*1.1f);
	m_fHP = m_fMaxHP = 122;

#ifdef _DEBUG
	this->AddComponent<CRenderer>();
#endif // _DEBUG

	m_pCollider = this->AddComponent<CCollider>();
	m_pAnimator = this->AddComponent<CAnimator>();
	m_pTrigger  = this->AddComponent<CTrigger>();

	m_pCollider->SetColliderRect(tRect(tPos(),m_Rect.Size()-tSize(43.f,20.f),m_Rect.Offset()));
	m_pTrigger->SetColliderRect(tRect(0.f, 0.f, 1200.f, 1200.f));
	m_pAnimator->Play("Magnolia_Idle");
	m_pAnimator->SetZOrder(3);
	m_pAnimator->SetReSize(true);

	m_fVelocity = 0.f;

	m_PreBehavior.push(m_fpAI[AI_IDLE]);
}

void CMagnolia::Update(void)
{
	CMonster::Physics();

	this->Animation();

	m_fResetTime += fDeltaTime;

	if (m_fResetTime > 2.f)
	{	
		m_fResetTime = 0.f;
		m_iHitCnt = 0;
	}
}

void CMagnolia::Render(HDC _hBackDC)
{
#ifdef _DEBUG
	if (DEBUG_MODE)
	{
		static HPEN hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255,94,0));
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

		rc = m_pTrigger->GetColRect();
		Ellipse(_hBackDC, 
			int(rc.L()) - DRAWX,
			int(rc.T()) - DRAWY,
			int(rc.R()) - DRAWX,
			int(rc.B()) - DRAWY);

		SelectObject(_hBackDC, hOldBrush);
		SelectObject(_hBackDC, hOldPen);
	}
#endif
}

void CMagnolia::Animation(void)
{
	m_bFilp = m_pAnimator->IsFlip();

	if (m_iPrevState == m_iState)
		return;

	m_fAIChangeTime = 0.f;
	m_fDelayTime	= 0.f;
	m_fSpeed		= 0.f;	

	m_PreBehavior.pop();
	m_PreBehavior.push(m_fpAI[m_iPrevState]);

	switch(m_iState)
	{
	case AI_IDLE:
		m_fAIChangeTime = 1.5f;
		m_Rect.SetSize(m_OriSize);
		m_pAnimator->Play("Magnolia_Idle");
		break;
	case AI_READY_ATK:
		m_pAnimator->SetAlpha(true);
		m_Rect.SetSize(m_OriSize);
		m_pAnimator->Play("Magnolia_Ready_Atk");
		break;
	case AI_JUMP:
		m_pAnimator->SetAlphaVal((BYTE)(255));
		m_pAnimator->SetAlpha(false);
		m_fVelocity = 700.f + rand()%200+100;
		m_Rect.SetSize(m_OriSize);
		m_pAnimator->Play("Magnolia_Jump");
		break;
	case AI_FALL:
		m_Rect.SetSize(m_OriSize);
		m_pAnimator->Play("Magnolia_Fall");
		break;
	case AI_DEAD:
	case AI_HIT:
		m_Rect.SetSize(m_OriSize);
		m_pAnimator->Play("Magnolia_Hit");
		break;
	case AI_ATK_1:
		m_Rect.SetSize(m_Atk1Size);
		m_pAnimator->Play("Magnolia_Atk");
		break;
	}

	m_iPrevState = m_iState;
}

