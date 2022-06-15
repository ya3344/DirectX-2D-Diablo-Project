#include "stdafx.h"
#include "SkillBridge.h"
#include "Obj.h"

SkillBridge::SkillBridge()
{
	m_pDevice = Device::GetInstance()->GetDevice();
	m_pSprite = Device::GetInstance()->GetSprite();
}


SkillBridge::~SkillBridge()
{
}

HRESULT SkillBridge::Initialize(int type, int enemyType)
{
	return E_NOTIMPL;
}

int SkillBridge::Update()
{
	return 0;
}

void SkillBridge::Render(void)
{

}

void SkillBridge::Collision(void)
{
}

bool SkillBridge::Skill()
{
	return true;
}

void SkillBridge::SetInfo(const int type, const TCHAR * pStateKey, FRAME frame, float durationTime, float attack)
{
	mType = type;
	mStateKey = pStateKey;
	mFrame = frame;
	mDurationTime = durationTime;
	mAttack = attack;
}

void SkillBridge::Release(void)
{
}
