#ifndef BehabiorAttack_h__
#define BehabiorAttack_h__

#include "BehaviorOnGround.h"

class CBehaviorAttack : public CBehaviorOnGround
{
	DeclRTTI(CBehaviorAttack,CBehaviorOnGround);
public:
	explicit CBehaviorAttack(void):m_bNextAtk(false),m_bAtkCol(true),m_pEffect(NULL),m_bCreateEffect(true){}
	virtual ~CBehaviorAttack(void){}
protected:
	CAniEffect* m_pEffect;
	bool		m_bCreateEffect;
	bool		m_bNextAtk;
	bool		m_bAtkCol;
protected:
	virtual void Physics(void)
	{
		this->Gravity();

		static float fPrevPosY = m_pPlayer->m_Rect.Pos().y;
		fPrevPosY = m_pPlayer->m_Rect.Pos().y;

		if (CCollisionMgr::Inst().WallColCheck(m_pPlayer->m_pCollider, GetVector(m_pPlayer->m_PrevPos, m_pPlayer->m_Rect.Pos())))
		{
			if (fPrevPosY != m_pPlayer->m_Rect.y)
			{
				if((m_pPlayer->m_fVelocity < 0.f && fPrevPosY > m_pPlayer->m_Rect.y) || (m_pPlayer->m_fVelocity >= 0.f && fPrevPosY < m_pPlayer->m_Rect.y))		
					m_pPlayer->m_fVelocity = 0.f;
			}
		}
	}
};

#endif // BehabiorAttack_1_h__