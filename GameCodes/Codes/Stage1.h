#ifndef Stage1_h__
#define Stage1_h__

#include "Scene.h"

class CStage1 : public CScene
{
public:
	explicit CStage1(void):m_bReady(false){}
	virtual	~CStage1(void){}
public:
	bool	m_bReady;
public:
	virtual void	Init(void);
	virtual void	Update(void);
	virtual void	Ready_Object(void);
};

#endif // Stage1_h__
