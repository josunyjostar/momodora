#ifndef WaterSurface2_h__
#define WaterSurface2_h__

class CWaterSurface2 : public CGameObject
{
	DeclRTTI(CWaterSurface2, CGameObject);
public:
	explicit CWaterSurface2(void);
	virtual ~CWaterSurface2(void){}
private:
	CAnimator*	m_pAnimator;
public:
	virtual void Init(void);
};

#endif // WaterSurface2_h__
