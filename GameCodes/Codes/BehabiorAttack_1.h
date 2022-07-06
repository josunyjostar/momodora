#ifndef BehabiorAttack_1_h__
#define BehabiorAttack_1_h__

#include "BehabiorAttack.h"

class CBehaviorAttack_1 : public CBehaviorAttack
{
	DeclRTTI(CBehaviorAttack_1,CBehaviorAttack);
public:
	explicit CBehaviorAttack_1(void){}
	virtual ~CBehaviorAttack_1(void){}
private:
	virtual void Update(void);
private:
	virtual void KeyState(void);
	virtual void Physics(void);
	virtual void Animation(void);
};

#endif // BehabiorAttack_1_h__