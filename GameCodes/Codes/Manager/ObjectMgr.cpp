#include "stdafx.h"
#include "ObjectMgr.h"

CObjectMgr::CObjectMgr(void)
:m_iTypeSize(0)
{
	memset(*m_pObj, NULL, sizeof(*m_pObj)*MAX_OBJECT_TYPE);
	memset(m_szTypeName, NULL, sizeof(m_szTypeName));
	memset(m_iSize, 0, sizeof(m_iSize));
}

CObjectMgr::~CObjectMgr(void)
{
	this->Release();
}

void CObjectMgr::Init() 
{
	for(int i = 0; i < m_iTypeSize; ++i)
		for(int j = 0; j < m_iSize[i]; ++j)
			m_pObj[i][j]->SetActive(false);
}

void CObjectMgr::Update()
{
	for(int i = 0; i < m_iTypeSize; ++i)
		for(int j = 0; j < m_iSize[i]; ++j)
			if(m_pObj[i][j]->GetActive()) 
			{
				m_pObj[i][j]->ComponentsUpdate();
				m_pObj[i][j]->Update();
			}
}

void CObjectMgr::Release()
{
	for(int i = 0; i < m_iTypeSize; ++i) 
	{
		for(int j = 0; j < m_iSize[i]; ++j)
		{
#ifdef _DEBUG
		const char* pName =	m_pObj[i][j]->GetRTTI()->GetClassName();
#endif // _DEBUG
			SAFE_DELETE(m_pObj[i][j]);
		}

		m_iSize[i] = 0;
	}
	m_iTypeSize = 0;
}

int CObjectMgr::GetTypeIndex(const char* _pName) 
{
	for(int i = 0; i < m_iTypeSize; ++i)
		if(m_szTypeName[i] == _pName)
			return i;

	m_szTypeName[m_iTypeSize] = _pName;
	return m_iTypeSize++;
}