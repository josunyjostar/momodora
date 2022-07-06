void CMagnolia::State_Idle(void)
{
	m_fDelayTime += fDeltaTime;

	if (m_fDistance_x > 0.f)
		m_pAnimator->SetFlipX(true);
	else
		m_pAnimator->SetFlipX(false);

	if (m_fVelocity < -600.f)
	{
		m_iState = AI_FALL;
		return;
	}

	if (m_fDelayTime > m_fAIChangeTime)
	{	
		switch(rand()%3)
		{
		case 0:
			m_iState = AI_READY_ATK;
			break;
		case 1:
			m_iState = AI_JUMP;
			break;
		default:
			m_fDelayTime = 1.f;
			break;
		}
	}
}

void CMagnolia::State_Jump(void)
{
	if(m_pTarget)
	{
		if (m_bFilp)
		{
			m_fSpeed += m_fAccel * fDeltaTime;
			m_Rect.x += m_fSpeed * fDeltaTime;
		}
		else
		{
			m_fSpeed -= m_fAccel * fDeltaTime;
			m_Rect.x += m_fSpeed * fDeltaTime;
		}
	}

	if (!m_pAnimator->IsPlay())
	{
		if (m_bWallCol)
			m_iState = AI_FALL;
	}
}

void CMagnolia::State_Fall(void)
{
	if (!m_pAnimator->IsPlay())
		m_iState = AI_IDLE;
}

void CMagnolia::State_Hit(void)
{
	m_fDelayTime += fDeltaTime;

	float p = pow(10.f,5) / m_fDelayTime;

	m_Rect.x = m_HitPos.x + sin(p)*3.5f;
	m_Rect.y = m_HitPos.y - cos(p)*4.7f;

	if (!m_pAnimator->IsPlay())
		m_iState = AI_IDLE;
}


void CMagnolia::State_Ready_Atk(void)
{
	m_fDelayTime += fDeltaTime;

	float f = sin(1/(m_fDelayTime*4+0.5f));
	m_pAnimator->SetAlphaVal((BYTE)(255*f));

	if (m_pTarget)
	{
		if (m_bAtkCol && 0.4f < f)
		{
			m_bAtkCol = false;
			CAniEffect::Create("Ring",false,true,255)->SetEffectSize(tRect(m_pTarget->GetPos()+tPos(0.f,-80.f),tSize(300.f,300.f)));
		}
		if (f < 0.45)
			m_Rect.SetPos(m_pTarget->GetPos()+tPos(!m_bFilp?100.f:-100.f,0.f));
	}

	if (!m_pAnimator->IsPlay())
	{
		m_bAtkCol = true;

		if (m_fDistance_y != 0.f)
		{
			m_iState = AI_JUMP;
			return;
		}
		else
		{
			m_iState = AI_ATK_1;
			return;
		}

		switch(rand()%2)
		{
		case 0:
			m_iState = AI_ATK_1;
			break;
		case 1:
			m_iState = AI_JUMP;
			break;
		}
	}
}


void CMagnolia::State_Atk_1(void)
{
	m_fDelayTime += fDeltaTime;

	if (4 == m_pAnimator->GetFrame())
	{
		if (m_bAtkCol)
		{
			m_bAtkCol = false;
			HITBOX(float(rand()%20+10),tRect(m_Rect.Pos()+tPos(((m_bFilp)?130.f:-130.f),-53.f), tSize(180.f, 110.f)),0.25f);
			CAniEffect::Create("Sting",!m_bFilp,false,255)->SetEffectSize(tRect(m_Rect.Pos()+tPos(((m_bFilp)?130.f:-130.f),-51.f),tSize(180.f,110.f)));
			m_pAnimator->SetAlphaVal((BYTE)(255));
			m_pAnimator->SetAlpha(false);
		}	
	}

	if (!m_pAnimator->IsPlay())
	{
		m_iState = AI_IDLE;
		m_bAtkCol = true;
	}
}

void CMagnolia::State_Dead(void)
{
	m_fDelayTime += fDeltaTime;

	float f = sin(1/(m_fDelayTime*10+0.5f));
	m_pAnimator->SetAlphaVal((BYTE)(255*f));

	if (f < 0.17f)
		this->SetActive(false);
}
