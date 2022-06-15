#include "stdafx.h"
#include "EscapeMoveBehavior.h"
#include "AStar.h"
#include "BuffSkill.h"

EscapeMoveBehavior::EscapeMoveBehavior()
{
	m_vTargetPos = { 0.f, 0.f, 0.f };
	m_vTargetDir = { 0.f, 0.f, 0.f };
}


EscapeMoveBehavior::~EscapeMoveBehavior()
{
}

void EscapeMoveBehavior::Initialize(AStar * pAStar, int enemyType)
{
	m_pAStar = pAStar;
	mEnemyType = enemyType;
}

int EscapeMoveBehavior::Move(Obj* srcObj, Obj* destObj)
{
	float distance = MathMgr::GetInstance()->CalDistance(srcObj->GetInfo().vPos, destObj->GetInfo().vPos);

	if (distance <= 300)
	{
		m_vTargetDir = MathMgr::GetInstance()->CalTargetDir(srcObj->GetInfo().vPos, destObj->GetInfo().vPos);
		m_vTargetDir *= -1;

		m_vTargetPos = srcObj->GetInfo().vPos;
		m_vTargetPos += m_vTargetDir * TILE_WIDTH;

		if (MoveBehavior::SkillOperation(1.7f, mEnemyType))
		{
			return OBJ_SPECIAL;
		}
		else if (m_pAStar->AStarStartPos(srcObj->GetInfo().vPos, m_vTargetPos))
		{
			//cout << "TARGET MOVE" << endl;
			return OBJ_MOVE;
		}
		else
		{
			if (MoveBehavior::RandomMove(srcObj->GetInfo(), m_pAStar))
			{
				//cout << "RANDOM MOVE" << endl;
				return OBJ_MOVE;
			}
		}
	}
	else
	{
		if (MoveBehavior::RandomMove(srcObj->GetInfo(), m_pAStar))
		{
			return OBJ_MOVE;
		}
	}

	return OBJ_NEUTRAL;
}

void EscapeMoveBehavior::SkillSelect(int enemyType)
{
	switch (enemyType)
	{
	case FALLEN_SHAMON:
		Obj* pObj = ObjFactory<BuffSkill>::CreateEffect(REVIVE, MathMgr::GetInstance()->CalPoint(), nullptr, FALLEN);
		ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pObj);
		break;
	}
}
