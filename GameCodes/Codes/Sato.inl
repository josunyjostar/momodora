#include "HitFilter.h"

void CSato::State_Idle(void)
{
	m_fDelayTime += fDeltaTime;

	if (m_pTarget)
	{
		if (m_fDistance_x < 0.f)
			m_pAnimator->SetFlipX(false);
		else
			m_pAnimator->SetFlipX(true);

		if (m_fDelayTime > m_fAIChangeTime)
		{
			switch(rand()%5)
			{
			case 0:
				m_iState = AI_ATK_1;
				break;
			case 1:
				m_iState = AI_ATK_3;
				break;
			case 2:
				m_iState = AI_ATK_3;
				break;
			case 3:
				m_iState = AI_ATK_3;
				break;
			case 4:
				m_iState = AI_DODGE;
				break;
			default:
				break;
			}
		}
	}
	else
	{
		if (m_fDelayTime > m_fAIChangeTime)
		{
			switch(rand()%4)
			{
			case 0:
				m_iState = AI_ATK_1;
				break;
			case 1:
				m_iState = AI_ATK_2;
				break;
			case 2:
				m_iState = AI_DODGE;
				break;
			default:
				break;
			}
		}
	}

}

void CSato::State_Dodge(void)
{
	if (m_bFilp)
		m_Rect.x += m_fRollSpeed* fDeltaTime;
	else
		m_Rect.x += -m_fRollSpeed* fDeltaTime;

	if (!m_pAnimator->IsPlay())
		m_iState = AI_IDLE;
}

void CSato::State_Hit(void)
{
	static float fRunTime = 0.f;
	fRunTime += fDeltaTime;

	float p = pow(10.f, 5) / fRunTime;	

	m_Rect.x = m_HitPos.x + sinf(p)*7.5f;
	m_Rect.y = m_HitPos.y + cosf(p)*5.5f;

	if (!m_pAnimator->IsPlay())
	{	
		m_iState = AI_IDLE;
		fRunTime = 0.f;
	}
}

void CSato::State_Atk_1(void)
{
	m_fDelayTime += fDeltaTime*15.f;
	
	if (5 > m_pAnimator->GetFrame())
	{
		if (!m_bFilp)
			m_fSpeed -= m_fAccel*fDeltaTime;
		else
			m_fSpeed += m_fAccel*fDeltaTime;

		m_Rect.x += m_fSpeed*fDeltaTime;
	}
	else
	{
		if (!m_bFilp)
			m_fSpeed -= m_fAccel*fDeltaTime;
		else
			m_fSpeed += m_fAccel*fDeltaTime;

		m_Rect.x += m_fSpeed*fDeltaTime/m_fDelayTime;
	}

	if( 5 == m_pAnimator->GetFrame())
	{
		if (m_bAtkCol)
		{	
			m_bAtkCol = false;
			HITBOX(25,tRect(m_Rect.Pos()+tPos(((m_bFilp)?85.f:-85.f),-50.f), tSize(110.f, 100.f)),0.2f);
		}
	}

	if (!m_pAnimator->IsPlay())
	{
		switch(rand()%4)
		{
		case 0:
			m_Rect.SetSize(m_OriSize);
			m_iState = AI_IDLE;
			break;
		case 1:
			m_Rect.SetSize(m_Atk2Size);
			m_iState = AI_ATK_2;
			break;
		case 2:
			m_Rect.SetSize(m_Atk2Size);
			m_iState = AI_ATK_2;
			break;
		case 3:
			m_Rect.SetSize(m_Atk2Size);
			m_iState = AI_ATK_3;
			break;
		}
		m_bAtkCol = true;
	}
}

void CSato::State_Atk_2(void)
{
	if( 5 > m_pAnimator->GetFrame())
	{
		if (m_PreBehavior.top() == &CSato::State_Atk_1)
		{
			if (!m_bFilp)
				m_fSpeed -= m_fAccel*fDeltaTime*0.4f;			
			else
				m_fSpeed += m_fAccel*fDeltaTime*0.4f;

			m_Rect.x += m_fSpeed*fDeltaTime;
		}
	}

	if( 3 == m_pAnimator->GetFrame())
	{
		if (m_bAtkCol)
		{	
			m_bAtkCol = false;
			HITBOX(55,tRect(m_Rect.Pos()+tPos(((m_bFilp)?40.f:-40.f),-100.f), tSize(155.f, 180.f)),0.2f);
		}
	}

	if (!m_pAnimator->IsPlay())
	{
		m_bAtkCol = true;

		switch(rand()%3)
		{
		case 0:
			m_Rect.SetSize(m_OriSize);
			m_iState = AI_IDLE;
			break;
		case 1:
			m_Rect.SetSize(m_Atk2Size);
			m_iState = AI_ATK_3;
			break;
		case 2:
			m_Rect.SetSize(m_Atk2Size);
			m_iState = AI_ATK_1;
			break;
		}

		m_Rect.SetSize(m_OriSize);
	}
}

