#pragma once
#include "AnimState.h"
class PlayerAnimState final : public AnimState
{
public:
	PlayerAnimState();
	virtual ~PlayerAnimState();

	// State��(��) ���� ��ӵ�
	virtual void Initialize(int type, wstring& objKey) override;
	virtual void FrameUpdate(ATTRIBUTE& attribute, FRAME& frame, wstring& stateKey) override;

};

