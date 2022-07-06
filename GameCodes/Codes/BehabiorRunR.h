#ifndef BehabiorRunR_h__
#define BehabiorRunR_h__

#include "Behavior.h"

class CBehaviorRunR : public CBehavior
{
	DeclRTTI(CBehaviorRunR,CBehavior);
public:
	explicit CBehaviorRunR(void){}
	virtual ~CBehaviorRunR(void){}
private:
	virtual void Update(void);
private:
	virtual void KeyState(void);
	virtual void Physics(void);
	virtual void Animation(void);
};

#endif // BehabiorRunR_h__