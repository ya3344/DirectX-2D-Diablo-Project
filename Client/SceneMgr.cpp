#include "stdafx.h"
#include "SceneMgr.h"

#include "Logo.h"
#include "Village.h"
#include "Act1.h"
#include "Act4.h"

IMPLEMENT_SINGLETON(SceneMgr);

SceneMgr::SceneMgr()
{
}


SceneMgr::~SceneMgr()
{
	Release();
}

HRESULT SceneMgr::ChangeScene(STAGE sceneID, const D3DXVECTOR3 vPos)
{
	mCurScene = sceneID;
	if (mCurScene != mPreScene)
	{
		switch (sceneID)
		{
		case STAGE::LOGO:
			SafeDelete<Scene*>(m_pScene);
			m_pScene = new Logo;
			gSceneName = L"Logo";
			break;
		case STAGE::VILLAGE:
			/*SafeDelete<Scene*>(m_pScene);
			m_pScene = new Logo;
			m_pScene->Initialize(vPos);*/

			SafeDelete<Scene*>(m_pScene);
			m_pScene = new Village;

			gSceneName = L"Village";
			break;
		case STAGE::ACT1:
			/*SafeDelete<Scene*>(m_pScene);
			m_pScene = new Logo;
			m_pScene->Initialize(vPos);

			SafeDelete<Scene*>(m_pScene);
			m_pScene = new Village;
			m_pScene->Initialize(vPos);*/

			SafeDelete<Scene*>(m_pScene);
			m_pScene = new Act1;

			gSceneName = L"Act1";
			break;
		case STAGE::ACT4:
		/*	SafeDelete<Scene*>(m_pScene);
			m_pScene = new Logo;
			m_pScene->Initialize(vPos);

			SafeDelete<Scene*>(m_pScene);
			m_pScene = new Village;
			m_pScene->Initialize(vPos);

			SafeDelete<Scene*>(m_pScene);
			m_pScene = new Act1;
			m_pScene->Initialize(vPos);*/

			SafeDelete<Scene*>(m_pScene);
			m_pScene = new Act4;

			gSceneName = L"Act4";
			break;
		default:
			break;
		}

		if (m_pScene == nullptr)
		{
			MESSAGE_BOX(L"Scene New Fail", L"SceneMgr::ChangeScene");
			return E_FAIL;
		}

		if (FAILED(m_pScene->Initialize(vPos)))
		{
			MESSAGE_BOX(L"Scene Change Failed", L"SceneMgr::ChangeScene");
			return E_FAIL;
		}
		mPreScene = mCurScene;
	}

	//if (sceneID != SCENE_LOGO)
	//	m_pScene->Update();

	return S_OK;
}

void SceneMgr::Update()
{
	m_pScene->Update();
}

void SceneMgr::Render()
{
	m_pScene->Render();
}

void SceneMgr::Release()
{
	SafeDelete<Scene*>(m_pScene);
}
