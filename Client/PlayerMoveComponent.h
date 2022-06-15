#pragma once
#include "MoveComponent.h"

class PlayerMoveComponent final : public MoveComponent
{
public:
	PlayerMoveComponent();
	virtual ~PlayerMoveComponent();

	// MoveComponent��(��) ���� ��ӵ�
	virtual bool Update(AStar* pAStar, ATTRIBUTE& attribute, INFO& info) override;
	virtual void FrameCal(ATTRIBUTE& attribute, const FRAME& frame) override;

};

