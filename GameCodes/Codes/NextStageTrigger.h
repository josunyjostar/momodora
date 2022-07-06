#ifndef NextStageTrigger_h__
#define NextStageTrigger_h__

#include "SceneMgr.h"

class CNextStageTrigger : public CGameObject
{
	DeclRTTI(CNextStageTrigger,CGameObject);
public:
	explicit CNextStageTrigger(void):m_pTrigger(NULL),m_eScene(CSceneMgr::SCENE_END){}
	virtual	~CNextStageTrigger(void){}
private:
	CTrigger*				m_pTrigger;
	CSceneMgr::SCENE_TYPE	m_eScene;
public:
	void		 SetTrigger(const tRect& _tRect,CSceneMgr::SCENE_TYPE _eScene);
public:
	virtual void Render(HDC _hBackDC);
	virtual void TriggerEnter(CGameObject* _ColObj);	
};

#endif // NextStageTrigger_h__
