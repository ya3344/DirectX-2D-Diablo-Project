#include "stdafx.h"
#include "SubjectMgr.h"

IMPLEMENT_SINGLETON(SubjectMgr);

SubjectMgr::SubjectMgr()
{
}


SubjectMgr::~SubjectMgr()
{
}

const list<void*>* SubjectMgr::GetDataList(int message) const
{
	auto iterFind = mDataSpace.find(message);

	if (iterFind == mDataSpace.end())
		return nullptr;

	return &iterFind->second;
}

void SubjectMgr::AddData(int message, void * pData)
{
	if (pData != nullptr)
	{
		auto iterFind = mDataSpace.find(message);

		if (iterFind == mDataSpace.end())
		{
			mDataSpace[message] = list<void*>();
		}
		mDataSpace[message].emplace_back(pData);
	}
}

void SubjectMgr::RemoveData(int message, void * pData)
{
	auto mapIter = mDataSpace.find(message);

	if (mapIter != mDataSpace.end())
	{
		auto iterListBegin = mapIter->second.begin();
		auto iterListEnd = mapIter->second.end();

		for (;; iterListBegin != iterListEnd)
		{
			if (*iterListBegin == pData)
			{
				iterListBegin = mapIter->second.erase(iterListBegin);
				return;
			}
			else
			{
				++iterListBegin;
			}
		}
	}
}

void SubjectMgr::Release()
{
	for (pair<int, list<void*>> mapPair : mDataSpace)
	{
		mapPair.second.clear();
	}

	mDataSpace.clear();
}
