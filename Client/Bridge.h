#pragma once
class Obj;

class Bridge abstract
{
public:
	Bridge();
	virtual ~Bridge();


public:
	virtual HRESULT Initialize(int type, int enemyType) PURE;
	virtual int Update() PURE;
	virtual void Render(void) PURE;
	virtual void Collision(void) PURE;
	virtual bool Skill() PURE;

public:
	virtual void SetInfo(const int type, const TCHAR* pStateKey, FRAME frame, float durationTime = 0.f, float attack = 0.f) PURE;
	virtual void Release(void) PURE;

public:
	void SetObj(Obj* pObj) { m_pObj = pObj; }
	void SetTargetObj(Obj* pTargetObj) { m_pTargetObj = pTargetObj; }
	void SetPos(const D3DXVECTOR3 vPos) { mInfo.vPos = vPos; }
	void SetType(const int type) { mType = type; }
	void SetColor(D3DXCOLOR color) { mColor = color; }
	void SetCollisionInfo(const COLLISION_INFO collisionInfo) { mInfo.mCollisionInfo = collisionInfo;  }
	void SetPortalVillage(const bool bPortalVillage) { m_bPortalVillage = bPortalVillage; }
public:
	int GetType() const { return mType; }
	const INFO& GetInfo() const { return mInfo; }

protected:
	Obj* m_pObj = nullptr;
	Obj* m_pTargetObj = nullptr;
	wstring mStateKey = L"";
	FRAME mFrame;
	INFO mInfo;
	bool m_bPortalVillage = false;

protected:
	float mDurationTime = 0.f;
	float mAttack = 0.f;
	int mType = SKILL_END;
	int mEnemyType = 0;
	D3DXCOLOR mColor = D3DCOLOR_ARGB(255, 255, 255, 255);
};

