#ifndef Platform_h__
#define Platform_h__

class CPlatform : public CGameObject
{
	DeclRTTI(CPlatform,CGameObject);
	enum PF_DIR{DIR_LR,DIR_UD,DIR_NONE};
public:
	explicit CPlatform(void);
	virtual ~CPlatform(void){}
private:
	CCollider*  	m_pCollider;
	CRenderer*  	m_pRenderer;
	tSprite*		m_pSprite;
	tSize			m_PlatformSize;

	PF_DIR			m_eMoveDir;
	float			m_fDir;
	float			m_fSpeed;
	tPos			m_fRangeS;
	tPos			m_fRangeE;
public:
	CGameObject* Ready_Object(TILE_TYPE _eType,const tPos& _Pos,int _iMapReSize,float _fTileSize,PF_DIR _eDir = DIR_NONE
		,float _fSpeed = 1.f,float _fRangeEnd = 10.f);
public:
	virtual void Init(void);
	virtual void Update(void);
	virtual void Render(HDC _hBackDC);
};

#endif // Platform_h__
