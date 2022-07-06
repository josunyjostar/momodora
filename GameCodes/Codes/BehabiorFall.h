#ifndef BehabiorFall_h__
#define BehabiorFall_h__

#include "BehaviorInAir.h"

class CBehaviorFall : public CBehaviorInAir
{
	DeclRTTI(CBehaviorFall,CBehaviorInAir);
public:
	explicit CBehaviorFall(void):m_bColWall(false){}
	virtual ~CBehaviorFall(void){}
private:
	bool	m_bColWall;
private:
	virtual void Update(void);
private:
	virtual void KeyState(void);
	virtual void Physics(void);
	virtual void Animation(void);
};

#endif // BehabiorFall_h__