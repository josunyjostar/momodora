#ifndef Knife_h__
#define Knife_h__

class CKnife : public CGameObject
{
	DeclRTTI(CKnife,CGameObject);
public:
	explicit CKnife(void);
	virtual ~CKnife(void){}
private:
	CAnimator*		 m_pAnimator;
	CCollider*		 m_pCollider;
	float			 m_fSpeed;
	bool			 m_bFilp;
	float			 m_fDamage;
public:
	CKnife* SetKnife(bool _bFilp,float _fDamage){m_bFilp = _bFilp;m_fDamage=_fDamage; return this;}
private:
	virtual void Init(void);
	virtual void Update(void);
	virtual void Render(HDC _hBackDC);

	virtual	void CollisionEnter(COL_INFO& _ColInfo);
};


#endif // Knife_h__

