#pragma once

class ScrollMgr
{
	DECLARE_SINGLETON(ScrollMgr);
private:
	ScrollMgr();
	~ScrollMgr();

public:
	void Initialize(Obj* pObj) { if (pObj != nullptr) m_pPlayer = pObj; }
	void Update();

public:
	void InitScrollX(float scrollX) { mScrollX = scrollX; }
	void InitScrollY(float scrollY) { mScrollY = scrollY; }

public:
	void SetScrollX(float scrollX);
	void SetScrollY(float scrollY);

public:
	float GetScrollX() const { return mScrollX; }
	float GetScrollY() const { return mScrollY; }

public:
	void PlayerInitPos(const TCHAR* pSceneName, const D3DXVECTOR3& vPos);

private:
	void FreeScroll();
	void PlayerScroll();
	

private:
	float mScrollX = 0.f;
	float mScrollY = 0.f;
	bool m_bFreeScroll = false;

	// Player Scroll Connected
private:
	float mTime = 0.f;
	float mStaticSpeed = 0.f;

private:
	D3DXVECTOR3 m_vDistance;

private:
	Obj* m_pPlayer = nullptr;

};

