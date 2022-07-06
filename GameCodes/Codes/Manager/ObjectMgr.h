#pragma once

static const unsigned int MAX_OBJECT_TYPE	= 2048;
static const unsigned int MAX_OBJECT		= 4096;

class CObjectMgr : public TSingleton<CObjectMgr>
{
	friend TSingleton;
private:
	explicit CObjectMgr(void);
	virtual ~CObjectMgr(void);
private:
	CGameObject*	m_pObj[MAX_OBJECT_TYPE][MAX_OBJECT];
	const char*		m_szTypeName[MAX_OBJECT_TYPE];
	int				m_iSize[MAX_OBJECT_TYPE];
	int				m_iTypeSize;
public:
	void Init(void);
	void Update(void);
	void Release(void);
public:
	int GetObjCount(void)
	{
		int Count = 0;
		for(int i = 0; i < m_iTypeSize; ++i)
			Count += m_iSize[i];
		return Count;
	}

	template<typename T>
	void Init(void) 
	{
		int Type = GetTypeIndex(T::GetRTTIInst()->GetClassName());

		for(int i = 0; i < m_iSize[Type]; ++i)
			m_pObj[Type][i]->SetActive(false);
	}

	template<typename T>
	void Release(void) 
	{
		int Type = GetTypeIndex(T::GetRTTIInst()->GetClassName());

		for(int i = 0; i < m_iSize[Type]; ++i)
			SAFE_DELETE(m_pObj[Type][i]);

		m_iSize[Type] = 0;
	}

	template<typename T>
	T* Create(CObj* _pObj = NULL) 
	{
#ifdef _DEBUG
		const char* pName = T::GetRTTIInst()->GetClassName();
#endif // _DEBUG

		int Type = GetTypeIndex(T::GetRTTIInst()->GetClassName());

		for(int i = 0; i < m_iSize[Type]; ++i)
		{
			if(m_pObj[Type][i]->GetActive()) 
				continue;
			if(_pObj) 
				m_pObj[Type][i]->SetTag(_pObj->GetTag());

			m_pObj[Type][i]->Init();
			m_pObj[Type][i]->SetActive(true);

			return (T*)m_pObj[Type][i];
		}

		m_pObj[Type][m_iSize[Type]] = new T;

		if(_pObj) 
			m_pObj[Type][m_iSize[Type]]->SetTag(_pObj->GetTag());

		m_pObj[Type][m_iSize[Type]]->Init();
		m_pObj[Type][m_iSize[Type]]->SetActive(true);

		return (T*)m_pObj[Type][m_iSize[Type]++];
	}
private:
	int GetTypeIndex(const char* _pName);
};
