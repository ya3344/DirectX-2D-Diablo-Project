#include "stdafx.h"
#include "CollisionMgr.h"


CollisionMgr::CollisionMgr()
{
}


CollisionMgr::~CollisionMgr()
{
}

bool CollisionMgr::CheckRect(const COLLISION_INFO& srcCollision, const COLLISION_INFO& destCollision)
{
	RECT rect;

	if (IntersectRect(&rect, &srcCollision.collisionRect, &destCollision.collisionRect))
	{
		return true;
	}
	else
	{
		return false;
	}

	return true;
}

bool CollisionMgr::CheckRectEX(const INFO& srcInfo, const INFO& destInfo, float & pMoveX, float & pMoveY)
{
	float widthRadius = (srcInfo.mCollisionInfo.collisionWidth * 0.5f) + (destInfo.mCollisionInfo.collisionWidth * 0.5f);
	float heightRadius = (srcInfo.mCollisionInfo.collisionHeight * 0.5f) + (destInfo.mCollisionInfo.collisionHeight * 0.5f);

	float distanceX = abs(destInfo.vPos.x - srcInfo.vPos.x) * 2.5f;
	float distanceY = abs(destInfo.vPos.y - srcInfo.vPos.y) * 2.5f;


	if ((widthRadius >= distanceX ) && (heightRadius >= distanceY))
	{
		//파고든거리를 구한다.
		pMoveX = widthRadius - distanceX;
		pMoveY = heightRadius - distanceY;
		return true;
	}

	return false;
}

void CollisionMgr::SetCollisionRect(INFO& info, const TEXTURE_INFO* pTextureInfo)
{
	float width = 0.f;
	float height = 0.f;
	LONG left = (LONG)(info.matTrans._41 - (info.centerX * info.mCollisionInfo.leftScale));
	LONG top = (LONG)(info.matTrans._42 - (info.centerY * info.mCollisionInfo.topScale));


	if (info.centerX == 0.f)
	{
		width = (float)pTextureInfo->imgInfo.Width;
	}
	else
	{
		width = (float)pTextureInfo->imgInfo.Width * 0.5f;
	}

	if (info.centerY == 0.f)
	{
		height = (float)pTextureInfo->imgInfo.Height;
	}
	else
	{
		height = (float)pTextureInfo->imgInfo.Height * 0.5f;
	}

	LONG right = (LONG)(info.matTrans._41 + (width* info.mCollisionInfo.rightScale));
	LONG bottom = (LONG)(info.matTrans._42 + (height * info.mCollisionInfo.bottomScale));


	info.mCollisionInfo.collisionRect = { left + info.mCollisionInfo.moveX , top + info.mCollisionInfo.moveY, 
		right + info.mCollisionInfo.moveX, bottom + info.mCollisionInfo.moveY };

	info.mCollisionInfo.collisionWidth = (float)(info.mCollisionInfo.collisionRect.right - info.mCollisionInfo.collisionRect.left);
	info.mCollisionInfo.collisionHeight = (float)(info.mCollisionInfo.collisionRect.bottom - info.mCollisionInfo.collisionRect.top);
	
	
}
