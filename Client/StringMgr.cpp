#include "stdafx.h"
#include "StringMgr.h"


StringMgr::StringMgr()
{
}


StringMgr::~StringMgr()
{
}

wstring StringMgr::Replace(wstring imageKey, const TCHAR* pSrcKey, const TCHAR* pReplaceKey)
{
	wstring::size_type pos = 0;

	pos = imageKey.find(pSrcKey);

	if (pos != wstring::npos)
	{
		imageKey.replace(imageKey.begin() + pos, imageKey.begin() + pos + lstrlen(pSrcKey), pReplaceKey);
	}

	return imageKey;
}

wstring StringMgr::DirAppend(wstring stateKey, DIRECTION dir)
{
	//wstring::size_type pos = 0;
	TCHAR dirBuf[2];
	_itow_s((size_t)dir, dirBuf, 10);

	stateKey.replace(stateKey.size()-1, stateKey.size(), dirBuf);
	

	return stateKey;
}
