#ifndef BehabiorHit_h__
#define BehabiorHit_h__

#include "Behavior.h"

class CBehaviorHit : public CBehavior
{
	DeclRTTI(CBehaviorHit,CBehavior);
public:
	explicit CBehaviorHit(void):m_bColWall(false),m_fRunTime(0.f){}
	virtual ~CBehaviorHit(void){}
private:
	bool	m_bColWall;
	float	m_fRunTime;
private:
	virtual void Update(void);
private:
	virtual void KeyState(void);
	virtual void Physics(void);
	virtual void Animation(void);
};

#endif // BehabiorHit_h__