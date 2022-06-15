#include "stdafx.h"
#include "PlayerObserver.h"


PlayerObserver::PlayerObserver()
{
}


PlayerObserver::~PlayerObserver()
{
}

void PlayerObserver::Update(int message, void * pData)
{
	const list<void*>* pDataList = SubjectMgr::GetInstance()->GetDataList(message);

	auto iterFind = find(pDataList->begin(), pDataList->end(), pData);

	if (pData == nullptr)
		iterFind = pDataList->begin();

	switch (message)
	{
	case PLAYER_DATA:
		mAttribute = *((ATTRIBUTE*)(*iterFind));
		break;
	}
}
