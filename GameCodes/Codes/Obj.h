#ifndef Obj_h__
#define Obj_h__

class CObj abstract
{
	DeclRootRTTI(CObj);
protected:
	explicit CObj(void):m_bActive(false),m_Tag(0){}
	virtual	~CObj(void){}
protected:
	int		m_Tag;
private:
	bool	m_bActive;
public:
	const	int& GetTag(void) const	{return m_Tag;}
	void	SetTag(const int& _Tag) {m_Tag = _Tag;}
	void	SetTag(const CObj& _Obj){m_Tag = _Obj.m_Tag;}

	bool	GetActive(void) const	{return m_bActive;}
	//XXX: SetActive(true) 셋팅시 반드시 이전에 false필요 -Component에서 ture하는데 한번더 SetActive(true)시 this->Enable()2번 호출됨
	void	SetActive(const bool& _bActive) {m_bActive = _bActive;(_bActive)?this->Enable():this->Disable();}
public:
	virtual void Enable(void)  {}
	virtual void Disable(void) {}
	virtual void Init(void)				{}
	virtual	void Update(void)			{}
	virtual void Render(HDC _hBackDC)	{}
	virtual void Release(void)			{}		
public:
	bool	CompareTag(const CObj& _Obj) const {return m_Tag == _Obj.m_Tag;}
	bool	CompareTag(const int& _Tag)  const {return m_Tag == _Tag;}
};

#endif // Obj_h__