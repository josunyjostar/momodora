
void CFennel::State_Ready(void)
{

}

void CFennel::State_Intro(void)
{

	static int Next = 0;

	if (!m_pAnimator->IsPlay())
	{
		switch(Next++)
		{
		case 1:
			m_pAnimator->Play("Fennel_Intro2");
			break;
		case 2:
			m_pAnimator->Play("Fennel_Intro3");
			break;
		case 3:
			m_pAnimator->Play("Fennel_Intro4");
			break;
		case 4:
			m_iState = AI_IDLE;
			break;
		}
	}
}

void CFennel::State_Idle(void)
{
	if (m_fDistance_x < 0.f)
		m_pAnimator->SetFlipX(false);
	else
		m_pAnimator->SetFlipX(true);

	m_fDelayTime += fDeltaTime;

	if (m_fDelayTime > m_fAIChangeTime)
	{
		switch(rand()%5)
		{
		case 0:
			m_iState = AI_ATK_1;
			break;
		case 1:
			m_iState = AI_BUFF;
			break;
		case 2:
			m_iState = AI_DASH;
			break;
		case 3:
			this->Jump();
			break;
		case 4:
			m_iState = AI_BACKFLIP;
			break;
		default:
			m_iState = AI_IDLE;
			break;
		}
	}
}

void CFennel::State_Impact(void)
{
	static tPos EffectPos;
	static const tSize EffectSize(256.f*2.2f,182.f*2.2f);

	if (11 == m_pAnimator->GetFrame())
	{
		if (m_bAtkCol)
		{
			m_bAtkCol = false;

			if (m_pTarget)
				EffectPos = tPos(m_pTarget->GetX(),CSceneMgr::Inst().GetGroundHeight()-200.f);
			else	
				EffectPos = m_Rect.Pos()+tPos(m_bFilp?20.f:-20.f,-166.f);

			HITBOX(m_fAtkPower*2.f,tRect(EffectPos,EffectSize+tSize(-220.f,0.f)),0.45f);
			CAniEffect::Create("Impact",m_bFilp,false,255)->SetEffectSize(tRect(EffectPos,EffectSize));
		}
	}
	else if (!m_pAnimator->IsPlay())
	{
		m_pBlackFilter->SetActive(false);
		m_bAtkCol = true;

		m_iState = AI_IDLE;
	}
}

void CFennel::State_BackFlip(void)
{
	static int iFrame = m_pAnimator->GetFrame();
	iFrame = m_pAnimator->GetFrame();
	static float fDodgeSpeed = 260.f;

	if (2 < iFrame)
	{
		fDodgeSpeed = 260.f;
		if (iFrame > 10)
			fDodgeSpeed = 0.f;
	
		if (m_bFilp)
			m_Rect.x += -fDodgeSpeed * fDeltaTime;
		else
			m_Rect.x += fDodgeSpeed * fDeltaTime;
	}
	
	if (!m_pAnimator->IsPlay())
	{
		switch(rand()%2)
		{
		case 0:
			m_iState = AI_ATK_1;
			break;
		case 1:
			m_iState = AI_IDLE;
			break;
		}
	}
}

void CFennel::State_Dash(void)
{
	m_fDelayTime += fDeltaTime;

	if (m_pAnimator->GetPlayAniName() == "Fennel_Dash")
	{
		if (m_bFilp)
		{	
			if(m_fSpeed <= 0.f)
				m_fSpeed = 800.f;

			m_fSpeed += m_fAccel * fDeltaTime;
			m_Rect.x += m_fSpeed * fDeltaTime;
		}
		else
		{	
			if(m_fSpeed >= 0.f)
				m_fSpeed = -800.f;

			m_fSpeed += -m_fAccel * fDeltaTime;
			m_Rect.x +=  m_fSpeed * fDeltaTime;
		}
	}

	if (m_fAIChangeTime < m_fDelayTime)
	{
		m_iState = AI_BRAKE;
	}
}

void CFennel::State_Break(void)
{
	if (!m_pAnimator->IsPlay())
	{
		if(m_PreBehavior.top() == &CFennel::State_Dash)
		{
			switch(rand()%3)
			{
			case 0:
				m_iState = AI_ATK_1;
				break;
			case 1:
				m_iState = AI_BUFF;
				break;
			case 2:
				this->Jump();
				break;
			}
		}
		else
		{
			switch(rand()%3)
			{
			case 0:
				m_iState = AI_BACKFLIP;
				break;
			case 1:
				m_iState = AI_IDLE;
				break;
			case 2:
				m_iState = AI_IDLE;
				break;
			}
		}
	}
}

