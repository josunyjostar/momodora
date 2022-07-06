#ifndef PlayerUI_h__
#define PlayerUI_h__

class CPlayer;
class CPlayerUI : public CUI
{
	DeclRTTI(CPlayerUI,CUI);
public:
	explicit CPlayerUI(void);
	virtual ~CPlayerUI(void){}
private:
	CPlayer*	m_pPlayer;
	CRenderer*	m_pRenderer;

	tSprite* 	m_pHPBarRootFrame;
	tSprite* 	m_pHPBarBodyFrame;
	tSprite* 	m_pHPBarHeadFrame;

	tSprite* 	m_pSPBarRootFrame;
	tSprite* 	m_pSPBarBodyFrame;
	tSprite* 	m_pSPBarHeadFrame;

	tSprite* 	m_pHPBack;
	tSprite* 	m_pHPFront;
	tSprite* 	m_pSPBack;
	tSprite* 	m_pSPFront;
	tSprite* 	m_pItemSlot;

	float		m_fHPBack_Pos;
	float		m_fSPBack_Pos;
public:
	void	SetPlayer(CPlayer* _pPlayer) {m_pPlayer = _pPlayer;}
public:
	void	Init(void);
	void	Update(void);
	void	Render(HDC _bBackDC);
};

#endif // PlayerUI_h__
