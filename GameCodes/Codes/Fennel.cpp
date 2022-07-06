#include "stdafx.h"
#include "Fennel.h"
#include "Demon.h"
#include "MasicCircle.h"
#include "AfterImage.h"
#include "BlackFilter.h"
#include "Door.h"
#include "Fennel.inl"
#include "Fennel_Ani.inl"

CFennel::CFennel(void)
:m_bFilp(false)
,m_bFirst(true)
,m_bAtkCol(true)
,m_fSpeed(0.f)
,m_fAccel(1000.f)
,m_iHitCnt(0)
,m_fResetTime(0.f)
,m_HitPos()
,m_fAtkPower(20.f)
,m_fBasePower(20.f)
,m_fBuffTime(0.f)
,m_fRateX(0.f)
,m_fRateY(0.f)
,m_iJumpAtkDir(1)
,m_pDoor(NULL)
,m_pBlackFilter(NULL)
{
	m_fpAI[AI_READY]	= &CFennel::State_Ready;
	m_fpAI[AI_INTRO]	= &CFennel::State_Intro;
	m_fpAI[AI_IDLE]		= &CFennel::State_Idle;
	m_fpAI[AI_IMPACT]	= &CFennel::State_Impact;
	m_fpAI[AI_BACKFLIP] = &CFennel::State_BackFlip;
	m_fpAI[AI_DASH]		= &CFennel::State_Dash;
	m_fpAI[AI_BRAKE]	= &CFennel::State_Break;
	m_fpAI[AI_BUFF]		= &CFennel::State_Buff;
	m_fpAI[AI_JUMP]		= &CFennel::State_Jump;
	m_fpAI[AI_FALL]		= &CFennel::State_Fall;
	m_fpAI[AI_JUMP_ATK]	= &CFennel::State_Atk_InAir;
	m_fpAI[AI_DOWN_ATK]	= &CFennel::State_DownAtk;
	m_fpAI[AI_ATK_1]	= &CFennel::State_Atk_1;
	m_fpAI[AI_HIT]		= &CFennel::State_Hit;
	m_fpAI[AI_DEAD]		= &CFennel::State_Dead;

	m_fpDODGE[AI_INTRO]		= &CFennel::Dodge;
	m_fpDODGE[AI_IDLE]		= &CFennel::Hurt;
	m_fpDODGE[AI_IMPACT]	= &CFennel::Dodge;
	m_fpDODGE[AI_BACKFLIP]	= &CFennel::Dodge;
	m_fpDODGE[AI_DASH]		= &CFennel::Dodge;
	m_fpDODGE[AI_BRAKE]		= &CFennel::Hurt;
	m_fpDODGE[AI_BUFF]		= &CFennel::Dodge;
	m_fpDODGE[AI_JUMP]		= &CFennel::Hurt;
	m_fpDODGE[AI_FALL]		= &CFennel::Hurt;
	m_fpDODGE[AI_JUMP_ATK]	= &CFennel::Hurt;
	m_fpDODGE[AI_DOWN_ATK]	= &CFennel::Dodge;
	m_fpDODGE[AI_ATK_1]		= &CFennel::Hurt;
	m_fpDODGE[AI_HIT]		= &CFennel::Dodge;
	m_fpDODGE[AI_DEAD]		= &CFennel::Dodge;

	m_fpANI[AI_INTRO]		= &CFennel::Ani_Intro;
	m_fpANI[AI_IDLE]		= &CFennel::Ani_Idel;
	m_fpANI[AI_IMPACT]		= &CFennel::Ani_Impact;
	m_fpANI[AI_BACKFLIP]	= &CFennel::Ani_BackFlip;
	m_fpANI[AI_DASH]		= &CFennel::Ani_Dash;
	m_fpANI[AI_BRAKE]		= &CFennel::Ani_Break;
	m_fpANI[AI_BUFF]		= &CFennel::Ani_Buff;
	m_fpANI[AI_JUMP]		= &CFennel::Ani_Jump;
	m_fpANI[AI_FALL]		= &CFennel::Ani_Fall;
	m_fpANI[AI_JUMP_ATK]	= &CFennel::Ani_Atk_InAir;
	m_fpANI[AI_DOWN_ATK]	= &CFennel::Ani_DownAtk;
	m_fpANI[AI_ATK_1]		= &CFennel::Ani_Atk_1;
	m_fpANI[AI_HIT]			= &CFennel::Ani_Hit;
	m_fpANI[AI_DEAD]		= &CFennel::Ani_Dead;
}

void CFennel::Hit(const float& _iDamage)
{
	(this->*m_fpDODGE[m_iState])(_iDamage);
}

