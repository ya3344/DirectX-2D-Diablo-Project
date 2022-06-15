#pragma once
#include "GraphicsComponent.h"

class EnemyGraphicsComponent final : public GraphicsComponent
{
public:
	EnemyGraphicsComponent();
	virtual ~EnemyGraphicsComponent();

	// GraphicsComponent을(를) 통해 상속됨
	virtual void Update(FRAME & frame, INFO & info) override;
	virtual void Render(const wstring & objKey, const wstring & stateKey, const LPD3DXSPRITE pSprite, const FRAME & frame, INFO & info) override;

};

