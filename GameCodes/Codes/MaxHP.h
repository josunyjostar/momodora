#ifndef MaxHP_h__
#define MaxHP_h__

class CMaxHP : public CGameObject
{
	DeclRTTI(CMaxHP, CGameObject);
public:
	explicit CMaxHP(void);
	virtual ~CMaxHP(void){}
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

#endif // MaxHP_h__