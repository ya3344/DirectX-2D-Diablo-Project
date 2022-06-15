#pragma once
#include "Scene.h"

class Village final : public Scene
{
public:
	Village();
	~Village();

	// Scene을(를) 통해 상속됨
	virtual HRESULT Initialize(const D3DXVECTOR3& vPos = { 0.f, 0.f, 0.f }) override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void NPCRender(); 

public:
	static unsigned int _stdcall ThreadFunc(void* pArg);

public:
	void SkillUI_Init();

private:
	FRAME mNPCFrame = {};


};

