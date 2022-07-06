#include "stdafx.h"
#include "KeyState.h"

CKeyState::KeyFunc CKeyState::m_fpKeyFunc[] =
{
	&CKeyState::KeyNull,
	&CKeyState::KeyDown,
	&CKeyState::KeyPush,
	&CKeyState::KeyUp
};


CKeyState::CKeyState(void)
:m_iSize(0)
,m_iUp(0)
,m_iDown(0)
,m_iLeft(0)
,m_iRight(0)
,m_iAttack(0)
,m_iRoll(0)
,m_bInput(false)
,m_iFirstKey(0)
,m_fInputDelay(0.f)
{
	memset(m_iObserveKey,0,sizeof(m_iObserveKey));
	memset(m_eKeyData,0,sizeof(m_eKeyData));
	memset(&m_MousePos,0,sizeof(m_MousePos));
	memset(m_CommandBuffer,0,sizeof(m_CommandBuffer));

	m_iObserveKey[m_iSize++] = m_iUp	= VK_UP;
	m_iObserveKey[m_iSize++] = m_iDown	= VK_DOWN;
	m_iObserveKey[m_iSize++] = m_iLeft	= VK_LEFT;
	m_iObserveKey[m_iSize++] = m_iRight = VK_RIGHT;
	m_iObserveKey[m_iSize++] = m_iAttack = 'Z';
	m_iObserveKey[m_iSize++] = m_iRoll	 = 'X';
}

void CKeyState::Update(void)
{
	m_bInput = false;

	m_fInputDelay += fDeltaTime;

	if (m_fInputDelay > 0.2f)
	{
		m_fInputDelay = 0.f;
		this->ClearCommandBuffer();
	}

	for(int i = 0; i < m_iSize; ++i) {
		SHORT state = GetAsyncKeyState(m_iObserveKey[i]);

		//KEY_STATE ekey = m_KeyData[m_ObserveKey[i]];

		(this->*m_fpKeyFunc[m_eKeyData[m_iObserveKey[i]]])(state,i);

		if(m_eKeyData[m_iObserveKey[i]] != KEY_NULL) 
			m_bInput = true;
	}

	static POINT _WinMousePos;

	GetCursorPos(&_WinMousePos);
	ScreenToClient(g_hWnd, &_WinMousePos);

	m_MousePos.x = (float)_WinMousePos.x + DRAWX;
	m_MousePos.y = (float)_WinMousePos.y + DRAWY;

}

 int CKeyState::GetKey(const int& _VK) 
{
	for(int i=0; i < m_iSize ; ++i)
	{
		if (_VK == m_iObserveKey[i])
			return _VK;
	}
	m_iObserveKey[m_iSize++] = _VK;

	return _VK;
}

 void CKeyState::InputCommandBuffer(int _KeyType)
 {
	for(int i = 0; i < MAX_COMMAND -1 ; ++i)
	{
		m_CommandBuffer[MAX_COMMAND - i - 1] = m_CommandBuffer[MAX_COMMAND - i -2];
	}
	m_iFirstKey = m_CommandBuffer[0] = _KeyType;
	m_fInputDelay = 0.f;
 }

 void CKeyState::ClearCommandBuffer(void)
 {
	memset(m_CommandBuffer,0,sizeof(m_CommandBuffer));
	m_iFirstKey = 0;
 }

