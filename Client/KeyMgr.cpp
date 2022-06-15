#include "stdafx.h"
#include "KeyMgr.h"

IMPLEMENT_SINGLETON(KeyMgr);

KeyMgr::KeyMgr(void)
{

}

KeyMgr::~KeyMgr(void)
{

}

void KeyMgr::KeyCheck(void)
{
	m_dwKey = 0;

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		m_dwKey |= KEY_LBUTTON;

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		m_dwKey |= KEY_RBUTTON;

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		m_dwKey |= KEY_ENTER;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		m_dwKey |= KEY_SPACE;

	if (GetAsyncKeyState('1') & 0x8000)
		m_dwKey |= KEY_1;

	if (GetAsyncKeyState('2') & 0x8000)
		m_dwKey |= KEY_2;

	if (GetAsyncKeyState('3') & 0x8000)
		m_dwKey |= KEY_3;

	if (GetAsyncKeyState('4') & 0x8000)
		m_dwKey |= KEY_4;

	if (GetAsyncKeyState('5') & 0x8000)
		m_dwKey |= KEY_5;

	if (GetAsyncKeyState('5') & 0x8000)
		m_dwKey |= KEY_5;

	if (GetAsyncKeyState('5') & 0x8000)
		m_dwKey |= KEY_5;

	if (GetAsyncKeyState('6') & 0x8000)
		m_dwKey |= KEY_6;

	if (GetAsyncKeyState('7') & 0x8000)
		m_dwKey |= KEY_7;

	if (GetAsyncKeyState('8') & 0x8000)
		m_dwKey |= KEY_8;

	if (GetAsyncKeyState('C') & 0x8000)
		m_dwKey |= KEY_C;

	if (GetAsyncKeyState('A') & 0x8000)
		m_dwKey |= KEY_A;

	if (GetAsyncKeyState('H') & 0x8000)
		m_dwKey |= KEY_H;

	if (GetAsyncKeyState('W') & 0x8000)
		m_dwKey |= KEY_W;

	if (GetAsyncKeyState('B') & 0x8000)
		m_dwKey |= KEY_B;

	if (GetAsyncKeyState('Q') & 0x8000)
		m_dwKey |= KEY_Q;


	if (GetAsyncKeyState('S') & 0x8000)
		m_dwKey |= KEY_S;

	if (GetAsyncKeyState('K') & 0x8000)
		m_dwKey |= KEY_K;

	if (GetAsyncKeyState('L') & 0x8000)
		m_dwKey |= KEY_L;


	if (GetAsyncKeyState(VK_F1) & 0x8000)
		m_dwKey |= KEY_F1;

	if (GetAsyncKeyState(VK_F2) & 0x8000)
		m_dwKey |= KEY_F2;

	if (GetAsyncKeyState(VK_F3) & 0x8000)
		m_dwKey |= KEY_F3;

	if (GetAsyncKeyState(VK_F4) & 0x8000)
		m_dwKey |= KEY_F4;


	if (GetAsyncKeyState(VK_F5) & 0x8000)
		m_dwKey |= KEY_F5;

	if (GetAsyncKeyState(VK_F6) & 0x8000)
		m_dwKey |= KEY_F6;

	if (GetAsyncKeyState(VK_F7) & 0x8000)
		m_dwKey |= KEY_F7;

	if (GetAsyncKeyState(VK_F8) & 0x8000)
		m_dwKey |= KEY_F8;

}

bool KeyMgr::KeyPressed(DWORD _dwKey, int iIndex)
{
	//0001		0010
	if (m_dwKey & _dwKey)
	{
		//0011		0001
		m_dwKeyPressed[iIndex] |= _dwKey;
		return false;
	}
	//0011		0001
	else if (m_dwKeyPressed[iIndex] & _dwKey)
	{
		//0010				0010
		m_dwKeyPressed[iIndex] = m_dwKey;
		return true;
	}
	return false;
}

bool KeyMgr::KeyDown(DWORD _dwKey)
{
	if (KeyPressed(_dwKey))
	{
		//0110			0001
		m_dwKeyDown ^= _dwKey;
	}

	//0111		0001
	if (!(m_dwKeyDown & _dwKey))
	{
		//0001			0001
		if (m_dwKey & _dwKey)
		{
			//0001
			m_dwKeyDown |= _dwKey;
			return true;
		}
	}
	return false;
}

bool KeyMgr::KeyCombinded(DWORD _dwFirstKey, DWORD _dwSecondKey)
{
	if (KeyDown(_dwSecondKey))
	{
		if (m_dwKey & _dwFirstKey)
		{
			return true;
		}
	}
	return false;
}

