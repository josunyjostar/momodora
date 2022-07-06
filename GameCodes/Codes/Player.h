#ifndef Player_h__
#define Player_h__

#include "Player.inl"

class CPlayer : public CUnit
{
	EMPOWERMENT_BEHAVIOR;
	DeclRTTI(CPlayer,CUnit);
public:
	explicit CPlayer(void);
	virtual ~CPlayer(void){}
private:
	CBehavior*	Behavior;
private:
	CAnimator*  m_pAnimator;
	float		m_fSpeed;
	const float	m_fAccel;
	const float	m_fMaxSpeed;
	tSize		m_tOriColSize;
	bool		m_bHitEffect;
public:
	virtual void Hit(const float& _iDamage);
public:
	float		GetVelocity(void) const {return m_fVelocity;}
	const char*	GetCurBehavior(void);
	void		SetBehavior(PLAYER_STATE _eState);
public:
	virtual void	Init(void);
	virtual void	Update(void);
	virtual void	Render(HDC _hBackDC);	
private:	//CallBack
	void	AfterImage(const float& _fRepeatTime,const float& _fEndTime);
	void	AfterImage(void* _pData);
	void	AfterImageDelete(void* _pData);
};

#endif // Player_h__
