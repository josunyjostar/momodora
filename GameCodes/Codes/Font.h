#ifndef Font_h__
#define Font_h__

class CFont : public CRenderer
{
	DeclRTTI(CFont,CRenderer);
public:
	enum FONT_ALPHA_TYPE {FONT_ALPHA_IN,FONT_ALPHA_OUT,FONT_ALPHA_INOUT,FONT_ALPHA_NONE};
public:
	explicit CFont(void):m_pFont(NULL),m_pIndex(NULL),m_iSize(0),m_iFontSize(0),m_bUIFont(true),
		m_eAlphaType(FONT_ALPHA_IN),m_fFontAlpha(100.f),m_fRate(1.f),m_fAccTime(0.f) {}
	virtual ~CFont(void) {this->Release();}
private:
	tAni*	m_pFont;
	int*	m_pIndex;
	int		m_iSize;
	int		m_iFontSize;
	bool	m_bUIFont;
	float	m_fFontAlpha;
	float	m_fRate; // [0.1]~[1.f]
	float	m_fAccTime;
	FONT_ALPHA_TYPE m_eAlphaType;
public:
	void Hide(void);
public:
	float GetFontAlpha(void) const {return m_fFontAlpha;}
	//XXX: _fRate [0.1]~[1.f]
	void SetAlphaRate(const float& _fRate)		{m_fRate = _fRate;}
	void SetFontAlpha(const float& _fAlpha)		{m_fFontAlpha = _fAlpha;}
	void SetAlphaType(FONT_ALPHA_TYPE _eType)	{m_eAlphaType = _eType;}
	void SetFontSize(int _iFontSize)			{m_iFontSize = _iFontSize;}
	void SetUI(bool _bUIFont)					{m_bUIFont = _bUIFont;}
public:
	void Init(void);
	void Release(void);
	void Render(HDC _hbackDC);
	void Numeric(int _iNumber);
	void Numeric(int _iNumber ,int _iSize);
	void String(char* _pString);
	void String(char* _pString, int _iStrlen);
private:
	void ReSize(int _iSize);
};

#endif // Font_h__