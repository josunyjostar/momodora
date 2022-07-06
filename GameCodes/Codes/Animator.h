#ifndef Animator_h__
#define Animator_h__

class CAnimator : public CRenderer
{
	DeclRTTI(CAnimator,CRenderer)
public:
	explicit CAnimator(void);
	virtual ~CAnimator(void) {}
private:
	tAni*	m_pPlayAni;
	char*	m_pPlayAniName;
	int		m_iFrame;
	float	m_fPlayTime;
	float	m_fPlaySpeed;
	bool	m_bPlaying;
	bool	m_bFlip;

	bool	m_bResize;
	bool	m_bAlpha;
	BYTE	m_AlphaVal;
public:
	void	SetPlaySpeed(float _fPlaySpeed) {m_fPlaySpeed = _fPlaySpeed;}
	void	SetReSize(bool _bReSize)		{m_bResize = _bReSize;}
	void	SetAlpha(bool _bAlpha)			{m_bAlpha = _bAlpha;}
	void	SetAlphaVal(BYTE _AlphaVal)		{m_AlphaVal = _AlphaVal;}
	int		GetFrame(void)		 const		{return m_iFrame;}	
	float	GetAniPlayTime(char* _pAniName);
	char*	GetPlayAniName(void) const		{return m_pPlayAniName;}
	
	bool	IsPlay(void)	 const  {return m_bPlaying;}//HACK: m_bPlaying의 조건을 다시 만들어야함 작성자: 박제영
	bool	IsFlip(void)	 const	{return m_bFlip;}
public:
	virtual void Init(void);
	virtual void Render(HDC _hBackDC);
public:
	void Play(char* _pAniName = NULL, bool _bInit = true);
	void Stop(bool _bClear = false);
	void SetFlipX(bool _bFlip)	{m_bFlip = _bFlip;}
};

#endif // Animator_h__
