#include "stdafx.h"
#include "Imp.h"
#include "Knife.h"
#include "Imp.inl"

CImp::CImp(void)
:m_iRandValue(1)
,m_fAtkDis(150.f)
,m_bThrowKnife(false)
,m_fJumpValue(400.f)
,m_fWalkSpeed(80.f)
,m_bFilp(false)
,m_HitPos()
{
	m_fpAI[AI_IDLE]  = &CImp::State_Idle;
	m_fpAI[AI_FALL]  = &CImp::State_Fall;
	m_fpAI[AI_JUMP]	 = &CImp::State_Jump;
	m_fpAI[AI_THROW] = &CImp::State_Throw;
	m_fpAI[AI_WALK]  = &CImp::State_ShiedWalk;
	m_fpAI[AI_ATK_1] = &CImp::State_Atk_1;
	m_fpAI[AI_HIT]	 = &CImp::State_Hit;
	m_fpAI[AI_DEAD]	 = &CImp::State_Dead;
}

void CImp::Hit(const float& _fDamage)
{
	if (m_iState == AI_DEAD)
		return;

	m_iState = AI_HIT;
	m_fHP -= _fDamage;
	m_fVelocity = 300.f;
	m_HitPos = m_Rect.Pos();

	m_bFilp = m_pAnimator->IsFlip();

	CAniEffect::Create("HitEffect",m_bFilp,true,255)->SetEffectSize(tRect(m_Rect.Pos()+tPos((m_bFilp?10.f:-10.f),-45.f),tSize(96.f,96.f)));

	if (m_fHP < 0)
	{
		m_pAnimator->SetAlpha(true);
		m_fHP = 0;
		m_iState = AI_DEAD;
		CAniEffect::Create("Bomb",false,true,255)->SetEffectSize(tRect(tPos(m_Rect.x,m_Rect.y-20.f),tSize(74.f,64.f)));
	}
}

void CImp::Init(void)
{
	m_Tag = TAG_ENEMY;
	m_Rect = tRect(0.f, 0.f, 74.f, 74.f, 0.5f, 1.f);

	m_fHP = m_fMaxHP = 35;

#ifdef _DEBUG
	this->AddComponent<CRenderer>();
#endif // _DEBUG

	m_pCollider = this->AddComponent<CCollider>();
	m_pAnimator = this->AddComponent<CAnimator>();
	m_pTrigger  = this->AddComponent<CTrigger>();

	m_pCollider->SetColliderRect(tRect(tPos(),m_Rect.Size()-tSize(30.f,21.f),m_Rect.Offset()));
	m_pTrigger->SetColliderRect(tRect(0.f, 0.f, 1300.f, 1300.f));
	m_pAnimator->Play("Imp_Idle");
	m_pAnimator->SetReSize(true);

	m_fVelocity = 0.f;
}

void CImp::Update(void)
{
	CMonster::Physics();

	this->Animation();
}

void CImp::Animation(void)
{
	if (m_iPrevState == m_iState)
		return;

	m_iRandValue	= rand()%200+150;
	m_fAIChangeTime = 0.f;
	m_fDelayTime	= 0.f;
	m_fAIChangeTime = 0.f;

	switch(m_iState)
	{
	case AI_IDLE:
		m_fAIChangeTime = (rand()%5+1)*0.1f;
		m_pAnimator->Play("Imp_Idle");
		break;
	case AI_WALK:
		m_fAIChangeTime = 1.5f;// (rand()%40+10)*0.1f;
		m_pAnimator->Play("Imp_ShieldWalk");
		break;
	case AI_JUMP:
		m_fAIChangeTime = (rand()%40+15)*0.01f;
		m_pAnimator->Play("Imp_Jump");
		break;
	case AI_FALL:
		m_pAnimator->Play("Imp_Fall");
		break;
	case AI_DEAD:
	case AI_HIT:
		m_pAnimator->Play("Imp_Hit");
		break;
	case AI_THROW:
		m_bThrowKnife = true;
		m_pAnimator->Play("Imp_ThrowKnife");
		break;
	case AI_ATK_1:
		m_pAnimator->Play("Imp_MeleeAtk");
		break;
	}

	m_iPrevState = m_iState;
}

void CImp::Render(HDC _hBackDC)
{
#ifdef _DEBUG
	if (DEBUG_MODE)
	{
		static HPEN hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255,228,0));
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



