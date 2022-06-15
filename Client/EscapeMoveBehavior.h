#pragma once

#include "MoveBehavior.h"

class EscapeMoveBehavior : public MoveBehavior
{
public:
	EscapeMoveBehavior();
	virtual ~EscapeMoveBehavior();

public:
	virtual void Initialize(AStar * pAStar, int enemyType) override;
	virtual int Move(Obj* srcObj, Obj* destObj) override;

private:
	void SkillSelect(int enemyType);

private:
	D3DXVECTOR3 m_vTargetPos;
	D3DXVECTOR3 m_vTargetDir;

private:
	static constexpr int ENEMY_TYPE = 100;
};

