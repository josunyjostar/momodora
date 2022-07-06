#ifndef BehabiorAttack_2_h__
#define BehabiorAttack_2_h__

#include "BehabiorAttack.h"

class CBehaviorAttack_2 : public CBehaviorAttack
{
	DeclRTTI(CBehaviorAttack_2,CBehaviorAttack);
public:
	explicit CBehaviorAttack_2(void){}
	virtual ~CBehaviorAttack_2(void){}
private:
	virtual void Update(void);
private:
	virtual void KeyState(void);
	virtual void Physics(void);
	virtual void Animation(void);
};

#endif // BehabiorAttack_2_h__