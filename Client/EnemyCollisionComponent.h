#pragma once
#include "CollisionComponent.h"
class EnemyCollisionComponent final : public CollisionComponent
{
public:
	EnemyCollisionComponent();
	virtual ~EnemyCollisionComponent();

	// CollisionComponent을(를) 통해 상속됨
	virtual void Initialize(Obj * pSrc) override;
	virtual void ObstacleCollision(const list<Obj*>& objSpace) override;
	virtual void MoveCollision(const list<Obj*>& objSpace) override;
	virtual void AttackCollision(const list<Obj*>& objSpace) override;

private:
	void EnemyAttackFrame();

private:
	int mAttackFrame[(size_t)ENEMY_TYPE::ENEMY_END][2] = {};

private:
	enum ATTACK_FRAME
	{
		START,
		END,
	};

};

