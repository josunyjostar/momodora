#ifndef WhiteFilter_h__
#define WhiteFilter_h__

class CWhiteFilter : public CGameObject
{
	DeclRTTI(CWhiteFilter,CGameObject);
public:
	explicit CWhiteFilter(void):m_pWhiteImage(NULL),m_fAlpha(255.f),m_fAccTime(0.f),m_fAlphaRate(1.f) {}
	virtual ~CWhiteFilter(void) {}
private:
	CImage* m_pWhiteImage;
	float	m_fAlpha;
	float	m_fAlphaRate;
	float	m_fAccTime;
public:
	virtual void Init(void);
	virtual void Render(HDC _hBackDC);
public:
	static CWhiteFilter* Create(void);
};

#endif // WhiteFilter_h__
