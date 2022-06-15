#pragma once
#include "LifeObj.h"

class MoveBehavior;

class Enemy : public LifeObj
{
public:
	Enemy();
	virtual ~Enemy();

	// Obj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update(void) override;
	virtual void Render(void) override;
	virtual void Collision(void) override;

private:
	void ChangeMode();
	void AttackDir(const D3DXVECTOR3 vSrcPos, const D3DXVECTOR3 vDestPos);
public:
	void SetType(const int type) { mAttribute.type = type; }
	void SkillOperation(const int type);
public:
	virtual void Release(void) override;

private:
	MoveBehavior* m_pMoveBehaivor = nullptr;
	ObjMgr* m_pObjMgr = nullptr;
	MathMgr* m_pMathMgr = nullptr;
};

