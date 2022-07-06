#ifndef BehaviorOnGround_h__
#define BehaviorOnGround_h__

#include "Behavior.h"

class CBehaviorOnGround : public CBehavior
{
	DeclRTTI(CBehaviorOnGround,CBehavior);
public:
	explicit CBehaviorOnGround(void){}
	virtual ~CBehaviorOnGround(void){}
public:
	virtual void Update(void)
	{
		m_ColMgr.WallColCheck(m_pPlayer->m_pCollider, GetVector(m_pPlayer->m_PrevPos, m_pPlayer->m_Rect.Pos()));
	}
};

#endif // BehaviorOnGround_h__