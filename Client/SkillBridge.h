#pragma once

#include "Bridge.h"

class SkillBridge : public Bridge
{
public:
	SkillBridge();
	virtual ~SkillBridge();

public:
	// Bridge을(를) 통해 상속됨
	virtual HRESULT Initialize(int type, int enemyType) override;
	virtual int Update() override;
	virtual void Render(void) override;
	virtual void Collision(void) override;
	virtual bool Skill() override;
	virtual void SetInfo(const int type, const TCHAR* pStateKey, FRAME frame, float durationTime = 0.f, float attack = 0.f) override;
	virtual void Release(void) override;

protected:
	LPDIRECT3DDEVICE9 m_pDevice = nullptr;
	LPD3DXSPRITE m_pSprite = nullptr;
	const TEXTURE_INFO*	m_pTextureInfo = nullptr;

protected:
	bool m_bOperation = false;
	bool m_bForever = false;

};

