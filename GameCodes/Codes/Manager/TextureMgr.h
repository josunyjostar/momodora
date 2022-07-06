#ifndef TextureMgr_h__
#define TextureMgr_h__

class CTextureMgr : public TSingleton<CTextureMgr>
{
	friend TSingleton;
private:
	explicit CTextureMgr(void) :m_pAniMgr(&CAnimationMgr::Inst()),m_pSpriteMgr(&CSpriteMgr::Inst()) {}
	virtual ~CTextureMgr(void) {this->Release();}
private:
	map<char*, CImage*>				m_mapTexture;
	CAnimationMgr*	const			m_pAniMgr;
	CSpriteMgr*		const			m_pSpriteMgr;
public:
	CImage* AddTexture(char* _pName, WCHAR* _pFilePath);
	CImage* GetTexture(char* _pName) {return m_mapTexture[_pName];}
public:
	void Init(void);
	void Release(void);
};

#endif // TextureMgr_h__
