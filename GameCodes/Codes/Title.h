#ifndef Title_h__
#define Title_h__

#include "Scene.h"

class CLoading;
class CDove;
class CTitle : public CScene
{
	enum BUTTON {BT_START,BT_QUIT};
public:
	explicit CTitle(void);
	virtual	~CTitle(void){}
private:
	CGameObject*	m_pStartBt;
	CGameObject*	m_pQuitBt;
	CGameObject*	m_pLoadingFont;
	CKeyState*		m_pKey;
	CDove*			m_pSelectIcon;

	int				m_iIdx;
	CLoading*		m_pLoading;
public:
	virtual void	Init(void);
	virtual void	Update(void);
};
#endif // Title_h__
