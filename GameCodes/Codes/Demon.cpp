#include "stdafx.h"
#include "Demon.h"
#include "Explosion.h"
#include "SceneMgr.h"
CDemon::CDemon(void)
:m_fLifeTime(0.f)
,m_fDelayTime(0.f)
,m_pAnimator(NULL)
,m_pTrigger(NULL)
,m_pTarget(NULL)
,m_fVelocity(0.f)
,m_iState(0)
,m_iPrevState(0)
,m_ShakePos()
{
	m_fpDEMON[DS_JUMP]	= &CDemon::State_Jump;
	m_fpDEMON[DS_FALL]	= &CDemon::State_Fall;
	m_fpDEMON[DS_ATK]	= &CDemon::State_Atk;
}

void CDemon::Ready_Object(const float& _fVelocity,bool _bFilp)
{
	m_Tag	= TAG_EFFECT;
	m_Rect	= tRect(tPos(), tSize(246.f*0.9f, 316.f*0.9f));

	m_pAnimator = this->AddComponent<CAnimator>();
	m_pAnimator->SetZOrder(5);
	m_pAnimator->SetReSize(true);
	m_pAnimator->SetAlpha(true);
	m_pAnimator->SetFlipX(_bFilp);
	m_pAnimator->Play("Demon_jump");

	this->AddComponent<CRenderer>();

	m_pTrigger = this->AddComponent<CTrigger>();
	m_pTrigger->SetColliderRect(tRect(0.f, 0.f, 1500.f, 1500.f));

	m_fVelocity	 = _fVelocity;
	m_fDelayTime = 0.f;
	m_fLifeTime	 = m_fVelocity/(m_fVelocity*0.2f);

	m_iState = m_iPrevState = DS_JUMP;
}

void CDemon::Update(void)
{
	(this->*m_fpDEMON[m_iState])();

	if (m_iPrevState == m_iState)
		return;

	switch(m_iState)
	{
	case DS_FALL:
		m_ShakePos = m_Rect.Pos();
		m_pAnimator->Play("Demon_Fall");
		break;
	case DS_ATK:
		CCamera::Inst().Shake(m_fLifeTime-m_fDelayTime*2.f);
		if(m_pTarget)
			CExplosion::Create(m_pTarget->GetPos());
		m_pAnimator->Play("Demon_Atk");
		break;
	}

	m_iPrevState = m_iState;
}

void CDemon::Render(HDC _hBackDC)
{
	m_fDelayTime += fDeltaTime;

	if(m_fDelayTime > m_fLifeTime)
		this->SetActive(false);
	else
		m_pAnimator->SetAlphaVal((BYTE)(255.f* (m_fLifeTime-m_fDelayTime)/(m_fLifeTime)));	

#ifdef _DEBUG
	if (DEBUG_MODE)
	{
		static HPEN hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(184,84,105));
		static HPEN hOldPen;
		static HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		static HBRUSH hOldBrush;

		hOldBrush = (HBRUSH)SelectObject(_hBackDC, hBrush);
		hOldPen = (HPEN)SelectObject(_hBackDC, hPen);

		tRect rc = m_pTrigger->GetColRect();
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

void CDemon::TriggerEnter(CGameObject* _ColObj)
{
	if(IsDynamicCast(CPlayer, _ColObj))
		m_pTarget = _ColObj;
}

void CDemon::State_Jump(void)
{
	m_fVelocity -= GRAVITY*fDeltaTime;
	m_Rect.y	-= m_fVelocity*fDeltaTime;

	if (!m_pAnimator->IsPlay())
	{
		if (m_Rect.y+152.f > CSceneMgr::Inst().GetGroundHeight())
			m_iState = DS_FALL;
	}
}

void CDemon::State_Fall(void)
{
	float p = pow(10.f,5) / m_fDelayTime;

	m_Rect.x = m_ShakePos.x + sin(p)*3.5f;
	m_Rect.y = m_ShakePos.y - cos(p)*4.7f;

	if (m_fDelayTime > m_fLifeTime*0.3f)
		m_iState = DS_ATK;
}

void CDemon::State_Atk(void)
{
	float p = pow(10.f,5) / m_fDelayTime;

	m_Rect.x = m_ShakePos.x + sin(p)*3.5f;
	m_Rect.y = m_ShakePos.y - cos(p)*4.7f;
}

CDemon* CDemon::Create(const float& _fVelocity,bool _bFilp)
{
	CDemon* pTemp = CGameObject::Create<CDemon>();
	pTemp->Ready_Object(_fVelocity,_bFilp);

	return pTemp;
}
