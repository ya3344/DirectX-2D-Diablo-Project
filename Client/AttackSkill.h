#pragma once
#include "SkillBridge.h"

class AttackSkill final : public SkillBridge
{
public:
	AttackSkill();
	virtual ~AttackSkill();

public:
	virtual HRESULT Initialize(int type, int enemyType) override;
	virtual int Update() override;
	virtual void Render(void) override;
	virtual void Collision(void) override;
	virtual bool Skill() override;
	virtual void SetInfo(const int type, const TCHAR* pStateKey, FRAME frame, float durationTime = 0.f, float attack = 0.f) override;

private:
	void SetAttribute(bool bForever, int skillCount, float attack, int attackPercent);
private:
	void Roll();
	void Meteor();
	void MeteorReady();

	void Twister(FRAME midFrame, FRAME endFrame);
	void Rock();
	void Volcano(FRAME midFrame, FRAME endFrame);
	void GroundFire(FRAME midFrame, FRAME endFrame);
	void StaticField();
	void DiabloFire(FRAME midFrame);
	void DirAttack(float& initFrame, int count, int& maxFrame, float distance, int dirNum);
	void DiaInferno();
public:
	virtual void Release(void) override;


private:
	Obj* m_pPlayer = nullptr;
	D3DXVECTOR3 m_vTargetPos;
	D3DXVECTOR3 m_vTargetDir;
	D3DXVECTOR3 m_vRandomPos;
	float mTargetDistance = 0.f;
	float mPreTargetDistance = 0.f;

private:
	int mSkillCount = 0;
	int mMaxSkillCount = 0;
	int mAttackPercent = 0;
	int mAttackStaticPercent = 0;
	float mPreFrameInit = -1.f;
	float attack = 0;

// Twister
private:
	float mScale = 1.f;

private:
	float mTime = 0.f;
	float mTwisterTime = 0.f;
	float mTwisterPreTime = 0.f;
	int mRandDistance = 0;

private:
	float mInitFrame = 0.f;
	int mMaxFrame = 0;
	bool m_bFireBall = false;

private:
	enum FRAME_COUNT
	{
		FIRE_BALL_FRAME =5,
		DIA_INFERNO_FRAME = 15,
	};

};

