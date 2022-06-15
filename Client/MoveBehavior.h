#pragma once
class AStar;
class Obj;

class MoveBehavior abstract
{
public:
	MoveBehavior();
	virtual ~MoveBehavior();

public:
	virtual void Initialize(AStar* pAStar, int enemyType) PURE;
	virtual int Move(Obj* srcObj, Obj* destObj) PURE;
	
protected:
	bool RandomMove(const INFO& srcInfo, AStar* pAStar);
	bool SkillOperation(float time, int enemyType = 0);

protected:
	AStar* m_pAStar = nullptr;
	DWORD mMoveTime = 0;
	size_t mRandomTime = 0;
	float mSkillTime = 0.f;
	size_t  mMoveState;

protected:
	D3DXVECTOR3 m_vRandomPos;
	int mEnemyType = 0;


};

