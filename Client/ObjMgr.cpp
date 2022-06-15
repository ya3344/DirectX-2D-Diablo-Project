#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "LifeObj.h"
#include "Bridge.h"
#include "UI.h"
IMPLEMENT_SINGLETON(ObjMgr)

ObjMgr::ObjMgr()
{
}


ObjMgr::~ObjMgr()
{
	Release();
}

Obj * ObjMgr::GetEffectObj(const int type)
{
	for (Obj* pObj : mObjSpace[OBJ_EFFECT])
	{
		if (pObj->GetBidge() != nullptr)
		{
			if (pObj->GetBidge()->GetType() == type)
			{
				return pObj;
			}
		}
		else
		{
			return nullptr;
		}
	}

	return nullptr;
}

Obj * ObjMgr::GetUIObj(const int type)
{

	for (Obj* pObj : mObjSpace[OBJ_UI])
	{
		if (dynamic_cast<UI*>(pObj) != nullptr)
		{
			if (dynamic_cast<UI*>(pObj)->GetType() == type)
			{
				return pObj;
			}
		}
	}
	return nullptr;
}

void ObjMgr::AddObject(const OBJ_ID objID, Obj * pObj)
{
	if (pObj == nullptr)
		return;

	mObjSpace[objID].emplace_back(pObj);

}

void ObjMgr::Update()
{
	if (EnemyMgr::GetInstance()->GetEnemyInit() == false || TileMgr::GetInstance()->GetObstacleInit() == false)
		return;

	int objEvent;

	for (int i = 0; i < OBJ_END; ++i)
	{
		auto iterBegin = mObjSpace[i].begin();
		auto iterEnd = mObjSpace[i].end();

		for (; iterBegin != iterEnd;)
		{
			objEvent = (*iterBegin)->Update();
			if (objEvent == OBJ_DIE)
			{
				SafeDelete<Obj*>(*iterBegin);
				iterBegin = mObjSpace[i].erase(iterBegin);
			}
			else if (objEvent == OBJ_NORMAL)
				++iterBegin;
			else if (objEvent == OBJ_SCENECHANGE)
				return;
			else
			{
				MESSAGE_BOX(L"objEvent Error!", L"ObjMgr::Update");
			}
		}
	}
}

void ObjMgr::Render()
{
	if (EnemyMgr::GetInstance()->GetEnemyInit() == false || TileMgr::GetInstance()->GetObstacleInit() == false)
		return;

	for (int i = OBJ_BACK; i <= OBJ_OBSTACLE; ++i)
	{
		for (Obj* pObj : mObjSpace[i])
		{
			mObjSortSpace.emplace_back(pObj);
		}
	}

	// Y좌표 기준으로 오름차순으로 정렬
	mObjSortSpace.sort(
		[](Obj* pObj1, Obj* pObj2) -> bool
	{
		return pObj1->GetInfo().vPos.y > pObj2->GetInfo().vPos.y;
	}
	);

	// 정렬순서대로 렌더링
	for (Obj* pObj : mObjSortSpace)
	{
		pObj->Render();
	}
	mObjSortSpace.clear();

	
	// Effect, UI Render
	for (int i = OBJ_EFFECT; i <= OBJ_MOUSE; ++i)
	{
		for (Obj* pObj : mObjSpace[i])
		{
			pObj->Render();
		}
	}
}

void ObjMgr::Collision()
{
	if (EnemyMgr::GetInstance()->GetEnemyInit() == false || TileMgr::GetInstance()->GetObstacleInit() == false)
		return;

	for (Obj* pObj : mObjSpace[OBJ_PLAYER])
	{
		dynamic_cast<LifeObj*>(pObj)->Collision();
	}

	for (Obj* pObj : mObjSpace[OBJ_ENEMY])
	{
		dynamic_cast<LifeObj*>(pObj)->Collision();
	}

	//for (Obj* pObj : mObjSpace[OBJ_UI])
	//{
	//	dynamic_cast<UI*>(pObj)->Collision();
	//}
}

void ObjMgr::Release()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for_each(mObjSpace[i].begin(), mObjSpace[i].end(), SafeDelete<Obj*>);
		mObjSpace[i].clear();
	}

	//for_each(mObjSortSpace.begin(), mObjSortSpace.end(), SafeDelete<Obj*>);
	//mObjSortSpace.clear();
}


void ObjMgr::DeleteObj(int objID)
{
	for (Obj* pObj : mObjSpace[objID])
	{
		SafeDelete<Obj*>(pObj);
	}

	mObjSpace[objID].clear();
}

void ObjMgr::DeleteSelectObj(Obj * pObj, int objID)
{
	auto iterBegin = mObjSpace[objID].begin();
	auto iterEnd = mObjSpace[objID].end();

	for (; iterBegin != iterEnd;)
	{
		if (*iterBegin == pObj)
		{
			SafeDelete<Obj*>(*iterBegin);
			iterBegin = mObjSpace[objID].erase(iterBegin);
		}
		else
		{
			++iterBegin;
		}
	}
}

