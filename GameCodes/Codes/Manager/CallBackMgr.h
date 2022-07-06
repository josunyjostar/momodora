#ifndef CallBackMgr_h__
#define CallBackMgr_h__

typedef struct tagTimer
{
	char* pFuncName;
	void* pData;
	float fMaxTime;
	float fDelayTime;
	bool  bRepeat;

	virtual void Call(void)PURE;
	virtual ~tagTimer(void) {}

}tTimer;

template<typename T>
struct BindingTimer : public tTimer
{
	T* pObj;
	virtual void Call(void)
	{
		if (pObj->GetActive())
		{	
			pObj->FunctionCall(pObj,pFuncName,pData);
		}
	}
};

static const int MAX_TIMER = 256;

class CCallBackMgr : public TSingleton<CCallBackMgr>
{
	friend TSingleton;
private:
	explicit CCallBackMgr(void);
	virtual ~CCallBackMgr(void) {this->Release();}

private:
	tTimer* m_Timer[MAX_TIMER];
	int		m_iSize;

public:
	void Update(void);
	void Release(void);

	//TODO :  m_iSize°ü¸®.
	template<typename T>
	void AddFunc(T* _pObj, char* _pFuncName, float _fTime, void* _pData, bool _bRepeat = false)
	{
		BindingTimer<T>* pTimer = new BindingTimer<T>;

		pTimer->pObj		= _pObj;
		pTimer->pFuncName	= _pFuncName;
		pTimer->fMaxTime	= _fTime;
		pTimer->fDelayTime  = _fTime;
		pTimer->pData		= _pData;
		pTimer->bRepeat		= _bRepeat;

		for(int i = 0; i < m_iSize ; ++i)
		{
			if (m_Timer[i])
				continue;

			m_Timer[m_iSize++] = pTimer;
			return;
		}
		m_Timer[m_iSize++] = pTimer;
	}
	
	void DeleteFunc(CGameObject* _pObj, char* _pFuncName);
};
#endif // CallBackMgr_h__
