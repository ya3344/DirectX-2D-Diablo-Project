#include "stdafx.h"
#include "AStar.h"
#include "Tile.h"

AStar::AStar()
{
	mOpenList.clear();
	mCloseList.clear();
	mExceptionPos = { 0.f ,0.f, 0.f };
}

AStar::~AStar()
{
	Clear();
}

bool AStar::AStarStart(size_t startIndex, size_t goalIndex)
{
	if (startIndex == goalIndex)
		return false;

	if (goalIndex < 0 || goalIndex >= TILE_TOTAL_NUM)
		return false;

	const vector<Tile*>& tileSpace = TileMgr::GetInstance()->GetTileSpace();

	if (tileSpace[goalIndex]->GetOption() == TILE_BLOCK)
		return false;

	mStartIndex = startIndex;
	mGoalIndex = goalIndex;

	// FindRoute after clear
	Clear();
	FindRoute(tileSpace);

	if (mBestRoadSpace.empty())
		return false;

	return true;
}

bool AStar::AStarStartPos(const D3DXVECTOR3 & vStartPos, const D3DXVECTOR3& vGoalPos, int type)
{
	mStartIndex = m_pTileMgr->Picking(vStartPos);
	mGoalIndex = m_pTileMgr->Picking(vGoalPos);

	if (mStartIndex == E_FAIL || mGoalIndex == E_FAIL)
		return false;
	
	if (AStarStart(mStartIndex, mGoalIndex) == false)
		return false;
	
	return true;
}

void AStar::FindRoute(const vector<Tile*>& tileSpace)
{
	//  Eight Direction Investigation
	ASTAR_NODE* pParent = new ASTAR_NODE(0.f, mStartIndex, nullptr, DIRECTION::DOWN);
	mCloseList.emplace_back(pParent);

	ASTAR_NODE* pNode = nullptr;

	while (true)
	{
		if (mAStarCount >= MAX_ASTAR_COUNT)
		{
			Clear();
			return;
		}

		
		{ // Up
			mIndex = pParent->index - TILE_NUM_X;

			if (Tile_BoundaryCheck(pParent->index, DIRECTION::UP)
				&& tileSpace[mIndex]->GetOption() != TILE_BLOCK
				&& CheckList(mIndex))
			{
				pNode = CreateNode(pParent, mIndex, tileSpace, DIRECTION::UP);
				mOpenList.emplace_back(pNode);
			}
		}
		 
		{ // RightUp, Right, Right Down, Down, LeftDown, Left, LeftUp
			
			// »ý·«
		}

		if (mOpenList.empty())
			return;

		// Sort by weighting
		mOpenList.sort(Compare);

		auto& iterOpenList = mOpenList.begin();
		mCloseList.emplace_back(*iterOpenList);

		pParent = (*iterOpenList);
		mOpenList.erase(iterOpenList);

		if (pParent->index == mGoalIndex)
		{
			while (true)
			{
				// Create Path
				if (pParent->pParent == nullptr)
					break;

				mBestRoadSpace.emplace(pParent);
				pParent = pParent->pParent;
			}
			break;
		}

		++mAStarCount;
	}
}

ASTAR_NODE * AStar::CreateNode(ASTAR_NODE* pParent, int index, const vector<Tile*>& tileSpace, DIRECTION dir)
{
	float G = m_pMathMgr->CalDistance(tileSpace[pParent->index]->GetTileInfo().vPos, tileSpace[index]->GetTileInfo().vPos);
	float H = m_pMathMgr->CalDistance(tileSpace[index]->GetTileInfo().vPos, tileSpace[mGoalIndex]->GetTileInfo().vPos);

	ASTAR_NODE* pNode = new ASTAR_NODE(G+H, index, pParent, dir);

	return pNode;
}

bool AStar::CheckList(size_t index)
{
	for (ASTAR_NODE* pNode : mOpenList)
	{
		if (pNode->index == index)
			return false;
	}

	for (ASTAR_NODE* pNode : mCloseList)
	{
		if (pNode->index == index)
			return false;
	}

	return true;
}

bool AStar::Compare(ASTAR_NODE * pSrcNode, ASTAR_NODE * pDestNode)
{
	return pSrcNode->cost < pDestNode->cost;
}

bool AStar::Tile_BoundaryCheck(size_t index, DIRECTION dir)
{
}

void AStar::Clear(void)
{
	for_each(mOpenList.begin(), mOpenList.end(), SafeDelete<ASTAR_NODE*>);
	mOpenList.clear();

	for_each(mCloseList.begin(), mCloseList.end(), SafeDelete<ASTAR_NODE*>);
	mCloseList.clear();
	
	while (mBestRoadSpace.empty() == false)
	{
		mBestRoadSpace.pop();
	}
}
