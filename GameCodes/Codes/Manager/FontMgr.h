#ifndef FontMgr_h__
#define FontMgr_h__

class CFontMgr : public TSingleton<CFontMgr>
{
	friend TSingleton;
private:
	explicit CFontMgr(void);
	virtual ~CFontMgr(void){}
private:
	CFont*		m_pNameUI;
	CFont*		m_pTimeUI;
	CFont*		m_pCoinUI;
	CFont*		m_pStarUI;
	CFont*		m_pTimeTxtUI;

	int			m_iCoin;
	int			m_iTime;
	char*		m_szName;
	float		m_fDelay;
	bool		m_bStop;
public:
	void Hide(void);
public:
	void SetName(char* _pName);
	void SetCoin(int _iCoin);
	void SetTime(int _iTime);
	void SetPause(bool _bPause) {m_bStop = _bPause;}

	int		GetTime(void)  const {return m_iTime;}
	int		GetCoin(void)  const {return m_iCoin;}
	char*	GetName(void)  const {return m_szName;}

	void AddTime(int _iTime);
	void AddCoin(int _iCoin);
public:
	void Init(void);
	void Update(void);

	CGameObject*	CreateText(char* _pString, int _iFontSize, const tPos& _tPos, bool _bUI = false);
	CGameObject*	CreateText(int _iNumber, int _iFontSize, const tPos& _tPos, bool _bUI = false);
	CGameObject*	CreateAlPhaText(char* _pString, int _iFontSize, const tPos& _tPos,CFont::FONT_ALPHA_TYPE _eType,
		float _fInitAlpha,bool _bUI = false);
};

#endif // FontMgr_h__
