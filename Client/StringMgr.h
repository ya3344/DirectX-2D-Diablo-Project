#pragma once
class StringMgr
{
public:
	StringMgr();
	~StringMgr();

public:
	static wstring Replace(wstring imageKey, const TCHAR* pSrcKey, const TCHAR* pReplaceKey);
	static wstring DirAppend(wstring stateKey, DIRECTION dir);
	//static wstring DirAppend(wstring stateKey, DIRECTION dir);
};

