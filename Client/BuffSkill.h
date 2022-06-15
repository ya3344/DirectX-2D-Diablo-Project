#pragma once
#include "SkillBridge.h"

class BuffSkill final : public SkillBridge
{
public:
	BuffSkill();
	virtual ~BuffSkill();

public:
	virtual HRESULT Initialize(int type, int enemyType) override;
	virtual int Update() override;
	virtual void Render(void) override;
	virtual bool Skill() override;
	virtual void SetInfo(const int type, const TCHAR* pStateKey, FRAME frame, float durationTime = 0.f, float attack = 0.f) override;

private:
	bool Summon(int objType);
	bool Portal();
	bool RedPortal();
	void PortalCollision();
	void RedPortalCollision();
	bool SkillOperation(const float time);

public:
	virtual void Release(void) override;
	
private:
	D3DXVECTOR3 m_vRandomPos;
	Tile* m_pTile = nullptr;

	bool m_bSummonInit = false;
	bool m_bPortalInit = false;
	float mSkillTime = false;

};

