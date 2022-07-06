#ifndef BehabiorDash_h__
#define BehabiorDash_h__

#include "BehaviorOnGround.h"

class CBehaviorDash : public CBehaviorOnGround
{
	DeclRTTI(CBehaviorDash,CBehaviorOnGround);
public:
	explicit CBehaviorDash(void):m_fTime(0.29f),m_fDashSpeed(780.f){}
	virtual ~CBehaviorDash(void){}
private:
	const float	m_fDashSpeed;
	const float	m_fTime;
private:
	virtual void Update(void);
private:
	virtual void KeyState(void);
	virtual void Physics(void);
	virtual void Animation(void);
};

#endif // BehabiorDash_h__