#ifndef Crystal_h__
#define Crystal_h__

class CCrystal : public CGameObject
{
	DeclRTTI(CCrystal, CGameObject);
public:
	explicit CCrystal(void);
	virtual ~CCrystal(void){}
private:
	float			m_fDir;
	CAnimator*		m_pAnimator;
	CCollider*		m_pCollider;
public:
	void Init(void);
	void Update(void);
	void Render(HDC _hBackDC);
private:
	virtual void CollisionEnter(COL_INFO& _ColInfo);
	
};

#endif // Crystal_h__
