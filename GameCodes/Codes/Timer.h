#ifndef Timer_h__
#define Timer_h__

class CTimer :  public CComponent
{
	DeclRTTI(CTimer,CComponent);
public:
	explicit CTimer(void) : m_fTime(0.f) {}
	virtual	~CTimer(void) {}
private:
	float m_fTime;
public:
	void SetTimer(const float& _fTime) 
	{ 
		m_fTime = _fTime; }
public:
	virtual void Update(void) 
	{
		m_fTime -= fDeltaTime;

		if(m_fTime <= 0.f)
			m_pGameObject->SetActive(false);
	}
};

#endif // Timer_h__
