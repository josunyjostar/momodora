
void CImp::State_Idle(void)
{
	if(!m_bWallCol)
	{	
		if(m_fVelocity < 0.f) 
		{
			if (m_iPrevState != AI_FALL)			
			{	
				m_iState = AI_FALL;
				return;
			}
		}
	}

	if(m_pTarget) 
	{
		m_fDelayTime += fDeltaTime;

		if(m_pTarget->GetPos().x > m_Rect.x) 
			m_pAnimator->SetFlipX(false);
		else
			m_pAnimator->SetFlipX(true);

		if (m_fDelayTime > m_fAIChangeTime)
		{
			switch(rand()%2)
			{
			case 0:
				m_iState = AI_WALK;
				break;
			case 1:
				m_fVelocity = m_fJumpValue+m_iRandValue;
				m_iState = AI_JUMP;
				break;
			case 2:
				m_iState = AI_THROW;
				break;
			default:
				break;
			}
			return;
		}
	}
	else
	{	
		switch(rand()%1)
		{
		case 0:
			m_iState = AI_WALK;
			break;
		case 1:
			m_fVelocity = m_fJumpValue+m_iRandValue;
			m_iState = AI_JUMP;
			break;
		case 2: 
			m_iState = AI_THROW;
			break;
		case 3:
			m_iState = AI_WALK;
			break;
		default:
			break;
		}
			
	}
}

void CImp::State_Fall(void)
{
	if(m_pTarget) 
	{
		if(m_fDistance_x > 0.f) 
		{	
			m_pAnimator->SetFlipX(false);
			if(m_fDistance_x > m_fAtkDis)
				m_Rect.x += fDeltaTime*m_iRandValue;
		}
		else
		{	
			m_pAnimator->SetFlipX(true);
			if(m_fDistance_x < -m_fAtkDis)
				m_Rect.x -= fDeltaTime*m_iRandValue;
		}
	}

	if (m_bWallCol)
		m_iState = AI_IDLE;
}

void CImp::State_Jump(void)
{
	m_fDelayTime += fDeltaTime;

	if (m_fVelocity < 50.f)
		m_iState = AI_FALL;
	else
	{
		if(m_pTarget) 
		{
			if(m_fDistance_x > 0.f) 
			{	
				m_pAnimator->SetFlipX(false);
				if(m_fDistance_x > m_fAtkDis)
					m_Rect.x += fDeltaTime*m_iRandValue;
			}
			else
			{	
				m_pAnimator->SetFlipX(true);
				if(m_fDistance_x < -m_fAtkDis)
					m_Rect.x -= fDeltaTime*m_iRandValue;			
			}
		}
		else
			m_iState = AI_THROW;
	}

	if (m_fDelayTime > m_fAIChangeTime )
		m_iState = AI_THROW;
}

void CImp::State_Throw(void)
{
	if (m_bThrowKnife)
	{	
		if(5 == m_pAnimator->GetFrame())
		{
			m_bThrowKnife = false;
			CGameObject::Create<CKnife>()->SetKnife(m_pAnimator->IsFlip(),25)->SetPos(m_Rect.Pos()+tPos(0.f,-8.f));
		}
	}

	if (!m_pAnimator->IsPlay())
		m_iState = AI_IDLE;
}

void CImp::State_ShiedWalk(void)
{
	m_fDelayTime += fDeltaTime;

	if(m_pTarget) 
	{
		if (abs(m_fDistance_x) > 150)
		{
			if(m_fDistance_x > 0.f) 
			{	
				if (m_pAnimator->GetFrame() > 3)
				{
					m_pAnimator->SetFlipX(false);
					m_Rect.x += fDeltaTime*m_fWalkSpeed;
				}
			}
			else
			{	if (m_pAnimator->GetFrame() > 3)
				{
					m_pAnimator->SetFlipX(true);
					m_Rect.x -= fDeltaTime*m_fWalkSpeed;
				}
			}
		}
		else
		{
			switch(rand()%3)
			{
			case 0:
				m_iState = AI_ATK_1;
				break;
			case 1:
				m_iState = AI_WALK;
				break;
			default:
				break;
			}

			return;
		}
	}
	else
	{
		if (m_pAnimator->GetFrame() > 3)
		{
			if (m_pAnimator->IsFlip())
				m_Rect.x -= fDeltaTime*m_fWalkSpeed;
			else
				m_Rect.x += fDeltaTime*m_fWalkSpeed;
		}
	}
	
	if (m_fDelayTime > m_fAIChangeTime)
		m_iState = AI_IDLE;

}

void CImp::State_Atk_1(void)
{
	if (!m_pAnimator->IsPlay())
		m_iState = AI_FALL;
}

void CImp::State_Hit(void)
{
	static float fRunTime = 0.f;
	fRunTime += fDeltaTime;

	float p = pow(10.f, 5) / fRunTime;	

	m_Rect.x = m_HitPos.x + sinf(p)*5.5f;
	m_Rect.y = m_HitPos.y + cosf(p)*3.5f;

	if (!m_pAnimator->IsPlay())
	{	
		m_iState =AI_IDLE;
		fRunTime = 0.f;
	}
}

void CImp::State_Dead(void)
{
	m_fVelocity = 0.f;

	static float fRunTime = 0.f;
	fRunTime += fDeltaTime;

	float p = pow(10.f, 5) / fRunTime;	

	m_Rect.x = m_HitPos.x + sinf(p)*2.5f;
	m_Rect.y = m_HitPos.y + cosf(p)*1.5f;

	static float fTime = 0.f;
	static float f = 0.f;
	fTime += fDeltaTime*15.f;

	f = sin(1/(fTime+0.5f));

	m_pAnimator->SetAlphaVal((BYTE)(255*f));

	if (f < 0.17f)
	{
		this->SetActive(false);
		f = fTime = 0.f;
	}
}

