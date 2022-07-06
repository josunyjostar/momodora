#ifndef Loading_h__
#define Loading_h__

class CLoading
{
public:
	enum LOADINGID {LOADING_TITLE, LOADING_STAGE1,LOADING_STAGE2,LOADING_STAGE3,LOADING_STAGE4,LOADING_ENDING, LOADING_END};
public:
	explicit CLoading(void):m_bFinish(false),m_LoadingID(LOADING_TITLE) {}
	~CLoading(void) {}
private:
	HANDLE				m_hThread;
	CRITICAL_SECTION	m_Crt;
	bool				m_bFinish;
	LOADINGID			m_LoadingID;
public:
	void				Set_LoadingID(LOADINGID _ID);
	LOADINGID			Get_LoadingID(void) const {return m_LoadingID;}
	bool				GetFinish(void) const {return m_bFinish;}
	CRITICAL_SECTION	GetCrt(void) const {return m_Crt;}
public:
	HRESULT Init(void);
	void	ResourceLoad(void);
	void	Release(void);
};

#endif // Loading_h__
