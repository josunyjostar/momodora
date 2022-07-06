#ifndef WaterSurface_h__
#define WaterSurface_h__

class CWaterSurface : public CGameObject
{
	DeclRTTI(CWaterSurface, CGameObject);
public:
	explicit CWaterSurface(void);
	virtual ~CWaterSurface(void){}
private:
	CAnimator*	m_pAnimator;
public:
	virtual void Init(void);
};

#endif // WaterSurface_h__