void CFennel::Init(void)
{
	m_Tag		= TAG_ENEMY;
	m_Rect		= tRect(0.f, 0.f, 118.f*2.4f, 78.f*2.4f, 0.55f, 0.67f);
	m_fHP = m_fMaxHP = 522.f;

#ifdef _DEBUG
	this->AddComponent<CRenderer>();
#endif // _DEBUG

	m_pCollider = this->AddComponent<CCollider>();
	m_pAnimator = this->AddComponent<CAnimator>();
	m_pTrigger  = this->AddComponent<CTrigger>();

	m_pCollider->SetColliderRect(tRect(tPos(),m_Rect.Size()-tSize(225.f,85.f),m_Rect.Offset()));
	m_pTrigger->SetColliderRect(tRect(0.f, 0.f, 1800.f, 1800.f));
	m_pAnimator->Play("Fennel_Idle");
	m_pAnimator->SetZOrder(1);
	m_pAnimator->SetReSize(true);

	m_fVelocity = 0.f;

	m_PreBehavior.push(m_fpAI[AI_READY]);

	AddCallbackFunc(CFennel, AfterImage);
	AddCallbackFunc(CFennel, AfterImageDelete);

	m_iState = m_iPrevState = AI_READY;
}

void CFennel::Update(void)
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

void CFennel::Render(HDC _hBackDC)
{
#ifdef _DEBUG
	if (DEBUG_MODE)
	{
		static HPEN hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(47,157,39));
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

void CFennel::Animation(void)
{
	m_bFilp = m_pAnimator->IsFlip();
	m_fBuffTime += fDeltaTime;

	if (m_bFilp)
		m_Rect.SetOffset(0.47f, 0.67f);
	else
		m_Rect.SetOffset(0.55f, 0.67f);

	if (m_iPrevState == m_iState)
		return;

	m_fAIChangeTime = 0.f;
	m_fDelayTime	= 0.f;
	m_fSpeed		= 0.f;	

	if (m_fBuffTime > 10.f)
		this->BuffEnd();

	m_PreBehavior.pop();
	m_PreBehavior.push(m_fpAI[m_iPrevState]);

	if (m_fDistance_x < 0.f)
		m_pAnimator->SetFlipX(false);
	else
		m_pAnimator->SetFlipX(true);

	(this->*m_fpANI[m_iState])();

	m_iPrevState = m_iState;
}

void CFennel::AfterImage(const float& _fRepeatTime,const float& _fEndTime)
{
	StopInvoke("AfterImageDelete");
	Repeat("AfterImage", _fRepeatTime);
	Invoke("AfterImageDelete", _fEndTime);
}

void CFennel::AfterImage(void* _pData)
{
	CAfterImage::Create(m_pAnimator->GetPlayAniName(), m_pAnimator->IsFlip(), m_pAnimator->GetFrame(), 0.4f, m_Rect);
}

void CFennel::AfterImageDelete(void* _pData)
{
	StopRepeat("AfterImage");
}


void CFennel::Jump(void)
{
	m_iState = AI_JUMP;
	m_fRateX = m_fDistance_x/(m_fDistance_x*0.6f);
	m_fRateY = m_fDistance_y/(m_fDistance_y*0.4f);

	m_fVelocity = abs(m_fDistance_x)*m_fRateX + abs(m_fDistance_y)*m_fRateY;
}

void CFennel::Hurt(const float& _iDamage)
{
	++m_iHitCnt;
	m_fResetTime = 0.f;
	m_iState = AI_HIT;
	m_fHP	-= _iDamage;
	m_HitPos = m_Rect.Pos();

	CAniEffect::Create("HitEffect",m_bFilp,true,255)->SetEffectSize(tRect(m_Rect.Pos()+tPos((m_bFilp?3.f:-3.f),-77.f),tSize(196.f,196.f)));

	if (m_fHP < 0)
	{
		m_pAnimator->SetAlpha(true);
		m_fHP = 0;
		m_iState = AI_DEAD;
		CAniEffect::Create("Bomb",false,true,255)->SetEffectSize(tRect(tPos(m_Rect.x,m_Rect.y-60.f),tSize(276.f,256.f)));

		if (m_pDoor)
			m_pDoor->UnLock();

		return;
	}

	if (m_iHitCnt > 3 + rand()%4)
	{
		switch(rand()%2)
		{
		case 0:
			m_iState = AI_DOWN_ATK;
			break;
		case 1:
			m_iState = AI_IMPACT;
			break;
		}
		m_iHitCnt = 0;
		return;
	}
}
