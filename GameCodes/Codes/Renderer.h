#ifndef Renderer_h__
#define Renderer_h__

class CRenderer : public CComponent
{
	DeclRTTI(CRenderer,CComponent)
public:
	explicit CRenderer(void):m_iLayer(LAYER_OBJECT),m_iZOrder(0){}
	virtual ~CRenderer(void){}
protected:
	int		m_iZOrder;
	int		m_iLayer;
public:
	void	SetLayer(int _iLayer)   { m_iLayer = _iLayer;}
	void	SetZOrder(int _iZOrder) { m_iZOrder = _iZOrder;}
	const	int& GetLayer(void)  const   {return m_iLayer;}
	const	int& GetZOrder(void) const   {return m_iZOrder;}
public:
	virtual void Enable(void)  {CRenderMgr::Inst().AddRenderer(this);}
	virtual void Disable(void) {CRenderMgr::Inst().DeleteRenderer(this);}
	virtual void Render(HDC _hBackDC) {m_pGameObject->Render(_hBackDC);}
};

#endif // Renderer_h__