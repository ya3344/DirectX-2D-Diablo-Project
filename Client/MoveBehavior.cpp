#include "stdafx.h"
#include "MoveBehavior.h"
#include "AStar.h"

MoveBehavior::MoveBehavior()
{
	mMoveTime = GetTickCount();
	//mSkillTime = GetTickCount();
	m_vRandomPos = { 0.f, 0.f, 0.f };
}


MoveBehavior::~MoveBehavior()
{
}

bool MoveBehavior::RandomMove(const INFO & srcInfo, AStar * pAStar)
{
	if (mMoveTime + mRandomTime < GetTickCount())
	{
		mRandomTime = (rand() % 500) + 1000;
		mMoveTime = GetTickCount();

		m_vRandomPos = MathMgr::GetInstance()->RandomPos(srcInfo.vPos);
		
		if (pAStar->AStarStartPos(srcInfo.vPos, m_vRandomPos))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	return false;
}

bool MoveBehavior::SkillOperation(float time, int enemyType)
{
	if (enemyType == FALLEN || enemyType == COUNTESS || enemyType == WRAITH || enemyType == ANIMAL)
	{
		return false;
	}

	switch (enemyType)
	{
	case COUNCIL:
		time = rand() % 3 + 1.5f;
		break;
	case DEMON:
		time = rand() % 3 + 1.2f;
		break;
	case DIABLO:
		time = rand() % 3 + 1.2f;
		break;
	default:
		break;
	}

	if (mSkillTime < time)
	{
		mSkillTime += TimeMgr::GetInstance()->GetTime();
		//cout << mSkillTime << endl;
	}
	else
	{
		mSkillTime = 0.f;
		return true;
	}
	return false;
}
