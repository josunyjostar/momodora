#ifndef SpriteMgr_h__
#define SpriteMgr_h__

class CSpriteMgr : public TSingleton<CSpriteMgr>
{
	friend TSingleton;
private:
	explicit CSpriteMgr(void) {}
	virtual ~CSpriteMgr(void) {this->Release();}
private:
	map<char*,tSprite*>	m_mapSprite;
public:
	tSprite* AddSprite(CImage* _Texture, char* _pName, int _X, int _Y, int _Width, int _Height, int _OX, int _OY, int _RenderingType);
	tSprite* GetSprite( char* _pName) { return m_mapSprite[_pName];}
public:
	void	Release(void);
};

#endif // SpriteMgr_h__
