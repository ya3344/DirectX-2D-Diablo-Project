#pragma once

#include "MoveBehavior.h"

class ChaseMoveBehavior : public MoveBehavior
{
public:
	ChaseMoveBehavior();
	virtual ~ChaseMoveBehavior();

public:
	virtual void Initialize(AStar * pAStar, int enemyType) override;
	virtual int Move(Obj* pSrcObj, Obj* pDestObj) override;

private:
	D3DXVECTOR3 m_vTargetDir;
	int DiabloCast();
};

