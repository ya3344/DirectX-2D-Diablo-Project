#pragma once

class Tile;

class TileMgr
{
	DECLARE_SINGLETON(TileMgr);

private:
	TileMgr();
	~TileMgr();

public:
	void Initialize(const TCHAR* pFilePath);
	void Update();
	void Render();
	void Release();
public:
	void ObstacleLoadData(const TCHAR* pFilePath);

public:
	int Picking();
	HRESULT Picking(const D3DXVECTOR3& vPos);
	void LoadData(const TCHAR* pFilePath);

public:
	bool SetTileOption(const D3DXVECTOR3& vPos, const int option);
	void SetDrawID(int drawID) { mDrawID = drawID; }
	void SetStageInit(const STAGE stageID) { m_bStageInit[(size_t)stageID] = true; }
	void SetPortalPos(const D3DXVECTOR3& vProtalPos) { m_vPortalPos = vProtalPos; }
	void SetSceneName(const TCHAR* pSceneName) { m_pSceneName = pSceneName; }
public:
	vector<Tile*> GetTileSpace() const { return mTileSpace; }
	Tile* GetTile(const size_t index);
	bool GetStageInit(const STAGE stageID) const { return m_bStageInit[(size_t)stageID]; }
	const D3DXVECTOR3& GetPortalPos() { return m_vPortalPos; }
	const TCHAR* GetSceneName() const { return m_pSceneName; }

	bool GetTileInit() const { return m_bTileInit; }
	bool GetObstacleInit() const { return m_bObstacleInit; }
private:
	D3DXVECTOR3 m_vPos;
	int mDrawID = 0;
	bool m_bDraw = false;

private:
	bool m_bStageInit[(size_t)STAGE::END] = {};

private:
	vector<Tile*> mTileSpace;

private:
	D3DXVECTOR3 m_vPortalPos;
	size_t mPortalIndex = 0;
	const TCHAR* m_pSceneName = nullptr;
	bool m_bTileInit = false;
	bool m_bObstacleInit = false;
};

