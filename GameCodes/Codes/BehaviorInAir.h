#ifndef BehaviorInAir_h__
#define BehaviorInAir_h__

#include "Behavior.h"

class CBehaviorInAir : public CBehavior
{
	DeclRTTI(CBehaviorInAir,CBehavior);
public:
	explicit CBehaviorInAir(void){}
	virtual ~CBehaviorInAir(void){}
public:
	virtual void Update(void)
	{
		m_ColMgr.WallColCheck(m_pPlayer->m_pCollider, GetVector(m_pPlayer->m_PrevPos, m_pPlayer->m_Rect.Pos()));
	}
};

#endif // BehaviorInAir_h__