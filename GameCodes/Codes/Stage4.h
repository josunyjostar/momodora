#ifndef Stage4_h__
#define Stage4_h__

#include "Scene.h"

class CStage4 : public CScene
{
public:
	explicit CStage4(void):m_bReady(false){}
	virtual	~CStage4(void){}
public:
	bool	m_bReady;
public:
	virtual void	Init(void);
	virtual void	Update(void);
	virtual void	Ready_Object(void);
};

#endif // Stage4_h__
