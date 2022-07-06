#ifndef Door_h__
#define Door_h__

class CDoor : public CGameObject
{
	DeclRTTI(CDoor, CGameObject);
public:
	explicit CDoor(void);
	virtual ~CDoor(void){}
private:
	CCollider*		m_pCollider;
	CSprite*		m_pSprite;
	tPos			m_OriPos;
	bool			m_bUnlock;
	float			m_bAlphaVal;
public:
	void	SetOriPos(const tPos& _Pos) {m_OriPos = _Pos;m_Rect.SetPos(_Pos);}
	void	UnLock(void){m_bUnlock = true; m_pCollider->SetActive(false);CCamera::Inst().Shake(1.5f);}
public:
	virtual void Init(void);
	virtual void Update(void);
	virtual void Render(HDC _hBackDC);
};

#endif // Door_h__