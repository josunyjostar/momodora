#ifndef BehabiorJump_h__
#define BehabiorJump_h__

#include "BehaviorOnGround.h"

class CBehaviorJump : public CBehaviorOnGround
{
	DeclRTTI(CBehaviorJump,CBehaviorOnGround);
public:
	explicit CBehaviorJump(void):m_bColWall(false){}
	virtual ~CBehaviorJump(void){}
private:
	bool	m_bColWall;
private:
	virtual void Update(void);
private:
	virtual void KeyState(void);
	virtual void Physics(void);
	virtual void Animation(void);
};

#endif // BehabiorJump_h__