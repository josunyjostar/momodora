#include "stdafx.h"
#include "Animator.h"

CAnimator::CAnimator(void)
:m_pPlayAni(NULL)
,m_pPlayAniName(NULL)
,m_iFrame(0)
,m_fPlayTime(0.f)
,m_fPlaySpeed(1.f)
,m_bPlaying(false)
,m_bFlip(false)
,m_bResize(false)
,m_bAlpha(false)
,m_AlphaVal(255)
{

}

float CAnimator::GetAniPlayTime(char* _pAniName)
{
	float fPlayTime = 0.f;
	m_pPlayAni = CAnimationMgr::Inst().GetAni(_pAniName);

	for (int i=0; i < m_pPlayAni->iMaxFrame ;++i)
		fPlayTime += m_pPlayAni->pFrameDelay[i];

	return fPlayTime;
}


void CAnimator::Init() 
{
	m_pPlayAni		= NULL;
	m_pPlayAniName	= NULL;
	m_iFrame		= 0;
	m_bPlaying		= false;
	m_fPlaySpeed	= 1.f;
	m_fPlayTime		= 0.f;
}

void CAnimator::Render(HDC _hBackDC)
{
	if (!m_pPlayAni)
		return;

	if (m_bPlaying)
	{
		m_fPlayTime += fDeltaTime * m_fPlaySpeed;

		if (m_pPlayAni->pFrameDelay[m_iFrame] < m_fPlayTime)
		{
			m_fPlayTime  -= m_pPlayAni->pFrameDelay[m_iFrame];

			if ( m_pPlayAni->iMaxFrame - 1 > m_iFrame)
				++m_iFrame;
			else if (m_pPlayAni->bRepeat)
				m_iFrame = 0;
			else if (m_pPlayAni->pNextAni)
				this->Play(m_pPlayAni->pNextAni);
			else if(!m_pPlayAni->bRepeat)
				m_bPlaying = false;
		}
	}

	if(m_bResize)
	{
		tRect rc = m_pGameObject->GetRect();

		if(m_bAlpha) 
		{
			m_pPlayAni->Draw(_hBackDC, m_bFlip, m_iFrame,
				rc.L() - DRAWX,
				rc.T() - DRAWY,
				(int)rc.cx,
				(int)rc.cy, m_AlphaVal);
		}
		else 
		{
			m_pPlayAni->Draw(_hBackDC, m_bFlip, m_iFrame,
				rc.L() - DRAWX,
				rc.T() - DRAWY,
				(int)rc.cx,
				(int)rc.cy);
		}
	}
	else
	{
		if(m_bAlpha) 
		{
			m_pPlayAni->Draw(_hBackDC, m_bFlip, m_iFrame,
				(int)(m_pGameObject->GetPos().x - (float)DRAWX),
				(int)(m_pGameObject->GetPos().y - (float)DRAWY), m_AlphaVal);
		}
		else {
			m_pPlayAni->Draw(_hBackDC, m_bFlip, m_iFrame,
				(int)(m_pGameObject->GetPos().x - (float)DRAWX),
				(int)(m_pGameObject->GetPos().y - (float)DRAWY));
		}
	}

}

void CAnimator::Play(char* _pAniName /*= NULL*/, bool _bInit /*= true*/)
{
	m_bPlaying = true;

	if (!_pAniName)
		return;

	if (!_bInit && (_pAniName == m_pPlayAniName))
		return;

	m_iFrame = 0;
	m_fPlayTime = 0.f;
	m_pPlayAniName = _pAniName;
	m_pPlayAni = CAnimationMgr::Inst().GetAni(_pAniName);

}

void CAnimator::Stop(bool _bClear /*= false*/)
{
	if (_bClear)
		Init();
	else
		m_bPlaying = false;
}
