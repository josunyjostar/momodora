#include "stdafx.h"
#include "AniEffect.h"

CAniEffect::CAniEffect(void)
:m_AlphaValue(255)
,m_bAlpha(false)
,m_pEffectName(NULL)
,m_pAnimator(NULL)
,m_fLifeTime(0.f)
,m_fDelayTime(0.f)
{

}

void CAniEffect::SetEffectSize(tRect _tRect)
{
	m_Rect = _tRect;
	m_pAnimator->SetReSize(true);
}

void CAniEffect::SetRenderOrder(LAYER_TYPE _eLayer,int _iZOrder)
{
	m_pAnimator->SetZOrder(_iZOrder);
	m_pAnimator->SetLayer(_eLayer);
}

void CAniEffect::Ready_Effect(char* _pEffectName, bool _bFilp,bool _Alpha, BYTE _StartAlphaValue,float _fLifeTime)
{
	m_Tag = TAG_EFFECT;

	m_pEffectName = _pEffectName;
	m_pAnimator = this->AddComponent<CAnimator>();
	m_pAnimator->SetZOrder(0);
	m_pAnimator->SetLayer(LAYER_EFFECT);

	m_fDelayTime = 0.f;
	m_bAlpha	 = _Alpha;
	m_AlphaValue = _StartAlphaValue;

	if (_fLifeTime == 0.f)
		m_fLifeTime = m_pAnimator->GetAniPlayTime(_pEffectName);
	else
		m_fLifeTime	= _fLifeTime+0.005f;

	m_pAnimator->Play(_pEffectName);
	m_pAnimator->SetAlpha(m_bAlpha);
	m_pAnimator->SetFlipX(_bFilp);
}

void CAniEffect::Update(void)
{
	m_fDelayTime += fDeltaTime;

	if(m_fDelayTime > m_fLifeTime)
		this->SetActive(false);
	else if (m_bAlpha)
		m_pAnimator->SetAlphaVal((BYTE)((float)m_AlphaValue* (m_fLifeTime-m_fDelayTime)/m_fLifeTime));	
}

CAniEffect* CAniEffect::Create(char* _pEffectName, bool _bFilp,bool _Alpha, BYTE _StartAlphaValue,float _fLifeTime /*= 0.f*/)
{
	CAniEffect* pEffect = CObjectMgr::Inst().Create<CAniEffect>();
	pEffect->Ready_Effect(_pEffectName,_bFilp,_Alpha,_StartAlphaValue,_fLifeTime);
	return pEffect;
}	

