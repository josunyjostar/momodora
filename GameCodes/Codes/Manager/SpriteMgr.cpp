#include "stdafx.h"
#include "SpriteMgr.h"

tSprite* CSpriteMgr::AddSprite(CImage* _Texture, char* _pName, int _X, int _Y, int _Width, int _Height, int _OX, int _OY, int _RenderingType)
{
	if(!_Texture) 
		return NULL;

	tSprite** dpSprite = &m_mapSprite[_pName];

	if(*dpSprite)
		return *dpSprite;

	*dpSprite = new tSprite(_Texture, _pName, _X, _Y, _Width, _Height, _OX, _OY, _RenderingType);
	return *dpSprite;
}

void CSpriteMgr::Release(void)
{
	map< char*,tSprite*>::iterator Iter = m_mapSprite.begin();
	map< char*,tSprite*>::iterator Iter_end = m_mapSprite.end();

	while(Iter_end != Iter)
	{
		SAFE_DELETE(Iter->second);
		++Iter;
	}
	m_mapSprite.clear();
}

