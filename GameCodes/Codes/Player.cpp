#include "stdafx.h"
#include "Player.h"

#include "Behavior.h"
#include "Behavior_Header.inl"
#include "HitFilter.h"
#include "AfterImage.h"

CPlayer::CPlayer()
:m_pAnimator(NULL)
,m_fAccel(1500.f)
,m_fSpeed(0.f)
,m_fMaxSpeed(550.f)
,m_tOriColSize()
,m_bHitEffect(false)
{}

void CPlayer::Init(void)
{
	m_Tag = TAG_PLAYER;

	m_Rect = tRect(300.f, 650.f , 96.f*1.3f ,96.f*1.3f ,0.5f,1.f);
	m_PrevPos = m_Rect.Pos();

	m_pAnimator = this->AddComponent<CAnimator>();
	m_pAnimator->SetZOrder(1);
	m_pAnimator->Play("Momo_Idle");
	m_pAnimator->SetPlaySpeed(1.f);
	m_pAnimator->SetReSize(true);

	m_fSpeed	= 0.f;
	m_fVelocity = 0.f;

	m_fHP = m_fMaxHP = 250.f;
	m_fSP = m_fMaxSP = 150.f;

	m_pCollider = this->AddComponent<CCollider>();
	m_pCollider->SetColliderRect(tRect(tPos(),m_Rect.Size()-tSize(95.f,26.f),m_Rect.Offset()));
	m_tOriColSize = m_pCollider->GetColSize();

	this->AddComponent<CRenderer>();

	Behavior = this->AddComponent<CBehavior>();
	Behavior->Init(this,m_pAnimator);
	Behavior = &Behavior->Fall;

	AddCallbackFunc(CPlayer, AfterImage);
	AddCallbackFunc(CPlayer, AfterImageDelete);
}

void CPlayer::Update(void)
{
	//XXX: m_PrevPos 삭제금지 - 충돌처리시 방향벡터 구하는 용도 
	m_PrevPos = m_Rect.Pos();
	Behavior->Update();
	Behavior->BehaviorTransiton();
}

void CPlayer::AfterImage(const float& _fRepeatTime,const float& _fEndTime)//0.09f,0.45f
{
	StopInvoke("AfterImageDelete");	
	Repeat("AfterImage", _fRepeatTime);		
	Invoke("AfterImageDelete", _fEndTime); 
}

void CPlayer::AfterImage(void* _pData)
{
	CAfterImage::Create(m_pAnimator->GetPlayAniName(), m_pAnimator->IsFlip(), m_pAnimator->GetFrame(), 0.4f, m_Rect);
}

void CPlayer::AfterImageDelete(void* _pData)
{
	StopRepeat("AfterImage");
}

void CPlayer::Hit(const float& _iDamage)
{
	if(Behavior->m_ePreState == STATE_HIT)
		return;
	else if (Behavior->m_eState == STATE_ROLL)
		return;

	Behavior->m_eState = STATE_HIT;

	m_fHP -= _iDamage;

	if (m_fHP < 0)
		m_fHP = 0;

	m_fVelocity = 390.f;
}

const char* CPlayer::GetCurBehavior(void)
{
	return Behavior->GetRTTI()->GetClassName();
}

void CPlayer::SetBehavior(PLAYER_STATE _eState)
{
	Behavior->m_eState = _eState;
}

void CPlayer::Render(HDC _hBackDC)
{
	if (m_bHitEffect)
	{
		m_bHitEffect = false;
		CGameObject::Create<CHitFilter>()->AddComponent<CTimer>()->SetTimer(0.04f);
	}

#ifdef _DEBUG
	if (DEBUG_MODE)
	{
		static TCHAR DebugText[128];
		_stprintf_s(DebugText,sizeof(DebugText)/sizeof(TCHAR), L"CPlayer m_fVelocity: %.2f", m_fVelocity);
		TextOut(_hBackDC, 30, 150, DebugText, lstrlen(DebugText));

		tVector ptemVec =	GetVector(m_PrevPos,m_Rect.Pos());
		static TCHAR DebugText2[128];
		_stprintf_s(DebugText2,	sizeof(DebugText2)/sizeof(TCHAR), L"CPlayer Dir: %.3f %.3f", ptemVec.x,ptemVec.y);
		TextOut(_hBackDC, 30, 170, DebugText2, lstrlen(DebugText2));

		static TCHAR DebugText3[128];
		_stprintf_s(DebugText3,	sizeof(DebugText3)/sizeof(TCHAR), L"cur x: %.3f y:%.3f", m_Rect.Pos().x,m_Rect.Pos().y);
		TextOut(_hBackDC, 30, 190, DebugText3, lstrlen(DebugText3));

		static HPEN hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255,0,255));
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