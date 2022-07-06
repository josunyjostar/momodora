#ifndef BehabiorRun_h__
#define BehabiorRun_h__

#include "BehaviorOnGround.h"

class CBehaviorRun : public CBehaviorOnGround
{
	DeclRTTI(CBehaviorRun,CBehaviorOnGround);
public:
	explicit CBehaviorRun(void){}
	virtual ~CBehaviorRun(void){}
private:
	virtual void Update(void);
private:
	virtual void KeyState(void);
	virtual void Physics(void);
	virtual void Animation(void);
};

#endif // BehabiorRun_h__