#include "stdafx.h"
#include "ChaseMoveBehavior.h"
#include "AStar.h"
#include "AttackSkill.h"

ChaseMoveBehavior::ChaseMoveBehavior()
{
	m_vTargetDir = D3DXVECTOR3(0.f, 0.f, 0.f);
}


ChaseMoveBehavior::~ChaseMoveBehavior()
{
}

void ChaseMoveBehavior::Initialize(AStar * pAStar, int enemyType)
{
	m_pAStar = pAStar;
	mEnemyType = enemyType;
}

int ChaseMoveBehavior::Move(Obj* pSrcObj, Obj* pDestObj)
{
	float distance = MathMgr::GetInstance()->CalDistance(pSrcObj->GetInfo().vPos, pDestObj->GetInfo().vPos);

	float skillrand = rand() % 3 + 1.5f;

	bool bSkill = MoveBehavior::SkillOperation(skillrand, mEnemyType);
	int range = 300;
	
	static bool bInit = false;



	if (pSrcObj->GetAttribute().type == DIABLO)
	{
		range = 500;
	}

	if (pSrcObj->GetAttribute().mode == MODE::SPECIAL_CAST)
	{
		return OBJ_SPECIAL;
	}
	else if (pSrcObj->GetAttribute().mode == MODE::SPECIAL)
	{
		return OBJ_BOSS_SUMMON_CAST;
	}
	else if (pSrcObj->GetAttribute().mode == MODE::FIRE_CAST)
	{
		return OBJ_FIRE_CAST;
	}
	else if (distance <= range)
	{
		if (pSrcObj->GetAttribute().bCollision && m_pAStar->GetBesRoadSpace().size() < 2)
		{
			return OBJ_ATTACK;
		}
		else if (bSkill)
		{
			if (pSrcObj->GetAttribute().type != DIABLO)
			{
				return OBJ_SPECIAL;
			}
			else
			{
				if (distance <= 250)
				{
					if (bInit == false)
					{
						/*SoundMgr::GetInstance()->StopAll();
						SoundMgr::GetInstance()->PlayBGM(L"DiabloLair.wav", CHANNAL::BGM);*/
						SoundMgr::GetInstance()->PlaySound(L"diablotaunt.wav", BUTTON_SOUND);
						bInit = true;
					}
				}

				return DiabloCast();
			}
			
		}
		else if (pSrcObj->GetAttribute().bEXCollision && distance < 80)
		{
			return OBJ_ATTACK;
		}
		else if (m_pAStar->AStarStartPos(pSrcObj->GetInfo().vPos, pDestObj->GetInfo().vPos))
		{
			return OBJ_MOVE;
		}
		else
		{
			return OBJ_MOVE;
		}
	}
	else
	{
		if (MoveBehavior::RandomMove(pSrcObj->GetInfo(), m_pAStar))
		{
			return OBJ_MOVE;
		}	
	}

	return OBJ_NEUTRAL;
}

int ChaseMoveBehavior::DiabloCast()
{
	int select = rand() % 10000 + 1;
	int objChoice = 0;


	if (select >= 1 && select <= 4000)
	{
		objChoice = OBJ_FIRE_CAST;
	}
	else if (select >= 4001 && select <= 8000)
	{
		objChoice = OBJ_BOSS_SUMMON_CAST;
	}
	else
	{
		objChoice = OBJ_SPECIAL;
	}


	return objChoice;
}
