#ifndef Component_h__
#define Component_h__

class CComponent abstract: public CObj
{
	template <typename T> friend T* CGameObject::AddComponent(void);
	DeclRTTI(CComponent,CObj)
public:
	explicit CComponent(void):m_pGameObject(NULL) {}
	virtual ~CComponent(void){}
protected:
	CGameObject* m_pGameObject;
public:
	//FIXME: *const& �ۼ��� memory leak ������ �մ°� ���� Ȯ�ε� ������ �ִٸ� *�� ����
	CGameObject*const&  GetGameObject(void) const   {return m_pGameObject;}
	template <typename T>
	T* GetGameObject_NC(void) const {return (T*)m_pGameObject;}
private:
	template<typename T>
	static T* Create(CGameObject* _pGameObj) 
	{
		CComponent* pComponent = new T;
		pComponent->SetGameObject(_pGameObj);
		pComponent->SetTag(_pGameObj->GetTag());
		pComponent->Init();
		pComponent->SetActive(true);
		return (T*)pComponent;
	}
private:
	void SetGameObject(CGameObject* _pGameObj) { m_pGameObject = _pGameObj;}
private:
	CComponent& operator=(const CComponent& rhs);
	CComponent(const CComponent& rhs);
};

#endif // Component_h__