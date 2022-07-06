#ifndef BehabiorDashEnd_h__
#define BehabiorDashEnd_h__

#include "BehaviorOnGround.h"

class CBehaviorDashEnd : public CBehaviorOnGround
{
	DeclRTTI(CBehaviorDashEnd,CBehaviorOnGround);
public:
	explicit CBehaviorDashEnd(void){}
	virtual ~CBehaviorDashEnd(void){}
private:
	virtual void Update(void);
private:
	virtual void KeyState(void);
	virtual void Physics(void);
	virtual void Animation(void);
};

#endif // BehabiorDashEnd_h__