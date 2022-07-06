#ifndef KeyState_h__
#define KeyState_h__

enum KEY_STATE
{
	KEY_NULL , KEY_DOWN , KEY_PUSH , KEY_UP
};

const unsigned int MAX_KEY_TYPE = 128; // 아스키 코드
const unsigned int MAX_COMMAND  = 8;

class CKeyState : public TSingleton<CKeyState>
{
	friend TSingleton;
private:
	explicit CKeyState(void);
	virtual ~CKeyState(void){}
public:
	int		m_CommandBuffer[MAX_COMMAND];
	int		m_iAttack;
	int		m_iRoll;
	int		m_iFirstKey;
public:
	tPos MousePos(void) const {return m_MousePos;}
	bool IsInput(void)  const {return m_bInput;}

	void Update(void);

	//Generic Method
	bool Is(const int& _VK)		{return m_eKeyData[GetKey(_VK)] != KEY_NULL;}
	bool IsPush(const int& _VK)	{return m_eKeyData[GetKey(_VK)] == KEY_PUSH;}
	bool IsDown(const int& _VK)	{return m_eKeyData[GetKey(_VK)] == KEY_DOWN;}
	bool IsUp(const int& _VK)	{return m_eKeyData[GetKey(_VK)] == KEY_UP;}

	//Special Method
	bool Up(SHORT _KeyState = KEY_NULL)		const {return m_eKeyData[m_iUp]	== _KeyState;}
	bool Down(SHORT _KeyState = KEY_NULL)   const {return m_eKeyData[m_iDown]  == _KeyState;}
	bool Left(SHORT _KeyState = KEY_NULL)	const {return m_eKeyData[m_iLeft]  == _KeyState;}
	bool Right(SHORT _KeyState = KEY_NULL)  const {return m_eKeyData[m_iRight] == _KeyState;}
	bool Attack(SHORT _KeyState = KEY_NULL) const {return m_eKeyData[m_iAttack] == _KeyState;}
	bool Roll(SHORT _KeyState = KEY_NULL)   const {return m_eKeyData[m_iRoll] == _KeyState;}

	void ClearCommandBuffer(void);
private:
	KEY_STATE	m_eKeyData[MAX_KEY_TYPE];
	bool		m_bInput;
	tPos		m_MousePos;

	int			m_iObserveKey[MAX_KEY_TYPE];
	int			m_iSize;

	int			m_iUp;
	int			m_iDown;
	int			m_iLeft;
	int			m_iRight;

	float		m_fInputDelay;

	typedef	void (CKeyState::*KeyFunc)(const SHORT& _state,const int& i);
	static	KeyFunc m_fpKeyFunc[];

private:
	int			GetKey(const int& _VK);
	inline void	KeyNull(const SHORT& _state,const int& i) {if(_state){m_eKeyData[m_iObserveKey[i]] = KEY_DOWN;this->InputCommandBuffer(m_iObserveKey[i]);}}
	inline void	KeyDown(const SHORT& _state,const int& i) {/*if(_state)*/m_eKeyData[m_iObserveKey[i]] = KEY_PUSH;/*else m_eKeyData[m_iObserveKey[i]]=KEY_UP;*/}//else m_eKeyData[m_iObserveKey[i]]=KEY_UP; 필요없을수도잇다
	inline void	KeyPush(const SHORT& _state,const int& i) {if(!_state)m_eKeyData[m_iObserveKey[i]] = KEY_UP;}
	inline void	KeyUp(const SHORT& _state,const int& i)	  {/*if(_state)m_eKeyData[m_iObserveKey[i]] = KEY_DOWN;else */m_eKeyData[m_iObserveKey[i]]=KEY_NULL;}

	void InputCommandBuffer(int _KeyType);

};

#endif // KeyState_h__
