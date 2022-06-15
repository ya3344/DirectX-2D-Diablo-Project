#pragma once
#include "MoveComponent.h"

class EnemyMoveComponent final : public MoveComponent
{
public:
	EnemyMoveComponent();
	virtual ~EnemyMoveComponent();

	// MoveComponent��(��) ���� ��ӵ�
	virtual bool Update(AStar * pAStar, ATTRIBUTE & attribute, INFO & info) override;
	virtual void FrameCal(ATTRIBUTE & attribute, const FRAME & frame) override;

private:
	int mPreTileIndex = -20;
	int mCount = 0;
};

