#ifndef Collider_h__
#define Collider_h__

class CCollider : public CComponent
{
	DeclRTTI(CCollider, CComponent);
public:
	explicit CCollider(void):m_Rect(), m_ColType(COL_RECT), m_bTrigger(false) {}
	virtual ~CCollider(void) {}
protected:
	bool	m_bTrigger;
private:
	tRect	m_Rect;		//Rect : Pos, Size, Offset, Line : SP, EP, Offset
	int		m_ColType;
public:
	void SetColliderPos(const tPos& _Pos)		{m_Rect.SetPos(_Pos);}
	void SetColliderRect(const tRect& _colRect)	{m_Rect = _colRect;}
	void SetColliderRect(const tSize& _colSize)	{m_Rect.SetSize(_colSize);}
	void SetColType(int _ColType)				{m_ColType = _ColType;}

	bool  IsTrigger(void)  const	{return m_bTrigger;}
	int	  GetColType(void) const	{return m_ColType;}
	tRect GetRect(void)    const	{return m_Rect;}
	tRect GetColRect(void) const	{return m_Rect+m_pGameObject->GetPos();}
	tSize GetColSize(void) const	{return m_Rect.Size();}
public:
	virtual void Enable(void)	{CCollisionMgr::Inst().AddCollider(this);}
	virtual void Disable(void)	{CCollisionMgr::Inst().DeleteCollider(this);}
};
#endif // Collider_h__