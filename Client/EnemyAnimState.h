#pragma once
#include "AnimState.h"
class EnemyAnimState final : public AnimState
{
public:
	EnemyAnimState();
	virtual ~EnemyAnimState();

	// State을(를) 통해 상속됨
	virtual void Initialize(int type, wstring& objKey) override;
	virtual void FrameUpdate(ATTRIBUTE & attribute, FRAME & frame, wstring & stateKey) override;
};

