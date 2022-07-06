void CFennel::Ani_Ready(void)
{
	m_pAnimator->Play("Fennel_Intro1",true);
}

void CFennel::Ani_Intro(void)
{
	m_pAnimator->Play("Fennel_Intro1");
}

void CFennel::Ani_Idel(void)
{
	m_fAIChangeTime = 1.5f;
	m_pAnimator->Play("Fennel_Idle");
}

void CFennel::Ani_Impact(void)
{
	m_pBlackFilter = CGameObject::Create<CBlackFilter>();
	m_pBlackFilter->SetFilterMode(CBlackFilter::FM_INOUT);
	m_pAnimator->Play("Fennel_Impact");
}

void CFennel::Ani_BackFlip(void)
{
	m_pAnimator->Play("Fennel_BackFlip");
}

void CFennel::Ani_Dash(void)
{
	m_fAIChangeTime = 1.5f + (rand()%5)*0.1f;
	this->AfterImage(0.11f,m_fAIChangeTime);
	m_pAnimator->Play("Fennel_Ready_Dash");
}

void CFennel::Ani_Break(void)
{
	m_pAnimator->Play("Fennel_Brake");
}

void CFennel::Ani_Buff(void)
{
	m_pAnimator->Play("Fennel_Buff");
}

void CFennel::Ani_Jump(void)
{
	m_pAnimator->Play("Fennel_Jump");
}

void CFennel::Ani_Fall(void)
{
	m_pAnimator->Play("Fennel_Brake");
}

void CFennel::Ani_Atk_InAir(void)
{
	m_pAnimator->Play("Fennel_Atk_InAir");
}

void CFennel::Ani_DownAtk(void)
{
	m_pAnimator->Play("Fennel_Atk_Down");
}

void CFennel::Ani_Atk_1(void)
{
	m_pAnimator->Play("Fennel_Atk_1");
}

void CFennel::Ani_Hit(void)
{
	m_pAnimator->Play("Fennel_Hit");
}

void CFennel::Ani_Dead(void)
{
	m_pAnimator->Play("Fennel_Hit");
}
