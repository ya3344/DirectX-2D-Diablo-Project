#include "stdafx.h"
#include "CollisionComponent.h"


CollisionComponent::CollisionComponent()
{
}


CollisionComponent::~CollisionComponent()
{
}

void CollisionComponent::ObstacleCollision_Common(Obj* pSrc, const list<Obj*>& objSpace)
{
	for (Obj* pObj : objSpace)
	{
		if (CollisionMgr::CheckRect(pSrc->GetInfo().mCollisionInfo, pObj->GetInfo().mCollisionInfo))
		{
			pObj->SetAlpha(100);
			pObj->SetObj(pSrc);
		}
		else
		{
			if (pObj->GetObj() == pSrc && pObj->GetAlpha() != 255)
			{
				pObj->SetAlpha(255);
				pObj->SetObj(nullptr);
			}
		}
	}
}
