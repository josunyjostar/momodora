#ifndef BehabiorDashEnd_InAir_h__
#define BehabiorDashEnd_InAir_h__

#include "BehaviorInAir.h"

class CBehaviorDashEndInAir : public CBehaviorInAir
{
	DeclRTTI(CBehaviorDashEndInAir,CBehaviorInAir);
public:
	explicit CBehaviorDashEndInAir(void):m_bColWall(false){}
	virtual ~CBehaviorDashEndInAir(void){}
private:
	bool	m_bColWall;
private:
	virtual void Update(void);
private:
	virtual void KeyState(void);
	virtual void Physics(void);
	virtual void Animation(void);
};

#endif // BehabiorDashEnd_InAir_h__