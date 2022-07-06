#ifndef Monster_h__
#define Monster_h__

#include "Player.h"

class CMonster abstract : public CUnit
{
	DeclRTTI(CMonster, CUnit);
public:
	explicit CMonster(void):m_pTrigger(NULL),m_pAnimator(NULL),m_pTarget(NULL),m_iState(AI_IDLE),
		m_iPrevState(AI_IDLE),m_bWallCol(false),m_fAIChangeTime(0.f),m_fDelayTime(0.f),m_fDistance_x(0.f),m_fDistance_y(0.f){}
	virtual ~CMonster(void){}
protected:		
	CTrigger*	m_pTrigger;
	CAnimator*	m_pAnimator;
	CPlayer*	m_pTarget;
	int			m_iState;
	int			m_iPrevState;
	bool		m_bWallCol;
	float		m_fAIChangeTime;
	float		m_fDelayTime;
	float		m_fDistance_x;
	float		m_fDistance_y;

protected:
	virtual void Behavior(void)PURE;
	void Physics(void)
	{
		m_PrevPos = m_Rect.Pos();

		if(m_pTarget) 
		{	
			m_fDistance_x = m_pTarget->GetPos().x -m_Rect.x;
			m_fDistance_y = m_pTarget->GetPos().y -m_Rect.y;
		}
		else
			m_fDistance_y	= m_fDistance_x = 0.f;

		m_fVelocity -= GRAVITY*fDeltaTime;
		m_Rect.y	-= m_fVelocity*fDeltaTime;

		this->Behavior();

		static float fPrevPosY = m_Rect.Pos().y;
		fPrevPosY = m_Rect.Pos().y;
		m_bWallCol = CCollisionMgr::Inst().WallColCheck(m_pCollider, GetVector(m_PrevPos, m_Rect.Pos()));

		if (m_bWallCol)
		{
			if(fPrevPosY != m_Rect.y)
			{
				if((m_fVelocity < 0.f && fPrevPosY > m_Rect.y) || (m_fVelocity >= 0.f && fPrevPosY < m_Rect.y))		
					m_fVelocity = 0.f;
			}
		}
		
	}
};

#endif // Monster_h__