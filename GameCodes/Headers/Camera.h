#ifndef Camera_h__
#define Camera_h__

class CCamera : public TSingleton<CCamera>
{
	friend TSingleton;
public:
	CCamera(void): m_ShakePos(),m_fShakeTime(0.f), m_fRunTime(0.f), m_pTarget(NULL) {}
	virtual ~CCamera(void) {}
private:
	tPos			m_ShakePos;
	float			m_fShakeTime;
	float			m_fRunTime;
	CGameObject*	m_pTarget;
public:
	void	SetTarget(CGameObject* _pTarget) { m_pTarget = _pTarget; if(!_pTarget) {DRAWX=0;DRAWY=0;}}
public:
	void	Update(void) 
	{
		if (m_pTarget)
			Focusing(m_pTarget->GetPos());

		if (m_fShakeTime > m_fRunTime)
		{
			m_fRunTime += fDeltaTime;

			float p = pow(m_fShakeTime*10.f, 5) / m_fRunTime;	

			m_ShakePos.x = sinf(p*2.f)*10.f;
			m_ShakePos.y = cosf(p)*9.5f;
		}
		else 
			m_ShakePos.x = m_ShakePos.y = 0.f;
	}

	void Shake(const float& _fShakeTime)
	{
		static int rndTime = 0;
		rndTime = rand()%7; // [degree 10 = 0.17] ~ [degree 360 = 6.28]
		m_fShakeTime = _fShakeTime + rndTime;
		m_fRunTime = (float)rndTime;
	}

private:
	inline int ScreenPos(const int& _TargetPos, const int& _MapSize,const int& _WndSize)const
	{
		return (_MapSize > _WndSize)*(  (_TargetPos < _MapSize-(_WndSize>>1)) )
			*(_TargetPos > (_WndSize>>1) )*( _TargetPos - (_WndSize>>1) ) 
			+ ( _TargetPos >= (_MapSize - (_WndSize>>1)) )*(_MapSize - _WndSize);
	}

	inline void Focusing(const tPos& _TargetPos) const
	{
		DRAWX = ScreenPos((int)_TargetPos.x,BGACX,WINCX) + (int)m_ShakePos.x;
		DRAWY = ScreenPos((int)_TargetPos.y,BGACY,WINCY) + (int)m_ShakePos.y;
	}
};

#endif // Camera_h__
