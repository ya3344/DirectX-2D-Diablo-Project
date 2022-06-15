#pragma once

class AStar;
class GraphicsComponent;
class MoveComponent;
class CollisionComponent;
class AnimState;

class LifeObj : public Obj
{
public:
	LifeObj();
	virtual ~LifeObj();

	// Obj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update(void) override;
	virtual void Render(void) override;
	virtual void Collision(void) PURE;
	virtual void Release(void) override;

public:
	const wstring& GetStateKey() const { return mStateKey; }

public:
	void SetStateKey(const wstring stateKey) { mStateKey = stateKey; }
	void SetMoveCheck(bool bMoveCheck) { m_bMoveCheck = bMoveCheck; }

protected:
	
	wstring mStateKey = L"";

protected:
	AStar* m_pAStar = nullptr;

protected:
	GraphicsComponent* m_pGraphicsComponent = nullptr;
	MoveComponent* m_pMoveComponent = nullptr;
	CollisionComponent* m_pCollisionComponent = nullptr;
	AnimState* m_pAnimationState = nullptr;

protected:
	MODE mPreMode = MODE::END;
	int mPreFrameDir = -1;
	bool m_bRun = true;
	bool m_bMoveCheck = false;


protected:
	TCHAR mDebugBuf[MAX_PATH] = L"";

};