void CFennel::State_Buff(void)
{
	if (3 == m_pAnimator->GetFrame())
	{
		if (m_bAtkCol)
		{
			m_bAtkCol = false;
			CMasicCircle::Create(tRect(m_Rect.Pos()+tPos(0.f,-120.f),tSize(320.f,320.f)),1.05f);
			this->BuffStart();
		}
	}

	if (!m_pAnimator->IsPlay())
	{
		m_bAtkCol = true;

		switch(rand()%4)
		{
		case 0:
			m_iState = AI_IDLE;
			break;
		case 1:
			m_iState = AI_BACKFLIP;
			break;
		case 2:
			m_iState = AI_DASH;
			break;
		case 3:
			m_iState = AI_ATK_1;
			break;
		}
	}
}

void CFennel::State_Jump(void)
{
	if (m_bFilp)
		m_Rect.x += 600.f * fDeltaTime;
	else
		m_Rect.x += -600.f * fDeltaTime;

	if (m_fVelocity < -50.f)
	{
		m_iState = AI_JUMP_ATK;
		m_iJumpAtkDir = (m_bFilp?1:-1);
	}
}

void CFennel::State_Fall(void)
{
	if (!m_pAnimator->IsPlay())
	{
		switch(rand()%3)
		{
		case 0:
			m_iState = AI_ATK_1;
			break;
		case 1:
			m_iState = AI_BACKFLIP;
			break;
		case 2:
			m_iState = AI_DASH;
			break;
		}
	}
}

void CFennel::State_Atk_InAir(void)
{
	m_fVelocity += 1000.f*fDeltaTime;

	m_Rect.x += 600.f * fDeltaTime * m_iJumpAtkDir;

	if (m_iJumpAtkDir == -1)
		m_pAnimator->SetFlipX(false);
	else
		m_pAnimator->SetFlipX(true);

	static int iFrame = m_pAnimator->GetFrame();
	iFrame = m_pAnimator->GetFrame();

	if (4 < iFrame && iFrame < 10)
		HITBOX(m_fAtkPower*1.2f,tRect(m_Rect.Pos(), tSize(300.f, 120.f)),0.04f);
	else if (11 == iFrame)
	{
		if (m_bWallCol)
			m_iState = AI_FALL;
	}
}

void CFennel::State_DownAtk(void)
{
	static int iFrame = m_pAnimator->GetFrame();
	iFrame = m_pAnimator->GetFrame();

	if (m_bAtkCol && 2 == iFrame)
	{
		m_bAtkCol = false;
		CDemon::Create(1000.f,m_bFilp)->SetPos(m_Rect.Pos()+tPos(0.f,-100.f));
		HITBOX(m_fAtkPower*2.f,tRect(m_Rect.Pos(), tSize(300.f, 220.f)),0.2f);
	}
	else if (12 == iFrame)
	{	
		m_bAtkCol = true;

		switch(rand()%3)
		{
		case 0:
			m_iState = AI_ATK_1;
			break;
		case 1:
			m_iState = AI_BACKFLIP;
			break;
		case 2:
			m_iState = AI_DASH;
			break;
		}
	}
}

void CFennel::State_Atk_1(void)
{
	static int iFrame = m_pAnimator->GetFrame();
	iFrame = m_pAnimator->GetFrame();
	static const float fSpeed = 190.f;

	if (2 < iFrame && iFrame < 19)
	{
		if (m_bFilp)
			m_Rect.x += fSpeed * fDeltaTime;
		else
			m_Rect.x += -fSpeed * fDeltaTime;

		if (6 == iFrame)
			HITBOX(m_fAtkPower*1.4f,tRect(m_Rect.Pos(), tSize(300.f, 120.f)),0.02f);
		else if (15 == iFrame)
			HITBOX(m_fAtkPower*1.6f,tRect(m_Rect.Pos(), tSize(260.f, 120.f)),0.02f);
	}
	else if (22 == iFrame)
	{
		switch(rand()%3)
		{
		case 0:
			m_iState = AI_IDLE;
			break;
		case 1:
			this->Jump();
			break;
		case 2:
			m_iState = AI_IMPACT;
			break;
		}

	}
}

void CFennel::State_Hit(void)
{
	m_fDelayTime += fDeltaTime;

	float p = pow(10.f,5) / m_fDelayTime;

	m_Rect.x = m_HitPos.x + sin(p)*3.5f;
	m_Rect.y = m_HitPos.y - cos(p)*4.7f;

	if (!m_pAnimator->IsPlay())
	{
		m_iState = AI_IDLE;
	}
}

void CFennel::State_Dead(void)
{
	m_fDelayTime += fDeltaTime;

	float f = sin(1/(m_fDelayTime*10+0.5f));
	m_pAnimator->SetAlphaVal((BYTE)(255*f));

	if (f < 0.17f)
		this->SetActive(false);
}

