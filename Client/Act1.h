#pragma once

#include "Scene.h"
class Act1 final : public Scene
{
public:
	Act1();
	virtual ~Act1();

	// Scene��(��) ���� ��ӵ�
	virtual HRESULT Initialize(const D3DXVECTOR3& vPos = { 0.f, 0.f, 0.f }) override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	static unsigned int _stdcall ThreadFunc(void* pArg);
};

