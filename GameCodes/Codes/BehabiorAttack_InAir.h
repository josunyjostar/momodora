#ifndef BehabiorAttack_InAir_h__
#define BehabiorAttack_InAir_h__

#include "BehabiorAttack.h"

class CBehaviorAttack_InAir : public CBehaviorAttack
{
	DeclRTTI(CBehaviorAttack_InAir,CBehaviorAttack);
public:
	explicit CBehaviorAttack_InAir(void):m_fAtkPower(5.f){}
	virtual ~CBehaviorAttack_InAir(void){}
private:
	const float m_fAtkPower;
private:
	virtual void Update(void);
private:
	virtual void KeyState(void);
	virtual void Physics(void);
	virtual void Animation(void);
};

#endif // BehabiorAttack_InAir_h__