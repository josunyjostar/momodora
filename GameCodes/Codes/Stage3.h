#ifndef Stage3_h__
#define Stage3_h__

#include "Scene.h"

class CStage3 : public CScene
{
public:
	explicit CStage3(void):m_bReady(false){}
	virtual	~CStage3(void){}
public:
	bool	m_bReady;
public:
	virtual void	Init(void);
	virtual void	Update(void);
	virtual void	Ready_Object(void);
};

#endif // Stage3_h__
