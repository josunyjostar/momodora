#ifndef Activator_h__
#define Activator_h__

#include "Player.h"

//TODO : Frame 드립 문제시 m_pTarget -> m_pTarget[MAX_CNT].

class CActivator : public CGameObject
{
	DeclRTTI(CActivator, CGameObject);
public:
	explicit CActivator(void);
	virtual ~CActivator(void){}
private:
	CCollider*		m_pCollider;
	CGameObject*	m_pTarget;
	tSize			m_ColSize;
public:
	void SetTarget(CGameObject* _pTarget,const tSize& _ColSize = tSize(2000.f,2000.f))
	{
		m_pTarget = _pTarget;
		this->SetPos(_pTarget->GetPos());
		m_pTarget->SetActive(false);
		m_ColSize = _ColSize;
		m_pCollider->SetColliderRect(tRect(tPos(0.f,0.f), m_ColSize));
	}
public:
	void Init(void);
	void Update(void);
	void Render(HDC _hBackDC);
private:
	virtual void CollisionEnter(COL_INFO& _ColInfo)
	{
		if (IsDynamicCast(CPlayer,_ColInfo.pObj))
		{
			if (m_pTarget)
			{	
				m_pTarget->SetActive(true);
				//this->SetActive(false);
			}
		}
	}

	virtual void CollisionExit(COL_INFO& _ColInfo)
	{
		if (IsDynamicCast(CPlayer,_ColInfo.pObj))
		{
			if (m_pTarget)
			{	
				m_pTarget->SetActive(false);
			//	this->SetActive(false);
			}
		}
	}
};

#endif // Activator_h__