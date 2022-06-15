#include "stdafx.h"
#include "EnemyMoveComponent.h"
#include "AStar.h"
#include "Tile.h"

EnemyMoveComponent::EnemyMoveComponent()
{
}


EnemyMoveComponent::~EnemyMoveComponent()
{
}

bool EnemyMoveComponent::Update(AStar * pAStar, ATTRIBUTE & attribute, INFO & info)
{
	if (pAStar->GetBesRoadSpace().empty())
	{
		return false;
	}

	m_pAStarNode = pAStar->GetBesRoadSpace().top();

	m_pTile = TileMgr::GetInstance()->GetTile(m_pAStarNode->index);
	m_vTargetDir = MathMgr::GetInstance()->CalTargetDir(info.vPos, m_pTile->GetTileInfo().vPos);

	attribute.vDistance = m_vTargetDir * attribute.speed * TimeMgr::GetInstance()->GetTime();
	info.vPos += attribute.vDistance;

	// 바라보는 방향 계산
	attribute.degree = MathMgr::GetInstance()->CalDirDegree(info.vPos, m_pTile->GetTileInfo().vPos);

	//cout << "Degree: " << attribute.degree << endl;
	float distance = MathMgr::GetInstance()->CalDistance(info.vPos, m_pTile->GetTileInfo().vPos);

	// 자기위치의 타일인덱스 계산
	attribute.tileIndex = TileMgr::GetInstance()->Picking(info.vPos);

	//if (mPreTileIndex != attribute.tileIndex)
	//{
	//	mPreTileIndex = attribute.tileIndex;
	//	mCount = 0;
	//}
	//else
	//{
	//	++mCount;
	//}
	//
	//if (mCount == 3)
	//{
	//	pAStar->Release();
	//	return false;
	//}

	if (attribute.type == COUNTESS)
	{
		if (pAStar->GetBesRoadSpace().size() < 2)
		{
			//info.vPos += attribute.vDistance * 1.5f;
		}
	}

	// 자기위치의 타일못가는 지역으로 변경
	/*if(attribute.tileIndex != -1 && (size_t)attribute.tileIndex < TileMgr::GetInstance()->GetTileSpace().size())
		if (TileMgr::GetInstance()->GetTile(attribute.tileIndex + 1)->GetOption() == TILE_BLOCK)
		{
			info.vPos += attribute.vDistance * 2;
		}*/

	if (distance <= 5.f)
	{
		pAStar->GetBesRoadSpace().pop();
		attribute.bSceneInit = false;
	}

	return true;
}

void EnemyMoveComponent::FrameCal(ATTRIBUTE & attribute, const FRAME & frame)
{
	if (frame.dirNum[(size_t)attribute.mode] == 0)
		return;

	if (frame.dirNum[(size_t)attribute.mode] == 1)
	{
		attribute.frameDir = 0;
		return;
	}

	// 반대방향으로 돌린다.
	attribute.frameDir = (int)roundf((frame.dirNum[(size_t)attribute.mode] - ((attribute.degree) / (360.f / frame.dirNum[(size_t)attribute.mode]))));


	// 오른쪽기준을 아래쪽기준으로 바꾼다.
	if (frame.dirNum[(size_t)attribute.mode] == 16)
		attribute.frameDir += 12;
	else
		attribute.frameDir += 6;

	attribute.frameDir %= frame.dirNum[(size_t)attribute.mode];
}
