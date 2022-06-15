#pragma once

class Scene;

class MainGame
{
public:
	MainGame();
	~MainGame();

public:
	HRESULT Initialize(void);
	void Update(void);
	void Render(void);

private:
	void Release(void);

private:
	LPDIRECT3DDEVICE9 m_pDevice = nullptr;
	LPD3DXSPRITE m_pSprite = nullptr;

private:
	SceneMgr* m_pSceneMgr = nullptr;

private:
	// Time Connected Variable
	float mTime = 0.f;
	DWORD mTimeCount = 0;
	TCHAR mFPSBuf[32] = L"";

};

