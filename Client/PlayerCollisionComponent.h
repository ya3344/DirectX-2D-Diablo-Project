#pragma once
#include "CollisionComponent.h"

class PlayerCollisionComponent final : public CollisionComponent
{
public:
	PlayerCollisionComponent();
	virtual ~PlayerCollisionComponent();

public:
	virtual void Initialize(Obj* pSrc) override;

public:
	virtual void ObstacleCollision(const list<Obj*>& objSpace) override;
	virtual void MoveCollision(const list<Obj*>& objSpace) override;
	virtual void AttackCollision(const list<Obj*>& objSpace) override;

private:
	void PlayAttackFrame();

private:
	int mAttackFrame[(size_t)PLAYER_TYPE::PLAYER_END][2] = {};

private:
	enum ATTACK_FRAME
	{
		START,
		END,
	};
};

