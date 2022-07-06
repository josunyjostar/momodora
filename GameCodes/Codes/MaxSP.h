#ifndef MaxSP_h__
#define MaxSP_h__

class CMaxSP : public CGameObject
{
	DeclRTTI(CMaxSP, CGameObject);
public:
	explicit CMaxSP(void);
	virtual ~CMaxSP(void){}
private:
	CCollider*		m_pCollider;
	CSprite*		m_pSprite;
public:
	virtual void Init(void);
	virtual void Update(void);
	virtual void Render(HDC _hBackDC);
private:
	virtual void CollisionEnter(COL_INFO& _ColInfo);
};
#endif // MaxSP_h__