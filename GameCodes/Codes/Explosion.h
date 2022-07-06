#ifndef Explosion_h__
#define Explosion_h__

class CExplosion : public CGameObject
{
	friend CObjectMgr;
	DeclRTTI(CExplosion, CGameObject);
private:
	explicit CExplosion(void);
	virtual ~CExplosion(void) {}
public:
	void Ready_Object(const tPos& _Pos);
public:
	virtual void Update(void);
	virtual void Render(HDC _hBackDC);
private:
	bool		m_bFilter;
	float		m_fDelayTime;
	float		m_fLifeTime;
	int			m_iFrame;

	CAnimator*  m_pAnimator;
public:
	static void Create(const tPos& _Pos);
};

#endif // Explosion_h__