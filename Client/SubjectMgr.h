#pragma once
#include "Subject.h"
class SubjectMgr final : public Subject
{
	DECLARE_SINGLETON(SubjectMgr);

private:
	SubjectMgr();
	virtual ~SubjectMgr();

public:
	const list<void*>* GetDataList(int message) const;

public:
	void AddData(int message, void* pData);
	void RemoveData(int message, void* pData);
	void Release();

private:
	map<int, list<void*>> mDataSpace;

};

