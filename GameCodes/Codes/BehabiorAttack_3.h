#ifndef BehabiorAttack_3_h__
#define BehabiorAttack_3_h__

#include "BehabiorAttack.h"

class CBehaviorAttack_3 : public CBehaviorAttack
{
	DeclRTTI(CBehaviorAttack_3,CBehaviorAttack);
public:
	explicit CBehaviorAttack_3(void){}
	virtual ~CBehaviorAttack_3(void){}
private:
	virtual void Update(void);
private:
	virtual void KeyState(void);
	virtual void Physics(void);
	virtual void Animation(void);
};

#endif // BehabiorAttack_3_h__