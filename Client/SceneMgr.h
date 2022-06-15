#pragma once

class Scene;

class SceneMgr
{
public:
	DECLARE_SINGLETON(SceneMgr);

private:
	SceneMgr();
	~SceneMgr();

public:
	HRESULT ChangeScene(STAGE sceneID, const D3DXVECTOR3 vPos = { 0.f, 0.f, 0.f });
	void Update();
	void Render();
	void Release();

private:
	Scene* m_pScene = nullptr;
	STAGE mCurScene = STAGE::END;
	STAGE mPreScene = STAGE::END;
};

