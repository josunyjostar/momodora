#ifndef UI_h__
#define UI_h__

class CUI : public CGameObject
{
	DeclRTTI(CUI,CGameObject);
public:
	explicit CUI(void){}
	virtual ~CUI(void){}
};

#endif // UI_h__
