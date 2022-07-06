#ifndef Waterfall_h__
#define Waterfall_h__

class CWaterfall : public CGameObject
{
	DeclRTTI(CWaterfall, CGameObject);
public:
	explicit CWaterfall(void);
	virtual ~CWaterfall(void){}
private:
	CAnimator* 	m_pAnimator;
public:
	virtual void Init(void);
};

#endif // Waterfall_h__
