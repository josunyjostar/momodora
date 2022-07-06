#ifndef Magnolia_h__
#define Magnolia_h__

#include "Monster.h"

class CMagnolia : public CMonster
{
	DeclRTTI(CMagnolia, CMonster);
public:
	explicit CMagnolia(void);
	virtual ~CMagnolia(void){}
private:
	typedef void (CMagnolia::*AI)(void);
	AI	m_fpAI[AI_TYPE_END];

	stack<AI>	m_PreBehavior;

	bool		m_bFilp;
	bool		m_bAtkCol;
	float		m_fSpeed;
	float		m_fResetTime;
	int			m_iHitCnt;
	const float	m_fAccel;

	tPos		m_HitPos;
	tSize		m_OriSize;
	tSize		m_Atk1Size;
public:
	virtual	void Hit(const float& _fDamage);
	virtual void Behavior(void)
	{
		m_iState;
		(this->*m_fpAI[m_iState])();}
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

	virtual void CollisionEnter(COL_INFO& _ColInfo)
	{
		if(IsDynamicCast(CPlayer, _ColInfo.pObj))
		{
			if (m_iState == AI_DEAD)
				return;
			if (m_iState == AI_JUMP)
			{
				((CPlayer*)_ColInfo.pObj)->Hit(float(20+rand()%10));
				return;
			}
			((CPlayer*)_ColInfo.pObj)->Hit(10);
		}
	}
private:
	void State_Idle(void);
	void State_Jump(void);
	void State_Fall(void);
	void State_Hit(void);
	void State_Ready_Atk(void);
	void State_Atk_1(void);
	void State_Dead(void);
};

#endif // Magnolia_h__