#include "stdafx.h"
#include "Subject.h"
#include "Observer.h"

Subject::Subject()
{
}


Subject::~Subject()
{
	Release();
}

void Subject::Subscribe(Observer * pObserver)
{
	if (pObserver == nullptr)
		return;

	mObserverSpace.emplace_back(pObserver);
}

void Subject::UnSubscribe(Observer * pObserver)
{
	auto iterBegin = mObserverSpace.begin();
	auto iterEnd = mObserverSpace.end();

	for (;; iterBegin != iterEnd)
	{
		if (*iterBegin == pObserver)
		{
			iterBegin = mObserverSpace.erase(iterBegin);
			return;
		}
		else
		{
			++iterBegin;
		}
	}
}

void Subject::Notify(int message, void * pData)
{
	for (Observer* pObserver : mObserverSpace)
	{
		pObserver->Update(message, pData);
	}
}

void Subject::Release(void)
{
	mObserverSpace.clear();
}
