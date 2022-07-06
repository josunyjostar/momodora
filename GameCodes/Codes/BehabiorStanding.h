#ifndef BehabiorStanding_h__
#define BehabiorStanding_h__

#include "BehaviorOnGround.h"

class CBehaviorStanding : public CBehaviorOnGround
{
	DeclRTTI(CBehaviorStanding,CBehaviorOnGround);
public:
	explicit CBehaviorStanding(void){}
	virtual ~CBehaviorStanding(void){}
private:
	virtual void Update(void);
private:
	virtual void KeyState(void);
	virtual void Physics(void);
	virtual void Animation(void);
};

#endif // BehabiorStanding_h__