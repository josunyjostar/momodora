#ifndef AnimationMgr_h__
#define AnimationMgr_h__

class CAnimationMgr : public TSingleton<CAnimationMgr>
{
	friend TSingleton;
private:
	explicit CAnimationMgr(void){}
	virtual ~CAnimationMgr(void){this->Release();}
private:
	map<char* ,tAni*>	m_mapAnimation;
public:
	tAni*	GetAni(char*  _pName)	{return m_mapAnimation[_pName];}
	void	AddAni(CImage* _LTexture, CImage* _RTexture, char* _pName, int _MaxFrame, 
		int _StartX, int _StartY, int _Width, int _Height, int _OX, int _OY, int _NullWidth, int _NullHeight, 
		int _RenderingType, bool _bRepeat, char* _pNextAni = NULL, float* _FrameDelay = NULL);
public:
	void	Release(void);
};

#endif // AnimationMgr_h__
