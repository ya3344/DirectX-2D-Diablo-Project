#include "stdafx.h"
#include "Obj.h"
#include "BuffSkill.h"
#include "SkillUI.h"

Obj::Obj()
{
	m_pSprite = Device::GetInstance()->GetSprite();
	m_pDevice = Device::GetInstance()->GetDevice();
}


Obj::~Obj()
{
}

void Obj::SetHP(const float HP)
{
	mAttribute.currentHP += HP;

	if (mAttribute.currentHP > mAttribute.maxHP)
		mAttribute.currentHP = mAttribute.maxHP;

	if (mAttribute.currentHP <= 0)
	{
		mAttribute.currentHP = 0;
	}

	SubjectMgr::GetInstance()->Notify(PLAYER_DATA, &mAttribute);
}

void Obj::SetMP(const float MP)
{
	mAttribute.currentMP += MP;

	if (mAttribute.currentMP > mAttribute.maxMP)
		mAttribute.currentMP = mAttribute.maxMP;

	if (mAttribute.currentMP <= 0)
	{
		mAttribute.currentMP = 0;
	}

	SubjectMgr::GetInstance()->Notify(PLAYER_DATA, &mAttribute);
}

void Obj::SetSP(const float SP)
{
	mAttribute.currentSP += SP;

	if (mAttribute.currentSP > mAttribute.maxSP)
		mAttribute.currentSP = mAttribute.maxSP;

	if (mAttribute.currentSP <= 0)
	{
		mAttribute.currentSP = 0;
	}

	SubjectMgr::GetInstance()->Notify(PLAYER_DATA, &mAttribute);
}

void Obj::SetStr(const int str)
{
	mAttribute.str += str;
	mAttribute.maxSP = mAttribute.str * 42.f;
	mAttribute.attack = (float)mAttribute.str;

	SubjectMgr::GetInstance()->Notify(PLAYER_DATA, &mAttribute);
}

void Obj::SetDex(const int dex)
{
	mAttribute.dex += dex;

	SubjectMgr::GetInstance()->Notify(PLAYER_DATA, &mAttribute);
}

void Obj::SetLife(const int life)
{
	mAttribute.life += life;
	mAttribute.maxHP = mAttribute.life * 53.f;

	SubjectMgr::GetInstance()->Notify(PLAYER_DATA, &mAttribute);
}

void Obj::SetEnergy(const int energy)
{
	mAttribute.energy += energy;
	mAttribute.maxMP = mAttribute.energy * 54.f;

	SubjectMgr::GetInstance()->Notify(PLAYER_DATA, &mAttribute);
}

void Obj::SetEXP(const float exp)
{
	if (mAttribute.Level >= 99)
		return;

	mAttribute.currentEXP += exp;

	if (mAttribute.currentEXP >= mAttribute.nextEXP)
	{
		mAttribute.currentEXP = mAttribute.nextEXP;
		++mAttribute.Level;
		mAttribute.statPoint += 6;
		mAttribute.skillPoint += 3;
		mAttribute.nextEXP = mAttribute.currentEXP * 1.14f;

		Obj* pObj = ObjFactory<BuffSkill>::CreateEffect(TRANSFORM, mInfo.vPos, nullptr, 0, D3DCOLOR_ARGB(255, 0, 255, 255));
		ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pObj);
	}

	SubjectMgr::GetInstance()->Notify(PLAYER_DATA, &mAttribute);
}

void Obj::SetStatPoint(const int statPoint)
{
	mAttribute.statPoint += statPoint;

	if (mAttribute.statPoint <= 0)
		mAttribute.statPoint = 0;
}

void Obj::SetSkillPoint(const int skillPoint)
{
	mAttribute.skillPoint += skillPoint;

	if (mAttribute.skillPoint <= 0)
		mAttribute.skillPoint = 0;
}

void Obj::SetPlayerDamage(const float attack)
{
	mAttribute.currentHP -= attack;
	mAttribute.mode = MODE::GETHIT;
	
	if (mAttribute.currentHP <= 0)
	{
		mAttribute.currentHP = 0;
	}
	
	SubjectMgr::GetInstance()->Notify(PLAYER_DATA, &mAttribute);
}

void Obj::SetEnemyDamage(const float attack)
{
	mAttribute.currentHP -= attack;

	if(mAttribute.type != DIABLO)
		mAttribute.mode = MODE::GETHIT;

	if (mAttribute.currentHP <= 0)
	{
		mAttribute.currentHP = 0;

		switch (mAttribute.type)
		{
		case FALLEN:
			m_pObj->SetEXP(500);
			break;
		case COUNTESS:
			m_pObj->SetEXP(1500);
			break;
		case COUNCIL:
			m_pObj->SetEXP(1500);
			break;
		case FALLEN_SHAMON:
			m_pObj->SetEXP(2000);
			m_pObj->SetShamenDisCount();
			cout << "Shamon" << m_pObj->GetAttribute().FallenShamanCount << endl;
			break;
		case DIABLO:
			m_pObj->SetEXP(50000);
			m_pObj->SetDiaDisCount();
			cout << "Diablo" << m_pObj->GetAttribute().DiabloCount << endl;
			break;
		case DEMON:
			m_pObj->SetEXP(4000);
			break;
		case WRAITH:
			m_pObj->SetEXP(3000);
			break;
		case ANIMAL:
			m_pObj->SetEXP(500);
			break;
		default:
			break;
		}
	}
}

