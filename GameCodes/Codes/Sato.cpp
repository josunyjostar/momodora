#include "stdafx.h"
#include "Sato.h"
#include "Sato.inl"

CSato::CSato(void)
:m_bFilp(false)
,m_bAtkCol(true)
,m_fRollSpeed(300.f)
,m_fSpeed(0.f)
,m_fMaxSpeed(400.f)
,m_fAccel(4000.f)
,m_iHitCnt(0)
,m_fResetTime(0.f)
,m_HitPos()
{
	m_fpAI[AI_IDLE]  = &CSato::State_Idle;
	m_fpAI[AI_DODGE]  = &CSato::State_Dodge;
	m_fpAI[AI_HIT]	 = &CSato::State_Hit;
	m_fpAI[AI_ATK_1] = &CSato::State_Atk_1;
	m_fpAI[AI_ATK_2] = &CSato::State_Atk_2;
	m_fpAI[AI_ATK_3] = &CSato::State_Atk_3;
	m_fpAI[AI_ATK_4] = &CSato::State_Atk_4;
	m_fpAI[AI_DEAD]	 = &CSato::State_Dead;
}

void CSato::Hit(const float& _fDamage)
{
	if (m_iState == AI_DEAD)
		return;
	else if (m_iState == AI_DODGE)
		return;
	else if (m_iState == AI_ATK_4)
		return;

	++m_iHitCnt;
	m_fResetTime = 0.f;
	m_iState = AI_HIT;
	m_fHP	-= _fDamage;
	m_HitPos = m_Rect.Pos();

	CAniEffect::Create("HitEffect",m_bFilp,true,255)->SetEffectSize(tRect(m_Rect.Pos()+tPos(0.f,-82.f),tSize(196.f,196.f)));

	if (m_fHP < 0)
	{
		m_pAnimator->SetAlpha(true);
		m_fHP = 0;
		m_iState = AI_DEAD;
		CAniEffect::Create("Bomb",false,true,255)->SetEffectSize(tRect(tPos(m_Rect.x,m_Rect.y-60.f),tSize(276.f,256.f)));
		return;
	}

	if (m_iHitCnt > rand()%3+5)
	{
		m_iState = AI_ATK_4;
		m_iHitCnt = 0;
		return;
	}
}

void CSato::Init(void)
{
	m_Tag = TAG_ENEMY;
	m_Rect = tRect(0.f, 0.f, 128.f, 128.f, 0.5f, 1.f);
	m_OriSize  = m_Rect.Size();
	m_Atk1Size = tSize(128.f*2.5f, 128.f*2.f);
	m_Atk2Size = tSize(128.f*2.f, 128.f*2.f);
	m_Atk3Size = tSize(128.f*1.57f,128.f);
	m_fHP = m_fMaxHP = 150;

#ifdef _DEBUG
	this->AddComponent<CRenderer>();
#endif // _DEBUG

	m_pCollider = this->AddComponent<CCollider>();
	m_pAnimator = this->AddComponent<CAnimator>();
	m_pTrigger  = this->AddComponent<CTrigger>();

	m_pCollider->SetColliderRect(tRect(tPos(),m_Rect.Size()-tSize(43.f,20.f),m_Rect.Offset()));
	m_pTrigger->SetColliderRect(tRect(0.f, 0.f, 1700.f, 1700.f));
	m_pAnimator->Play("Sato_Idle");
	m_pAnimator->SetZOrder(2);
	m_pAnimator->SetReSize(true);

	m_fVelocity = 0.f;

	m_PreBehavior.push(m_fpAI[AI_IDLE]);
}

void CSato::Update(void)
{
	CMonster::Physics();

	this->Animation();

	m_fResetTime += fDeltaTime;
	m_fVelocity = 0.f;

	if (m_fResetTime > 2.f)
	{	
		m_fResetTime = 0.f;
		m_iHitCnt = 0;
	}
}

void CSato::Render(HDC _hBackDC)
{
#ifdef _DEBUG
	if (DEBUG_MODE)
	{
		static HPEN hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0,108,147));
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

void CSato::Animation(void)
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
		m_pAnimator->Play("Sato_Idle");
		break;
	case AI_DODGE:
		m_Rect.SetSize(m_OriSize);
		m_pAnimator->Play("Sato_Roll");
		break;
	case AI_DEAD:
	case AI_HIT:
		m_Rect.SetSize(m_OriSize);
		m_pAnimator->Play("Sato_Hit");
		break;
	case AI_ATK_1:
		m_Rect.SetSize(m_Atk1Size);
		m_pAnimator->Play("Sato_Atk_1");
		break;
	case AI_ATK_2:
		m_Rect.SetSize(m_Atk2Size);
		m_pAnimator->Play("Sato_Atk_2");
		break;
	case AI_ATK_3:
		m_Rect.SetSize(m_Atk3Size);
		m_pAnimator->Play("Sato_Atk_3");
		break;
	case AI_ATK_4:
		m_Rect.SetSize(m_Atk3Size);
		m_pAnimator->Play("Sato_Atk_4");
		break;
	}

	m_iPrevState = m_iState;
}