void CSato::State_Atk_3(void)
{
	static float fTargetPosX = 0.f;
	static float fDifY	= 0.f;
	
	if (0 == m_pAnimator->GetFrame())
	{
		if (m_pTarget)
		{	
			fTargetPosX = m_pTarget->GetPos().x;
			fDifY = abs(m_pTarget->GetPos().y - m_Rect.y);
		}
		else
			fTargetPosX = m_Rect.x;
	}
	else if(5 == m_pAnimator->GetFrame())
	{
		if (fDifY > 200.f)
		{
			m_iState = AI_ATK_1;
			m_Rect.SetSize(m_OriSize);
			return;
		}

		if (m_bAtkCol)
		{	
			static float fIceBurgY = 0.f;
			fIceBurgY = CSceneMgr::Inst().GetGroundHeight() - 150.f;

			m_bAtkCol = false;
			HITBOX(float(rand()%10+40),tRect(tPos(fTargetPosX,fIceBurgY), tSize(145.f, 280.f)),0.3f);
			CAniEffect::Create("IceBerg",m_bFilp,false,255)->SetEffectSize(tRect(tPos(fTargetPosX,fIceBurgY),tSize(156.f,296.f)));
			CCamera::Inst().Shake(0.6f);
		}
	}

	if (!m_pAnimator->IsPlay())
	{
		m_iState = AI_IDLE;
		m_bAtkCol = true;
		m_Rect.SetSize(m_OriSize);
	}
}

void CSato::State_Atk_4(void)
{
	static float fTargetPosX = 0.f;

	m_fDelayTime += fDeltaTime;

	if (1 == m_pAnimator->GetFrame())
	{	
		if (m_pTarget)	
			fTargetPosX = m_pTarget->GetPos().x;
		else
			fTargetPosX = m_Rect.x;
	}
	else if(12 == m_pAnimator->GetFrame())
	{
		if (m_bAtkCol)
		{	
			m_bAtkCol = false;
			HITBOX(float(rand()%10+40),tRect(tPos(fTargetPosX,m_Rect.y-210.f), tSize(130.f, 1000.f)),0.3f);
			CGameObject::Create<CHitFilter>()->SetMode(CHitFilter::FM_WHITE)->AddComponent<CTimer>()->SetTimer(0.033f);
			CAniEffect::Create("Thunder",false,false,255)->SetEffectSize(tRect(tPos(fTargetPosX,m_Rect.y-210.f),tSize(160.f,1000.f)));
			CCamera::Inst().Shake(0.6f);
		}
	}
	else if (m_fDelayTime > 0.89f && m_fDelayTime < 0.9f)
	{
		int Randx = rand()%130 + 100;
		tPos  ThunderPos(m_Rect.x+Randx,m_Rect.y-200.f);
		HITBOX(float(rand()%10+15),tRect(ThunderPos, tSize(80.f, 1000.f)),0.3f);
		CGameObject::Create<CHitFilter>()->SetMode(CHitFilter::FM_WHITE)->AddComponent<CTimer>()->SetTimer(0.03f);
		CAniEffect::Create("Thunder2",false,false,255)->SetEffectSize(tRect(ThunderPos,tSize(80.f,1000.f)));
	}
	else if (m_fDelayTime > 1.09f && m_fDelayTime < 1.11f)
	{
		int Randx = (rand()%130 + 100)*-1;
		tPos  ThunderPos(m_Rect.x+Randx,m_Rect.y-200.f);
		HITBOX(float(rand()%10+15),tRect(ThunderPos, tSize(80.f, 1000.f)),0.3f);
		CAniEffect::Create("Thunder2",false,false,255)->SetEffectSize(tRect(ThunderPos,tSize(100.f,1000.f)));
	}

	if (!m_pAnimator->IsPlay())
	{
		m_iState = AI_IDLE;
		m_bAtkCol = true;
		m_Rect.SetSize(m_OriSize);
	}
}

void CSato::State_Dead(void)
{
	static float fRunTime = 0.f;
	fRunTime += fDeltaTime;

	float p = pow(10.f, 5) / fRunTime;	

	m_Rect.x = m_HitPos.x + sinf(p)*4.9f;
	m_Rect.y = m_HitPos.y + cosf(p)*3.5f;

	float f = sin(1/(fRunTime*10+0.5f));
	m_pAnimator->SetAlphaVal((BYTE)(255*f));

	if (f < 0.17f)
	{
		this->SetActive(false);
		fRunTime = 0.f;
	}
}
