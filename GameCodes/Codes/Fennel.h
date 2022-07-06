#ifndef Fennel_h__
#define Fennel_h__

#include "Monster.h"

class CDoor;
class CBlackFilter;
class CFennel : public CMonster
{
	DeclRTTI(CFennel, CMonster);
public:
	explicit CFennel(void);
	virtual ~CFennel(void){}
private:
	typedef void (CFennel::*AI)(void);
	AI	m_fpAI[AI_TYPE_END];

	typedef void (CFennel::*ANI)(void);
	ANI		m_fpANI[AI_TYPE_END];

	typedef void (CFennel::*DODGE)(const float& _iDamage);
	DODGE	m_fpDODGE[AI_TYPE_END];

	stack<AI>	m_PreBehavior;

	bool		m_bFirst;
	bool		m_bFilp;
	bool		m_bAtkCol;
	float		m_fSpeed;
	float		m_fResetTime;
	float		m_fBuffTime;
	float		m_fAtkPower;
	int			m_iHitCnt;
	int			m_iJumpAtkDir;
	const float	m_fBasePower;
	const float	m_fAccel;
	tPos		m_HitPos;

	float		m_fRateX;
	float		m_fRateY;
	
	CBlackFilter* m_pBlackFilter;
	CDoor*		  m_pDoor;
public:
	void	SetDoor(CDoor* _pDoor) {m_pDoor = _pDoor;}
public:
	virtual	void Hit(const float& _iDamage);
	virtual void Behavior(void) {(this->*m_fpAI[m_iState])();}
private:
	virtual void Init(void);
	virtual void Update(void);
	virtual void Render(HDC _hBackDC);
private:
	void Animation(void);
	void AfterImage(const float& _fRepeatTime,const float& _fEndTime);
	void AfterImage(void* _pData);
	void AfterImageDelete(void* _pData);
private:
	virtual void TriggerEnter(CGameObject* _ColObj)
	{	
		if (m_bFirst)
		{
			if(IsDynamicCast(CPlayer, _ColObj))
			{
				m_bFirst = false;
				m_pTarget = (CPlayer*)_ColObj;
				m_iState = AI_INTRO;
			}
		}
	}

	virtual void CollisionEnter(COL_INFO& _ColInfo)
	{
		if(IsDynamicCast(CPlayer, _ColInfo.pObj))
		{
			if (m_iState == AI_DEAD)
				return;
			((CPlayer*)_ColInfo.pObj)->Hit(m_fBasePower*0.5f);
		}
	}
private:
	void State_Ready(void);
	void State_Intro(void);
	void State_Idle(void);
	void State_Impact(void);
	void State_BackFlip(void);
	void State_Dash(void);
	void State_Break(void);
	void State_Buff(void);
	void State_Jump(void);
	void State_Fall(void);
	void State_Atk_InAir(void);
	void State_DownAtk(void);
	void State_Atk_1(void);
	void State_Hit(void);
	void State_Dead(void);
private:
	void Ani_Ready(void);
	void Ani_Intro(void);
	void Ani_Idel(void);
	void Ani_Impact(void);
	void Ani_BackFlip(void);
	void Ani_Dash(void);
	void Ani_Break(void);
	void Ani_Buff(void);
	void Ani_Jump(void);
	void Ani_Fall(void);
	void Ani_Atk_InAir(void);
	void Ani_DownAtk(void);
	void Ani_Atk_1(void);
	void Ani_Hit(void);
	void Ani_Dead(void);
private:
	void BuffStart(void){m_fAtkPower += m_fBasePower;m_fBuffTime = 0.f;}
	void BuffEnd(void)	{m_fAtkPower = m_fBasePower;}
	void Jump(void);
	void Dodge(const float& _iDamage){};
	void Hurt(const float& _iDamage);
};

#endif // Fennel_h__