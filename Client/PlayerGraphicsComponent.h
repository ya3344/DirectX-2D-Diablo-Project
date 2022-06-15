#pragma once
#include "GraphicsComponent.h"

class PlayerGraphicsComponent final : public GraphicsComponent
{
public:
	PlayerGraphicsComponent();
	virtual ~PlayerGraphicsComponent();

	// GraphicsComponent��(��) ���� ��ӵ�
	virtual void Update(FRAME& frame, INFO& info) override;
	virtual void Render(const wstring& objKey, const wstring& stateKey, const LPD3DXSPRITE pSprite, const FRAME& frame, INFO& info) override;


};

