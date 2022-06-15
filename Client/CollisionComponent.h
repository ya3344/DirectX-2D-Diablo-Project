#pragma once
class CollisionComponent abstract
{
public:
	CollisionComponent();
	virtual ~CollisionComponent();

public:
	virtual void Initialize(Obj* pSrc) PURE;
	virtual void ObstacleCollision(const list<Obj*>& objSpace) PURE;
	virtual void MoveCollision(const list<Obj*>& objSpace) PURE;
	virtual void AttackCollision(const list<Obj*>& objSpace) PURE;

protected:
	void ObstacleCollision_Common(Obj* pSrc, const list<Obj*>& objSpace);
protected:
	Obj* m_pSrc = nullptr;
protected:
	int mFrame = 0;
	int mFrameNum = 0;
	int mAttackPercent = 0;
};

