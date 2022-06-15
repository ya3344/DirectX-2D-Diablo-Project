#pragma once

#include "Scene.h"
class Act4 final : public Scene
{
public:
	Act4();
	virtual ~Act4();

	// Scene을(를) 통해 상속됨
	virtual HRESULT Initialize(const D3DXVECTOR3 & vPos = { 0.f,0.f,0.f }) override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	static unsigned int _stdcall ThreadFunc(void* pArg);
};

