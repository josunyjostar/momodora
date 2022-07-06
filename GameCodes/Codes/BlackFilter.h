#ifndef BlackFilter_h__
#define BlackFilter_h__

class CBlackFilter : public CGameObject
{
	DeclRTTI(CBlackFilter,CGameObject);
public:
	enum FILTER_MODE {FM_IN,FM_OUT,FM_NONE,FM_INOUT};
public:
	explicit CBlackFilter(void):m_pBlackImage(NULL),m_fAlpha(255.f),m_eMode(FM_NONE),m_fAccTime(0.f) {}
	virtual ~CBlackFilter(void) {}
private:
	CImage* m_pBlackImage;
	float	m_fAlpha;
	float	m_fAccTime;
	FILTER_MODE m_eMode;

	typedef	void (CBlackFilter::*ModeFunc)(void);
	static	ModeFunc m_fpModeFunc[];
public:
	void SetFilterMode(FILTER_MODE _eMode) {m_eMode = _eMode;}
public:
	void Init(void);
	void Render(HDC _hBackDC);
private:
	inline void ModeIn(void)	{static float f = 0.f;m_fAccTime += fDeltaTime*2.f;f = 1 / pow(M_E,1/m_fAccTime);m_fAlpha = 255.f *f;if(m_fAlpha >= 255.f)m_fAlpha=255.f;}
	inline void ModeOut(void)	{static float f = 0.f;m_fAccTime += fDeltaTime*0.5f+0.03f;f = sin(1/(m_fAccTime+0.5f));m_fAlpha = 255.f * f;if(m_fAlpha < 10.f)this->SetActive(false);}
	inline void ModeNone(void)	{m_fAlpha = 255.f;}
	inline void ModeInOut(void)	
	{
		m_fAccTime += fDeltaTime*2.5f;

		static float f = 0.f;
		f = sin(m_fAccTime);

		m_fAlpha = 255.f *f;

		if(m_fAlpha < 5.7f)
		{
			m_fAlpha  = 5.7f;
			m_fAccTime = 0.f;
			this->SetActive(false);
		}
	}
};

#endif // BlackFilter_h__
