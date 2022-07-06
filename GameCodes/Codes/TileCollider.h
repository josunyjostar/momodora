#ifndef TileCollider_h__
#define TileCollider_h__

class CTileCollider : public CGameObject
{
	DeclRTTI(CTileCollider,CGameObject);
public:
	explicit CTileCollider(void):m_pCollider(NULL)	{}
	virtual ~CTileCollider(void)  {}
private:
	CCollider*  m_pCollider;
public:
	void Init(tRect _tCollRect, COL_TYPE _ColType = COL_RECT);
	void Render(HDC _hbackDC);
};

#endif // TileCollider_h_