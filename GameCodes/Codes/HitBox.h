#ifndef HitBox_h__
#define HitBox_h__

#define HITBOX(__DAMAGE, __RECT,__TIME)\
CHitBox::Create(this,this->GetTag(), __DAMAGE, __RECT)->AddComponent<CTimer>()->SetTimer(__TIME)

class CHitBox : public CGameObject
{
	DeclRTTI(CHitBox,CGameObject);
public:
	explicit CHitBox(void);
	virtual ~CHitBox(void){}
private:
	CCollider*	m_pCollider;
	float		m_fDamage;
public:
	void		Ready_Object(int _iTag,float _fDamage,const tRect& _ColRect);
public:
	virtual void Init(void);
	virtual void Render(HDC _hBackDC);
	virtual void CollisionEnter(COL_INFO& _ColInfo);
public:
	static CHitBox* Create(CObj* _pObj,int _iTag,float _fDamage,const tRect& _ColRect);
};

#endif // HitBox_h__
