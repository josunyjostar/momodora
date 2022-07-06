#include "stdafx.h"
#include "GameObject.h"
#include "Component.h"

CGameObject::CGameObject(void)
:m_iSize(0)
,m_fAngle(0.f)
,m_Rect()
{
	memset(m_Components, NULL, sizeof(m_Components));
	memset(m_TypeName, NULL, sizeof(m_TypeName));
}

CGameObject::~CGameObject(void)
{
	this->ClearComponents();
}

int CGameObject::GetTypeIndex(const char* _pName)
{
	for(int i = 0; i < m_iSize; ++i) 
	{
		if(!m_TypeName[i]) 
		{
			m_TypeName[i] = _pName;
			return i;
		}
		else if(m_TypeName[i] == _pName) 
			return i;
	}

	m_TypeName[m_iSize] = _pName;
	return m_iSize++;
}

void CGameObject::ComponentsEnable()
{
	for(int i = 0; i < m_iSize; ++i)
		if(m_Components[i] && !m_Components[i]->GetActive()) m_Components[i]->SetActive(true);
}

void CGameObject::ComponentsDisable()
{
	for(int i = 0; i < m_iSize; ++i)
		if(m_Components[i] && m_Components[i]->GetActive()) m_Components[i]->SetActive(false);
}

void CGameObject::ComponentsUpdate()
{
	for(int i = 0; i < m_iSize; ++i)
		if(m_Components[i] && m_Components[i]->GetActive()) m_Components[i]->Update();
}

void CGameObject::DeleteComponent(CComponent* _pComponent)
{
	for(int i = 0; i < m_iSize; ++i){
		if(m_Components[i] == _pComponent){
			SAFE_DELETE(m_Components[i]);
			m_TypeName[i] = NULL;
		}
	}
}

void CGameObject::ClearComponents()
{
	for(int i = 0; i < m_iSize; ++i)
		SAFE_DELETE(m_Components[i]);
	m_iSize = 0;
}

RECT CGameObject::GetRECT() const
{
	RECT rc = {
		LONG(m_Rect.L()), 
		LONG(m_Rect.T()),
		LONG(m_Rect.R()), 
		LONG(m_Rect.B())};
		return rc;
}