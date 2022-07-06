#ifndef TemplateSingleton_h__
#define TemplateSingleton_h__

template<typename T>
class TSingleton abstract
{
protected:
			 TSingleton(void) {}
	virtual ~TSingleton(void) {}
public:
	static T& Inst(void) {
		static T Instance;
		return Instance;
	}
private:
	TSingleton&	operator=(const TSingleton& rhs);
	TSingleton(const TSingleton& rhs);
};

#endif // TemplateSingleton_h__
