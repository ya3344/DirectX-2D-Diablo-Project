#pragma once
#include "LifeObj.h"

typedef struct tagSkillSlot
{
	explicit tagSkillSlot(const TCHAR* pkeyName, D3DXVECTOR3 vPos, int drawID)
	{
		lstrcpy(keyBuf, pkeyName);
		this->vPos = vPos;
		this->drawID = drawID;
	}
	tagSkillSlot()
	{
		vPos = { 0.f, 0.f, 0.f };
		drawID = 0;
	}

	TCHAR keyBuf[5] = L"";
	D3DXVECTOR3 vPos = { 0.f, 0.f, 0.f };
	int drawID = 0;

}SKILL_SLOT;

class Player final : public LifeObj
{
public:
	Player();
	virtual ~Player();

	// Obj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update(void) override;
	virtual void Render(void) override;
	virtual void Collision(void) override;

public:
	const vector<SKILL_SLOT*>& GetSkillSlotSpace() const { return mSkillSlotSpace; }

public:
	void AddSkillSlot(const TCHAR * pKeyName, D3DXVECTOR3 vPos, int drawID);

private:
	void KeyCheck();
	void ChangeMode();
	int StageChange();
	void SetInfo(int type, MODE mode, int str, int dex, int life, int energy);
	void TransInfo(int type, MODE mode);
	void SkillOperation();
	bool PortalCollision();
	bool RedPortalCollision();

public:
	void SetSkillChoice(const int skillChoice) { mSkillChoice = skillChoice; }

public:
	virtual void Release(void) override;

private:
	int mSkillChoice = 0;
	vector<SKILL_SLOT*> mSkillSlotSpace;

private:
	enum SKILL_TYPE
	{
		BOULDER_ROLL_TYPE =2,
		TOWNPORTAL_TYPE = 61,
		REVIVE_TYPE = 40,
		VOLCAINO_TYPE = 12,
		TWISTER_TYPE = 14,
		METEOR_TYPE = 6,
		LIGHTING_TYPE = 20,
		DIABLOFIRE_TYPE = 26,
	};

	
};

