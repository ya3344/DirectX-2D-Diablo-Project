#pragma once

class AStar;
class Tile;

class MoveComponent abstract
{
public:
	MoveComponent();
	virtual ~MoveComponent();

public:
	virtual bool Update(AStar* pAStar, ATTRIBUTE& attribute, INFO& info) PURE;
	virtual void FrameCal(ATTRIBUTE& attribute, const FRAME& frame) PURE;

protected:
	ASTAR_NODE* m_pAStarNode = nullptr;
	Tile* m_pTile = nullptr;
	D3DXVECTOR3 m_vTargetDir;
};

