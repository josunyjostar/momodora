#ifndef Dove_h__
#define Dove_h__

class CPlayer;
class CCrystal;

class CDove : public CGameObject
{
	DeclRTTI(CDove,CGameObject);
public:
	enum DOVE_MOVE {MOVE_PLAYER_AROUND,MOVE_TRACE,MOVE_SCREENOUT,MOVE_NONE};
public:
	explicit CDove(void);
	virtual ~CDove(void){}
private:
	CAnimator* 			m_pAnimator;
	CCollider*			m_pCollider;
	CTrigger*			m_pTrigger;
	CGameObject*		m_pPlayer;
	CGameObject*		m_pTarget;
	DOVE_MOVE			m_eMove;

	float				m_fSpeed;
	float				m_fRotSpeed;

	queue<CGameObject*> m_TargetQue;
public:
	void	Init(void);
	void	Update(void);
	void	Render(HDC _hBackDC);
public:
	void	SetPlayer(CGameObject* _pPlayer) {m_pPlayer = _pPlayer;}
	void	SetMoveMode(DOVE_MOVE _eMode)	  {m_eMove = _eMode;}
private:
	virtual void TriggerEnter(CGameObject* _ColObj)
	{
		if(TAG_ITEM == _ColObj->GetTag())
		{	
			m_TargetQue.push(_ColObj);
			m_pTarget = m_TargetQue.front();
			m_eMove = MOVE_TRACE;
			m_fSpeed = 500.f;
			m_fRotSpeed = D2R(260.f);
		}
	}
};

#endif // Dove_h__
