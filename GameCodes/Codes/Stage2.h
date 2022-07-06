#ifndef Stage2_h__
#define Stage2_h__

#include "Scene.h"

class CStage2 : public CScene
{
public:
	explicit CStage2(void):m_bReady(false){}
	virtual	~CStage2(void){}
public:
	bool	m_bReady;
public:
	virtual void	Init(void);
	virtual void	Update(void);
	virtual void	Ready_Object(void);
};

#endif // Stage2_h__
