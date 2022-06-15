#pragma once

class Tile;


class AStar
{
public:
	AStar();
	~AStar();

public:
	stack<ASTAR_NODE*>& GetBesRoadSpace(void) { return mBestRoadSpace; }
	void Clear(void);

public:
	bool AStarStart(size_t startIndex, size_t goalIndex);
	bool AStarStartPos(const D3DXVECTOR3& vStartPos, const D3DXVECTOR3& vGoalPos, int type = 0);
public:
	void SetObjID(const int objID) { mObjID = objID; }

private:
	void FindRoute(const vector<Tile*>& tileSpace);
	ASTAR_NODE* CreateNode(ASTAR_NODE* pParent, int index, const vector<Tile*>& tileSpace, DIRECTION dir);
	bool CheckList(size_t index);
	static bool Compare(ASTAR_NODE* pSrcNode, ASTAR_NODE* pDestNode);

private:
	bool Tile_BoundaryCheck(size_t index, DIRECTION dir);
	int mIndex = 0;
	size_t mAStarCount = 0;

private:
	list<ASTAR_NODE*> mOpenList;
	list<ASTAR_NODE*> mCloseList;

	stack<ASTAR_NODE*> mBestRoadSpace;
	MathMgr* m_pMathMgr;
	TileMgr* m_pTileMgr;

private:
	size_t mStartIndex = 0;
	size_t mGoalIndex = 0;

	int mObjID = 0;

	D3DXVECTOR3 mExceptionPos;

	static constexpr size_t TILE_TOTAL_NUM = 0;
	static constexpr size_t TILE_NUM_X = 0;
	static constexpr size_t TILE_NUM_Y = 0;
	static constexpr size_t MAX_ASTAR_COUNT = 0;

};

