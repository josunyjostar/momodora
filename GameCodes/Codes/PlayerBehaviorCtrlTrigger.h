#ifndef PlayerBehaviorCtrlTrigger_h__
#define PlayerBehaviorCtrlTrigger_h__

class CPlayerBehaviorCtrlTigger : public CGameObject
{
	DeclRTTI(CPlayerBehaviorCtrlTigger,CGameObject);
public:
	explicit CPlayerBehaviorCtrlTigger(void):m_pTrigger(NULL),m_eStare(STATE_IDLE){}
	virtual	~CPlayerBehaviorCtrlTigger(void){}
private:
	CTrigger*				m_pTrigger;
	PLAYER_STATE			m_eStare;
public:
	void		 SetTrigger(const tRect& _tRect,PLAYER_STATE _eState);
public:
	virtual void Render(HDC _hBackDC);
	virtual void TriggerEnter(CGameObject* _ColObj);	
};

#endif // PlayerBehaviorCtrlTrigger_h__
