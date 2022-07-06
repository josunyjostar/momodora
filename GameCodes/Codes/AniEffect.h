#ifndef AniEffect_h__
#define AniEffect_h__

class CAniEffect : public CGameObject
{
	friend CObjectMgr;
	DeclRTTI(CAniEffect,CGameObject);
private:
	explicit CAniEffect(void);
	virtual ~CAniEffect(void) {}
public:
	void		SetEffectSize(tRect _tRect);
	void		SetRenderOrder(LAYER_TYPE _eLayer,int _iZOrder);
private:
	bool		m_bAlpha;
	char*		m_pEffectName;
	BYTE		m_AlphaValue;
	float		m_fLifeTime;
	float		m_fDelayTime;
	CAnimator*  m_pAnimator;
private:
	void		 Ready_Effect(char* _pEffectName, bool _bFilp,bool _Alpha, BYTE _StartAlphaValue,float _fLifeTime);
	virtual	void Update(void);
public:
	static CAniEffect* Create(char* _pEffectName, bool _bFilp,bool _Alpha, BYTE _StartAlphaValue,float _fLifeTime = 0.f);
	//_fLifeTime == 0 -> _fLifeTime == Total AniPlayTime
};

#endif // AniEffect_h__