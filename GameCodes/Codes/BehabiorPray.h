#ifndef BehabiorPray_h__
#define BehabiorPray_h__

#include "Behavior.h"

class CBehaviorPray : public CBehavior
{
	DeclRTTI(CBehaviorPray,CBehavior);
	enum PRAY_MODE { TOPRAY,PRAYING,ENDPRAY, PM_END};
public:
	explicit CBehaviorPray(void);
	virtual ~CBehaviorPray(void){}
private:
	bool		m_bNext;
	float		m_fRunTime;
	PRAY_MODE	m_eState;
	PRAY_MODE	m_ePreState;

	typedef void (CBehaviorPray::*PRAY)(void);
	PRAY	m_fpPRAY[PM_END];
private:
	virtual void Update(void);
private:
	virtual void KeyState(void);
	virtual void Physics(void);
	virtual void Animation(void);
private:
	void ToPray(void);
	void Praying(void);
	void EndPray(void);
};

#endif // BehabiorPray_h__