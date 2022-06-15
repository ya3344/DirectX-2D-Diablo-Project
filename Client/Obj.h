#pragma once

class Bridge;

class Obj abstract
{
public:
	Obj();
	virtual ~Obj();

public:
	virtual HRESULT Initialize() PURE;
	virtual int Update(void) PURE;
	virtual void Render(void) PURE;
	virtual void Release(void) PURE;

public:
	void SetBridge(Bridge* pBirdge) { m_pBridge = pBirdge; }
	void SetObjKey(const TCHAR* pObjKey) { mObjKey = pObjKey; }
	void SetPos(const D3DXVECTOR3 vPos) { mInfo.vPos = vPos; }
	void SetAlpha(const int alpha) { mAlpha = alpha; }
	void SetObj(Obj* pObj) { m_pObj = pObj; }
	void SetTarget(Obj* pObj) { m_pTarget = pObj; }
	void SetDrawID(const int drawID) { mDrawID = drawID; }

public:
	void SetHP(const float HP);
	void SetMP(const float MP);
	void SetSP(const float SP);

public:
	void SetStr(const int str);
	void SetDex(const int dex);
	void SetLife(const int life);
	void SetEnergy(const int energy);

public:
	void SetShamenDisCount() { if(mAttribute.FallenShamanCount > 0) mAttribute.FallenShamanCount -= 1; }
	void SetDiaDisCount() { if (mAttribute.DiabloCount > 0) mAttribute.DiabloCount -= 1; }

public:
	void SetEXP(const float exp);

public:
	void SetStatPoint(const int statPoint);
	void SetSkillPoint(const int skillPoint);

public:
	void SetCollision(const bool bCollision) { mAttribute.bCollision = bCollision; }
	void SetEXCollision(const bool bEXCollision) { mAttribute.bEXCollision = bEXCollision; }

public:
	void SetPlayerDamage(const float attack);
	void SetEnemyDamage(const float attack);

public:
	const Obj* GetObj() const { return m_pObj; }
	Bridge* GetBidge() const { return m_pBridge; }
	const Obj* GetTarget() const { return m_pTarget; }

public:
	const INFO& GetInfo() const { return mInfo; }
	const wstring& GetObjKey() const { return mObjKey; }
	ATTRIBUTE& GetAttribute() { return mAttribute; }
	const FRAME& GetFrame() const { return mFrame; }

public:
	int GetAlpha() const { return mAlpha; }
	int GetDrawID() const { return mDrawID; }

protected:
	LPDIRECT3DDEVICE9 m_pDevice = nullptr;
	LPD3DXSPRITE m_pSprite = nullptr;
	TEXTURE_INFO* m_pTextureInfo = nullptr;

protected:
	INFO mInfo;
	FRAME mFrame;
	ATTRIBUTE mAttribute;

protected:
	wstring mObjKey = L"";
	int mAlpha = 255;
	int mDrawID = 0;

protected:
	Bridge* m_pBridge = nullptr;
	Obj* m_pObj = nullptr;
	Obj* m_pTarget = nullptr;
};

