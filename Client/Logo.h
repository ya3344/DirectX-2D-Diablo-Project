#pragma once
#include "Scene.h"

class Logo final : public Scene
{
public:
	Logo();
	~Logo();

	// Scene을(를) 통해 상속됨
	virtual HRESULT Initialize(const D3DXVECTOR3& vPos = { 0.f, 0.f, 0.f }) override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void KeyCheck();
	void MapRender();

private:
	const TEXTURE_INFO* m_pTextureInfo = nullptr;
	RECT mCollisionRect = {};
private:
	INFO mInfo;
	FRAME mFrame;

};

