#include "stdafx.h"
#include "PlayerMoveComponent.h"
#include "AStar.h"
#include "Tile.h"

PlayerMoveComponent::PlayerMoveComponent()
{
}


PlayerMoveComponent::~PlayerMoveComponent()
{
}

bool PlayerMoveComponent::Update(AStar* pAStar, ATTRIBUTE& attribute, INFO& info)
{
	if (pAStar->GetBesRoadSpace().empty())
	{
		return false;
	}

	m_pAStarNode = pAStar->GetBesRoadSpace().top();

	m_pTile = TileMgr::GetInstance()->GetTile(m_pAStarNode->index);
	m_vTargetDir = MathMgr::GetInstance()->CalTargetDir(info.vPos, m_pTile->GetTileInfo().vPos);

	attribute.vDistance = m_vTargetDir * attribute.speed * TimeMgr::GetInstance()->GetTime();
	ScrollMgr::GetInstance()->SetScrollX(roundf(attribute.vDistance.x));
	ScrollMgr::GetInstance()->SetScrollY(roundf(attribute.vDistance.y));

	info.vPos += attribute.vDistance;

	//cout << info.vPos.x << endl;
	//cout << info.vPos.y << endl;

	// �ٶ󺸴� ���� ���
	attribute.degree = MathMgr::GetInstance()->CalDirDegree(info.vPos, m_pTile->GetTileInfo().vPos);

	// �ڱ���ġ�� Ÿ���ε��� ���
	attribute.tileIndex = TileMgr::GetInstance()->Picking(info.vPos);

	//cout << "Degree: " << attribute.degree << endl;
	float distance = MathMgr::GetInstance()->CalDistance(info.vPos, m_pTile->GetTileInfo().vPos);

	if (distance <= 5.f)
	{
		pAStar->GetBesRoadSpace().pop();
		attribute.bSceneInit = false;
		//attribute.vDistance = D3DXVECTOR3(0.f, 0.f, 0.f);
	}

	return true;
}

void PlayerMoveComponent::FrameCal(ATTRIBUTE & attribute, const FRAME & frame)
{
	if (frame.dirNum[(size_t)attribute.mode] == 0)
		return;

	if (frame.dirNum[(size_t)attribute.mode] == 1)
	{
		attribute.frameDir = 0;
		return;
	}
		
	// �ݴ�������� ������.
	attribute.frameDir = (int)(frame.dirNum[(size_t)attribute.mode] - ((attribute.degree) / (360.f / frame.dirNum[(size_t)attribute.mode])));


	// �����ʱ����� �Ʒ��ʱ������� �ٲ۴�.
	if(frame.dirNum[(size_t)attribute.mode] == 16)
		attribute.frameDir += 12;
	else
		attribute.frameDir += 6;

	attribute.frameDir %= frame.dirNum[(size_t)attribute.mode];
}

