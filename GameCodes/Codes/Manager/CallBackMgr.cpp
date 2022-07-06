#include "stdafx.h"
#include "CallBackMgr.h"

CCallBackMgr::CCallBackMgr(void)
:m_iSize(0)
{
	memset(m_Timer,NULL,sizeof(m_Timer));
}

void CCallBackMgr::Update(void)
{
	for(int i=0; i < m_iSize ; ++i)
	{
		if (!m_Timer[i])
			continue;

		m_Timer[i]->fDelayTime -= fDeltaTime;

		if (m_Timer[i]->fDelayTime <= 0.f)
		{
			m_Timer[i]->Call();

			if (m_Timer[i]->bRepeat)
				m_Timer[i]->fDelayTime = m_Timer[i]->fMaxTime;
			else
				SAFE_DELETE(m_Timer[i]);
		}
	}

}

void CCallBackMgr::Release(void)
{
	for(int i =0; i < m_iSize ; ++i)
		SAFE_DELETE(m_Timer[i]);

	m_iSize = 0;
}

void CCallBackMgr::DeleteFunc(CGameObject* _pObj, char* _pFuncName)
{
	for (int i=0; i < m_iSize ; ++i)
	{
		if (!m_Timer[i])
			continue;

		if (m_Timer[i]->pFuncName == _pFuncName && ((BindingTimer<CGameObject>*)m_Timer[i])->pObj == _pObj)
		{
			SAFE_DELETE(m_Timer[i]);
			return;
		}
	}
}
