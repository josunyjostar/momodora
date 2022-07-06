#ifndef AfterImage_h__
#define AfterImage_h__

class CAfterImage : public CGameObject
{
	friend CObjectMgr;
	DeclRTTI(CAfterImage, CGameObject);
private:
	explicit CAfterImage(void);
	virtual ~CAfterImage(void) {}
public:
	void Init(char* _pImageName, bool _bFlip, int _iFrame, float _fLifeTime, tRect _Rect);
	void Render(HDC _hBackDC);
private:
	float		m_fLifeTime;
	float		m_fDelayTime;
	char*		m_pImageName;
	tAni*		m_pAni;
	bool		m_bFlip;
	int			m_iFrame;
public:
	static void Create(char* _pImageName, bool _bFlip, int _iFrame, float _fLifeTime, tRect _Rect);
};

#endif // AfterImage_h__
