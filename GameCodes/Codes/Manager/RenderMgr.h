#ifndef RenderMgr_h__
#define RenderMgr_h__

static const unsigned int MAX_RENDERER = 4096;
static const unsigned int MAX_BGA = 4;

typedef struct tagBGADrawPos {int x;int y;}BGA_POS;

class CRenderer;
class CRenderMgr : public TSingleton<CRenderMgr>
{
	friend	TSingleton;
private:
	explicit CRenderMgr(void);
	virtual ~CRenderMgr(void);
private:
	HDC			m_hdc;
	HDC			m_hBackDC;
	HBITMAP		m_hDBBitmap;

	CRenderer*	m_pRenderer[MAX_RENDERER];
	CRenderer*	m_pSortRenderer[MAX_RENDERER];
	int			m_iSize;
	int			m_iSortSize;

	CGameObject*	m_pBGAs[MAX_BGA];
	BGA_POS			m_BGAPos[MAX_BGA];

public:
	void Init(void);
	void Release(void);
	void Render(void);
	void Paint(void);
	void Sort(const int& _Layer);

	CGameObject* AddBGA(char* _pName,const int& _ZOrder);
	CGameObject* AddBGA(char* _pName, int _BGACX, int _BGACY, int _DrawX, int _DrawY, int _ZOrder = 0);
	void SetBGASize(int _BGACX,int _BGACY);
	void ClearBGA(void);

public: //CRenderer
	void AddRenderer(CRenderer* _pRenderer);
	void DeleteRenderer(CRenderer* _pRenderer);
};
#endif // RenderMgr_h__
