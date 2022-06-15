#pragma once
class Scene abstract
{
public:
	Scene();
	virtual ~Scene();

public:
	virtual HRESULT Initialize(const D3DXVECTOR3& vPos = { 0.f, 0.f, 0.f }) PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

public:
	void PlayerInit(const TCHAR* pSceneName, const D3DXVECTOR3& vPos);


public:
	void LoadingRender(int frame);

protected:
	LPD3DXSPRITE m_pSprite = nullptr;
	const TEXTURE_INFO* m_pTextureInfo = nullptr;

protected:
	D3DXMATRIX mMapMatrix;

// MultiThread Connection
protected:
	static bool g_bLogo;
	static bool g_bVillage;
	static bool g_bAct1;
	static bool g_bAct4;
public:
	static int gLoadingFrame;
	//static FRAME gLoadingFrame;

protected:
	HANDLE m_hThread;

protected:
	//FRAME mLoadingFrame;

};

