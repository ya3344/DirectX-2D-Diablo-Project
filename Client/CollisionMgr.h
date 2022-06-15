#pragma once
class CollisionMgr
{
public:
	CollisionMgr();
	~CollisionMgr();

public:
	static bool CheckRect(const COLLISION_INFO& srcCollision, const COLLISION_INFO& destCollision);
	static bool CheckRectEX(const INFO& srcInfo, const INFO& destInfo, float& pMoveX, float& pMoveY);

public:
	static void SetCollisionRect(INFO& info, const TEXTURE_INFO* pTextureInfo);
};

