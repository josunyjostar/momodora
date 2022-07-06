#ifndef Imp_h__
#define Imp_h__

#include "Monster.h"

class CImp : public CMonster
{
	DeclRTTI(CImp, CMonster);
public:
	explicit CImp(void);
	virtual ~CImp(void){}
private:
	typedef void (CImp::*AI)(void);
	AI	m_fpAI[AI_TYPE_END];

	const float	m_fAtkDis;
	int			m_iRandValue;
	float		m_fJumpValue;
	float		m_fWalkSpeed;

	bool		m_bFilp;
	bool		m_bThrowKnife;
	tPos		m_HitPos;
public:
	virtual void Hit(const float& _fDamage);
	virtual void Behavior(void) {(this->*m_fpAI[m_iState])();}
private:
	virtual void Init(void);
	virtual void Update(void);
	virtual void Render(HDC _hBackDC);
private:
	void Animation(void);
private:
	virtual void TriggerEnter(CGameObject* _ColObj)
	{	
		if(IsDynamicCast(CPlayer, _ColObj))
			m_pTarget = (CPlayer*)_ColObj;
	}

	virtual void TriggerExit(CGameObject* _ColObj)
	{
		if(m_pTarget == _ColObj)
			m_pTarget = NULL;
	}


	virtual void CollisionEnter(COL_INFO& _ColInfo)
	{
		if(IsDynamicCast(CPlayer, _ColInfo.pObj))
		{
			if (m_iState == AI_DEAD)
				return;

			((CPlayer*)_ColInfo.pObj)->Hit(10);
		}
	}
private:
	void State_Idle(void);
	void State_Fall(void);
	void State_Jump(void);
	void State_Throw(void);
	void State_ShiedWalk(void);
	void State_Atk_1(void);
	void State_Hit(void);
	void State_Dead(void);
};

#endif // Imp_h__