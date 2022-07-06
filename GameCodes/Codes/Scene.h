#ifndef Scene_h__
#define Scene_h__

#include "Player.h"

#define CREATE_TILE(__RESIZE,__X,__Y,__CX,__CY)\
	CGameObject::Create<CTileCollider>()->Init(tRect(__RESIZE*__X,__RESIZE*__Y,__RESIZE*__CX,__RESIZE*__CY,0.f,0.f))

class CScene abstract
{
public:
	explicit CScene(void):m_bRun(false)
		,m_Camera(CCamera::Inst())
		,m_KeyState(CKeyState::Inst())
		,m_RenderMgr(CRenderMgr::Inst())
		,m_ObjectMgr(CObjectMgr::Inst())
		,m_CollMgr(CCollisionMgr::Inst())
		,m_FontMgr(CFontMgr::Inst())
		,m_CallBackMgr(CCallBackMgr::Inst()){}
	virtual	~CScene(void){}
protected:
	bool	m_bRun;
private:
	CKeyState&		 m_KeyState;
	CCamera&		 m_Camera;
	CObjectMgr&		 m_ObjectMgr;
	CCollisionMgr&	 m_CollMgr;
	CRenderMgr&		 m_RenderMgr;
	CFontMgr&		 m_FontMgr;
	CCallBackMgr&	 m_CallBackMgr;
public:
	void	SetRun(bool _bRun){m_bRun = _bRun;}
public:
	virtual void	Init(void)	PURE;
	virtual void	Update(void)
	{
		if(m_bRun)
		{
			m_KeyState.Update();
			m_CallBackMgr.Update();

			m_ObjectMgr.Update();
			m_FontMgr.Update();

			m_CollMgr.Update();
			m_Camera.Update();

			m_RenderMgr.Render();
		}
	}
	virtual void	Ready_Object(void){};
};

#endif // Scene_h__
