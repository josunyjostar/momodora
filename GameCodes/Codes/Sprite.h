#ifndef Sprite_h__
#define Sprite_h__

class CSprite : public CRenderer 
{
	DeclRTTI(CSprite,CRenderer)
public:
	explicit CSprite(void):m_pSprite(NULL),m_bResize(true),m_bAlpha(false),m_AlphaVal(255) {}
	virtual ~CSprite(void) {}
private:
	tSprite*	m_pSprite;
	bool		m_bResize;
	bool		m_bAlpha;
	BYTE		m_AlphaVal;
	char*		m_szSpriteName;
public:
	void SetSprite(char* _pSpriteName) {m_pSprite  = CSpriteMgr::Inst().GetSprite(_pSpriteName); m_szSpriteName = _pSpriteName;}
	void SetResize(bool _bResize)	   {m_bResize  = _bResize;}
	void SetAlpha(bool _bAlpha)		   {m_bAlpha   = _bAlpha;}
	void SetAlphaVal(BYTE _AlphaVal)   {m_AlphaVal = _AlphaVal;}

	bool GetAlpha(void)		const {return m_bAlpha;}
	BYTE GetAlphaVal(void)	const {return m_AlphaVal;}
	const char* GetSpriteName(void) const {return m_szSpriteName;}
public:
	virtual void Render(HDC _hBackDC) 
	{
		if(!m_pSprite) 
			return;

#ifdef _DEBUG
		const char* pName = m_pGameObject->GetRTTI()->GetClassName();
#endif // _DEBUG

		if(m_bResize)//HACK: 
		{
			tRect rc = m_pGameObject->GetRect();

			if(m_bAlpha) 
			{
				m_pSprite->Draw(_hBackDC,
					rc.L() - DRAWX,
					rc.T() - DRAWY,
					(int)rc.cx,
					(int)rc.cy, m_AlphaVal);
			}
			else 
			{
				m_pSprite->Draw(_hBackDC,
					rc.L() - DRAWX,
					rc.T() - DRAWY,
					(int)rc.cx,
					(int)rc.cy);
			}
		}
		else 
		{
			if(m_bAlpha) 
			{
				m_pSprite->Draw(_hBackDC,
					(int)(m_pGameObject->GetPos().x - (float)DRAWX),
					(int)(m_pGameObject->GetPos().y - (float)DRAWY), m_AlphaVal);
			}
			else 
			{
				m_pSprite->Draw(_hBackDC,
					(int)(m_pGameObject->GetPos().x - (float)DRAWX),
					(int)(m_pGameObject->GetPos().y - (float)DRAWY));
			}
		}
	}
};

#endif // Sprite_h__
