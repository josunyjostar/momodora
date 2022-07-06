#ifndef Sato_h__
#define Sato_h__

#include "Monster.h"

class CSato : public CMonster
{
	DeclRTTI(CSato, CMonster);
public:
	explicit CSato(void);
	virtual ~CSato(void){}
private:
	typedef void (CSato::*AI)(void);
	AI	m_fpAI[AI_TYPE_END];

	stack<AI>	m_PreBehavior;

	bool		m_bFilp;
	bool		m_bAtkCol;
	float		m_fRollSpeed;
	float		m_fSpeed;
	float		m_fResetTime;
	int			m_iHitCnt;
	const float m_fMaxSpeed;
	const float	m_fAccel;

	tSize		m_OriSize;
	tSize		m_Atk1Size;
	tSize		m_Atk2Size;
	tSize		m_Atk3Size;
	tPos		m_HitPos;
public:
	virtual	void Hit(const float& _fDamage);
	virtual void Behavior(void){(this->*m_fpAI[m_iState])();}
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
	void State_Dodge(void);
	void State_Hit(void);
	void State_Atk_1(void);
	void State_Atk_2(void);
	void State_Atk_3(void);
	void State_Atk_4(void);
	void State_Dead(void);
};

#endif // Sato_h__