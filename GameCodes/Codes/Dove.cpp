#include "stdafx.h"
#include "Dove.h"

#include "Player.h"
#include "Crystal.h"

CDove::CDove(void)
:m_pAnimator(NULL)
,m_pCollider(NULL)
,m_pTrigger(NULL)
,m_pPlayer(NULL)
,m_pTarget(NULL)
,m_eMove(MOVE_NONE)
,m_fSpeed(300.f)
,m_fRotSpeed(1.f)
{

}

void CDove::Init(void)
{
	m_Tag = TAG_PET;

	m_Rect = tRect(500.f, 500.f , 50.f ,60.f ,0.5f,0.5f);
	this->AddComponent<CRenderer>();

	m_pAnimator = this->AddComponent<CAnimator>();
	m_pAnimator->Play("Dove_Fly");//Dove_Fly//"Dove_Stright
	m_pAnimator->SetZOrder(4);
	m_pAnimator->SetLayer(LAYER_OBJECT);
	m_pAnimator->SetReSize(true);
	m_pAnimator->SetPlaySpeed(1.f);

	m_pCollider = this->AddComponent<CCollider>();
	m_pTrigger  = this->AddComponent<CTrigger>();
	m_pCollider->SetColliderRect(tRect(tPos(),m_Rect.Size(),m_Rect.Offset()));
	m_pTrigger->SetColliderRect(tRect(0.f, 0.f, 800.f, 800.f));

	m_fRotSpeed = D2R(360.f);
}

void CDove::Update(void)
{
	switch(m_eMove)
	{
	case MOVE_TRACE:
		{
			if(!m_pTarget->GetActive())
			{	
				if(m_TargetQue.empty())
					m_eMove = MOVE_PLAYER_AROUND;
				else
				{
					if(!m_TargetQue.empty())
						m_TargetQue.pop();
					if(!m_TargetQue.empty())
						m_pTarget = m_TargetQue.front();
				}
			}

			tVector vLook = LookAt2(m_Rect.Pos(),m_pTarget->GetPos());
			tVector	vDir  = R2UV(m_fAngle);

			float fRotDir = Cross(vDir,vLook);
			float fDegree = acosf(Dot(vDir,vLook));

			if (fRotDir < 0.f)
				fDegree = -fDegree;

			m_Rect	 += vDir * (m_fSpeed * fDeltaTime);
			m_fAngle += fDegree * m_fRotSpeed * fDeltaTime;

			static float fDistance = 0.f;
			static float y  = 0.f;

			float f = V2D(vLook);

			if (abs(f) > 90.f)
				m_pAnimator->SetFlipX(true);
			else
				m_pAnimator->SetFlipX(false);
		}
		break;
	case MOVE_PLAYER_AROUND:
		{
			bool bFilp = m_pPlayer->GetComponent<CAnimator>()->IsFlip();
			tVector vLook = LookAt2(m_Rect.Pos(),m_pPlayer->GetPos()+tPos(bFilp?20.f:-20.f,-130.f));
			tVector	vDir  = R2UV(m_fAngle);

			float fRotDir = Cross(vDir,vLook);
			float fDegree = acosf(Dot(vDir,vLook));

			if (fRotDir < 0.f)
				fDegree = -fDegree;

			m_Rect	 += vDir * (m_fSpeed * fDeltaTime);
			m_fAngle += fDegree * m_fRotSpeed * fDeltaTime;

			static float fDistance = 0.f;
			static float y  = 0.f;

			fDistance =  sqrDistance(m_Rect.Pos(),m_pPlayer->GetPos());
			y		 += fDeltaTime;

			if (fDistance < 28000.f)
			{
				m_fSpeed = 100.f;
				m_fRotSpeed = D2R(190.f);
				m_Rect.y += sinf(y)*0.3f;
				m_Rect.x += cosf(y)*0.2f;

				m_pAnimator->SetFlipX(bFilp);
				break;
			}
			else
			{	
				m_fSpeed += fDeltaTime*200.f;
				if (m_fSpeed > 500.f)
					m_fSpeed = 500.f;
				m_fRotSpeed = D2R(200.f);
			}

			float f = V2D(vLook);

			if (abs(f) > 90.f)
				m_pAnimator->SetFlipX(true);
			else
				m_pAnimator->SetFlipX(false);
		}
		break;
	case MOVE_SCREENOUT:
		break;
	case MOVE_NONE:
		break;
	}
}

void CDove::Render(HDC _hBackDC)
{
#ifdef _DEBUG
	if (DEBUG_MODE)
	{
		static HPEN hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255,0,255));
		static HPEN hOldPen;
		static HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		static HBRUSH hOldBrush;

		hOldBrush = (HBRUSH)SelectObject(_hBackDC, hBrush);
		hOldPen = (HPEN)SelectObject(_hBackDC, hPen);

		tRect rc = m_pCollider->GetColRect();
		Rectangle(_hBackDC, 
			int(rc.L()) - DRAWX,
			int(rc.T()) - DRAWY,
			int(rc.R()) - DRAWX,
			int(rc.B()) - DRAWY);

		rc = m_pTrigger->GetColRect();
		Ellipse(_hBackDC, 
			int(rc.L()) - DRAWX,
			int(rc.T()) - DRAWY,
			int(rc.R()) - DRAWX,
			int(rc.B()) - DRAWY);

		SelectObject(_hBackDC, hOldBrush);
		SelectObject(_hBackDC, hOldPen);
	}
#endif
}


	