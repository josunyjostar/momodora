#ifndef HitFilter_h__
#define HitFilter_h__

class CHitFilter : public CGameObject
{
	DeclRTTI(CHitFilter,CGameObject);
	enum FILTER_MODE {FM_RED,FM_WHITE,FM_HIT};
public:
	explicit CHitFilter(void);
	virtual ~CHitFilter(void) {}
public:
	CHitFilter*	SetMode(FILTER_MODE _eMode) { m_eMode = _eMode; return this;}
private:
	CImage* m_pWhiteImage;
	CImage* m_pRedImage;
	float	m_fAlpha;
	float	m_fAccTime;
	FILTER_MODE m_eMode;
public:
	void Init(void);
	void Render(HDC _hBackDC);
};

#endif // HitFilter_h__