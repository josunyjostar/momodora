#ifndef BehabiorRoll_h__
#define BehabiorRoll_h__

#include "BehaviorOnGround.h"

class CBehaviorRoll : public CBehaviorOnGround
{
	DeclRTTI(CBehaviorRoll,CBehaviorOnGround);
public:
	explicit CBehaviorRoll(void){}
	virtual ~CBehaviorRoll(void){}
private:
	virtual void Update(void);
private:
	virtual void KeyState(void);
	virtual void Physics(void);
	virtual void Animation(void);
};

#endif // BehabiorRoll_h__