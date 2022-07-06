#ifndef BehabiorBrake_h__
#define BehabiorBrake_h__

#include "BehaviorOnGround.h"

class CBehaviorBrake : public CBehaviorOnGround
{
	DeclRTTI(CBehaviorBrake,CBehaviorOnGround);
public:
	explicit CBehaviorBrake(void){}
	virtual ~CBehaviorBrake(void){}
private:
	virtual void Update(void);
private:
	virtual void KeyState(void);
	virtual void Physics(void);
	virtual void Animation(void);
};

#endif // BehabiorBrake_h__