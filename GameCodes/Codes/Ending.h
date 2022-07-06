#ifndef Ending_h__
#define Ending_h__

#include "Scene.h"

class CEnding : public CScene
{
public:
	explicit CEnding(void):m_bReady(false){}
	virtual	~CEnding(void){}
public:
	bool	m_bReady;
public:
	virtual void	Init(void);
	virtual void	Update(void);
};

#endif // Ending_h__