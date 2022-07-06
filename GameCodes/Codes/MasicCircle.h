#ifndef MasicCircle_h__
#define MasicCircle_h__

class CMasicCircle : public CGameObject
{
	friend CObjectMgr;
	DeclRTTI(CMasicCircle, CGameObject);
private:
	explicit CMasicCircle(void);
	virtual ~CMasicCircle(void) {}
public:
	void Ready_Object(const tRect& _Rect,const float& _fLifeTime);
public:
	virtual void Render(HDC _hBackDC);
private:
	float		m_fLifeTime;
	float		m_fDelayTime;
	CAnimator*  m_pAnimator;
public:
	static void Create(const tRect& _Rect,const float& _fLifeTime = 0.f);
};

#endif // MasicCircle_h__
