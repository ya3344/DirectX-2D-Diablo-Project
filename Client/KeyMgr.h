#pragma once

class KeyMgr
{
public:
	DECLARE_SINGLETON(KeyMgr)

private:
	KeyMgr(void);
	~KeyMgr(void);

public:
	void KeyCheck(void);
	bool KeyPressed(DWORD _dwKey, int iIndex = 0);
	bool KeyDown(DWORD _dwKey);
	bool KeyCombinded(DWORD _dwFirstKey, DWORD _dwSecondKey);

private:
	DWORD		m_dwKey = 0;
	DWORD		m_dwKeyPressed[3] = {};
	DWORD		m_dwKeyDown = 0;
};
