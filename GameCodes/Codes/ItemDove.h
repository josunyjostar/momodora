#ifndef ItemDove_h__
#define ItemDove_h__

class CItemDove : public CGameObject
{
	DeclRTTI(CItemDove, CGameObject);
public:
	explicit CItemDove(void);
	virtual ~CItemDove(void){}
private:
	CAnimator*		m_pAnimator;
	CCollider*		m_pCollider;
	tSprite*		m_pSprite;
public:
	virtual void Init(void);
	virtual void Render(HDC _hBackDC);
private:
	virtual void CollisionEnter(COL_INFO& _ColInfo);
};

#endif // ItemDove_h__