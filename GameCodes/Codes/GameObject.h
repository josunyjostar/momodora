#ifndef GameObject_h__
#define GameObject_h__

const int MAX_OBJECT_COMPONENTS		= 64;

#define AddCallbackFunc(__TYPE,__FUNC_NAME)	FuncInst<__TYPE>()[#__FUNC_NAME]=&__TYPE::__FUNC_NAME;
#define Invoke(__FUNC_NAME,__TIME)			CCallBackMgr::Inst().AddFunc(this,__FUNC_NAME,__TIME,NULL)
#define Repeat(__FUNC_NAME,__TIME)			CCallBackMgr::Inst().AddFunc(this,__FUNC_NAME,__TIME,NULL,true)
#define InvokeEx(__FUNC_NAME,__TIME,__DATA)	CCallBackMgr::Inst().AddFunc(this,__FUNC_NAME,__TIME,__DATA)
#define RepeatEx(__FUNC_NAME,__TIME,__DATA)	CCallBackMgr::Inst().AddFunc(this,__FUNC_NAME,__TIME,__DATA,true)
#define StopInvoke(__FUNC_NAME)				CCallBackMgr::Inst().DeleteFunc(this,__FUNC_NAME)
#define StopRepeat(__FUNC_NAME)				CCallBackMgr::Inst().DeleteFunc(this,__FUNC_NAME)

class CComponent;
class CGameObject : public CObj
{
	friend  class CObjectMgr;
	DeclRTTI(CGameObject, CObj);
protected:
	explicit CGameObject(void);
	virtual ~CGameObject(void);
protected:
	tRect	m_Rect;
	float	m_fAngle;
private:
	CComponent* m_Components[MAX_OBJECT_COMPONENTS];
	const char*	m_TypeName[MAX_OBJECT_COMPONENTS];
	int			m_iSize;
public:
	template<typename T>
	map<char*, void(T::*)(void*)>& FuncInst(void) { static map<char*, void(T::*)(void*)> mFunc; return mFunc;}

	template<typename T>
	void FunctionCall(T* _pObj, char* _pFuncName, void* _pData) { (_pObj->*FuncInst<T>()[_pFuncName])(_pData); }

	virtual void CollisionEnter(COL_INFO& _ColInfo) {}
	virtual void Collision(COL_INFO& _ColInfo)		{}
	virtual void CollisionExit(COL_INFO& _ColInfo)	{}
	virtual void TriggerEnter(CGameObject* _ColObj) {}
	virtual void Trigger(CGameObject* _ColObj)		{}
	virtual void TriggerExit(CGameObject* _ColObj)	{}

	//XXX : Enable(), Disalbe() 재정의 시 반드시 ComponentsEnable(), ComponentsDisable() 메서드를 호출하는 소스가 포함되어야함.
	virtual void Enable()	{this->ComponentsEnable();}
	virtual void Disable()	{this->ComponentsDisable();}

	template <typename T> 
	T* AddComponent(void)
	{
		int i = GetTypeIndex(T::GetRTTIInst()->GetClassName());
		if(!m_Components[i]) m_Components[i] = CComponent::Create<T>(this);
		return (T*)m_Components[i];
	}

	template <typename T> 
	T* GetComponent(void)
	{return (T*)m_Components[GetTypeIndex(T::GetRTTIInst()->GetClassName())];}

	template <typename T>
	void DeleteComponent(void)
	{
		int i = GetTypeIndex(T::GetRTTIInst()->GetClassName());
		SAFE_DELETE(m_Components[i]);
		m_TypeName[i] = NULL;
	}

	void DeleteComponent(CComponent* _pComponent);

public:
	void AddPosX(float _x)					{m_Rect.x+=_x;}
	void AddPosY(float _y)					{m_Rect.y+=_y;}
	void AddPos(const tPos& _Pos)			{m_Rect.x+=_Pos.x;m_Rect.y+=_Pos.y;}
	void AddSizeX(float _cx)				{m_Rect.cx+=_cx;}
	void AddSizeY(float _cy)				{m_Rect.cy+=_cy;}
	void AddSize(const tSize& _Size)		{m_Rect.cx+=_Size.x;m_Rect.cy+=_Size.y;}

	void SetAngle(float _fAngle)			{m_fAngle = _fAngle;}
	void SetX(float _fX)					{m_Rect.x = _fX;}
	void SetY(float _fY)					{m_Rect.y = _fY;}
	void SetPos(const tPos& _Pos)			{m_Rect.SetPos(_Pos);}
	CGameObject* SetPos(float _x, float _y)	{m_Rect.SetPos(tPos(_x, _y));return this;}
	void SetSize(const tPos& _Size)	{m_Rect.SetSize(_Size);}
	void SetSize(float _cx, float _cy)		{m_Rect.SetSize(tSize(_cx,_cy));}
	void SetOffset(const tOffset& _Offset)	{m_Rect.SetOffset(_Offset);}
	void SetOffset(float _ox, float _oy)	{m_Rect.SetOffset(tOffset(_ox,_oy));}
	void SetRect(const tRect& _Rect)		{m_Rect = _Rect;}
	void SetRect(const tPos& _Pos, const tSize& _Size, const tOffset& _Offset = tOffset(0.5f, 0.5f)) 
	{m_Rect = tRect(_Pos,_Size,_Offset);}
	void SetRect(float _x, float _y, float _cx, float _cy, float _ox = 0.5f, float _oy = 0.5f)	
	{m_Rect = tRect(_x, _y, _cx, _cy, _ox, _oy);}

	float		GetX(void)		const	{return m_Rect.x;}
	float		GetY(void)		const	{return m_Rect.y;}
	tPos		GetPos(void)	const	{return m_Rect.Pos();}
	tSize		GetSize(void)	const	{return m_Rect.Size();}
	tRect		GetRect(void)	const	{return m_Rect;}
	float		GetAngle(void)	const	{return m_fAngle;}
	float		GetRadius(void) const	{return (m_Rect.cx<m_Rect.cy)?m_Rect.cx/2.f:m_Rect.cy/2.f;}
	RECT		GetRECT(void)	const;

protected:
	void ComponentsEnable(void);
	void ComponentsDisable(void);
private:
	int  GetTypeIndex(const char* _pName);
	void ClearComponents(void);
	void ComponentsUpdate(void);
public:
	template<typename T>
	static T* Create(void)	{return CObjectMgr::Inst().Create<T>();}
};

#endif // GameObject_h__