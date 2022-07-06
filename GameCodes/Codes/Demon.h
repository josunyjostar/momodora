#ifndef Demon_h__
#define Demon_h__

class CPlayer;
class CDemon : public CGameObject
{
	friend CObjectMgr;
	DeclRTTI(CDemon, CGameObject);
	enum DEMON_STATE {DS_JUMP,DS_FALL,DS_ATK,DS_END};
private:
	explicit CDemon(void);
	virtual ~CDemon(void) {}
private:
	int				m_iState;
	int				m_iPrevState;
	float			m_fLifeTime;
	float			m_fDelayTime;
	float			m_fVelocity;
	CAnimator*  	m_pAnimator;
	CTrigger*		m_pTrigger;
	CGameObject*	m_pTarget;
	tPos			m_ShakePos;

	typedef void (CDemon::*DEMON)(void);
	DEMON	m_fpDEMON[DS_END];

public:
	void Ready_Object(const float& _fVelocity,bool _bFilp);
public:
	virtual void Update(void);
	virtual void Render(HDC _hBackDC);
private:
	virtual void TriggerEnter(CGameObject* _ColObj);
private:
	void	State_Jump(void);
	void	State_Fall(void);
	void	State_Atk(void);
public:
	static CDemon* Create(const float& _fVelocity,bool _bFilp);
};
#endif // Demon_h__