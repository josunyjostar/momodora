#ifndef Behavior_h__
#define Behavior_h__

#include "Player.inl"

class CBehavior :public CComponent
{
	friend CPlayer;
	DeclRTTI(CBehavior,CComponent);
public:
	explicit CBehavior(void);
	virtual ~CBehavior(void){}
public:
	static CBehaviorStanding		Standing;
	static CBehaviorRun				Run;
	static CBehaviorBrake			Brake;
	static CBehaviorRoll			Roll;
	static CBehaviorTurn			Turn;
	static CBehaviorJump			Jump;
	static CBehaviorFall			Fall;
	static CBehaviorDash			Dash;
	static CBehaviorDashEnd			DashEnd;
	static CBehaviorDashEndInAir	DashEnd_InAir;
	static CBehaviorAttack_1		Atk_1;
	static CBehaviorAttack_2		Atk_2;
	static CBehaviorAttack_3		Atk_3;
	static CBehaviorAttack_InAir	Atk_InAir;
	static CBehaviorHit				Hit;
	static CBehaviorPray			Pray;
	static CBehaviorRunR			RunR;
protected:
	CCollisionMgr&		m_ColMgr;
	static CAnimator*	m_pAnimator;
	static CPlayer*		m_pPlayer;
	static CKeyState*	m_pKey;

	static PLAYER_STATE			m_ePreState;
	static PLAYER_STATE			m_eState;
	static queue<CBehavior*>	m_qBehavior;

	static bool					m_bDoubleJump;

	typedef void (CBehavior::*ANI)(void);
	ANI		m_fpANI[PLAYER_STATE_END];
public:
	void Init(CPlayer* _pPlayer,CAnimator* _pAnimator) 
	{
		m_pPlayer	=_pPlayer;
		m_pAnimator =_pAnimator;
		m_ePreState = m_eState = STATE_FALL;
		m_bDoubleJump = true;
	}
	virtual void Update(void){}
	void		 BehaviorTransiton(void);
protected:
	void		 Gravity(void);
	void		 DoubleJump(void);
protected:
	virtual void KeyState(void){}
	virtual void Physics(void){}
	virtual void Animation(void){}
private:
	void Ani_Idel(void);
	void Ani_Run(void);
	void Ani_Roll(void);
	void Ani_Brake(void);
	void Ani_Jump(void);
	void Ani_Fall(void);
	void Ani_Dash(void);
	void Ani_Dash_End(void);
	void Ani_Dash_End_Air(void);
	void Ani_Atk_1(void);
	void Ani_Atk_2(void);
	void Ani_Atk_3(void);
	void Ani_Atk_InAir(void);
	void Ani_Hit(void);
	void Ani_Pray(void);
	void Ani_RunR(void);
};

#endif // Behavior_h__