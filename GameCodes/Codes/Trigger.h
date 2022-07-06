#ifndef Trigger_h__
#define Trigger_h__

class CTrigger : public CCollider
{
	DeclRTTI(CTrigger,CCollider)
public:
	explicit CTrigger(void) {m_bTrigger = true;}
	virtual ~CTrigger(void) {}
};

#endif // Trigger_h__
