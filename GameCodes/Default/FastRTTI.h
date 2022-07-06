#ifndef FastRTTI_h__
#define FastRTTI_h__
//XXX  : \µÚ °ø¹é

class CRTTI
{  
public:  
	CRTTI( const char* const strClassName, const CRTTI* const pBaseRTTI )
		:m_strClassName(strClassName),m_pBaseRTTI(pBaseRTTI) {}
	inline const char* GetClassName() const {return m_strClassName;}
	inline const CRTTI* GetBaseRTTI() const {return m_pBaseRTTI;}
private:
	const char*	 const	m_strClassName;
	const CRTTI* const 	m_pBaseRTTI;
};

#define DeclRootRTTI(classname) \
public: \
	virtual const CRTTI*  GetRTTI() const {return GetRTTIInst();} \
	static const CRTTI*   GetRTTIInst()  {static const CRTTI ms_RTTI(#classname, NULL); return &ms_RTTI;} \
	const bool IsKindOf( const CRTTI* const pRTTI, const CRTTI* pObject )const \
{ \
	const char*const pClassName = pRTTI->GetClassName(); \
	while(pObject != NULL) \
{ \
	if(pObject->GetClassName() == pClassName) return true; \
			else pObject = pObject->GetBaseRTTI(); \
} \
	return false; \
} 

#define DeclRTTI(classname, baseclassname) \
public: \
	virtual const CRTTI*  GetRTTI() const {return GetRTTIInst();} \
	static  const CRTTI*  GetRTTIInst() {static const CRTTI ms_RTTI(#classname, baseclassname::GetRTTIInst()); return &ms_RTTI;}

#define IsDynamicCast(classname, pObject) \
	pObject->IsKindOf(classname::GetRTTIInst(), pObject->GetRTTI())

#endif // FastRTTI_h__
