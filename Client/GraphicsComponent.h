#pragma once

class AStar;

class GraphicsComponent abstract
{
public:
	GraphicsComponent();
	virtual ~GraphicsComponent();

public:
	virtual void Update(FRAME& frame, INFO& info) PURE;
	virtual void Render(const wstring& objKey, const wstring& stateKey, const LPD3DXSPRITE pSprite, const FRAME& frame, INFO& info) PURE;
};

