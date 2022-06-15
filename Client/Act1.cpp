#include "stdafx.h"
#include "Act1.h"
#include "Player.h"
#include "Bridge.h"

Act1::Act1()
{
}


Act1::~Act1()
{
	Release();
}

HRESULT Act1::Initialize(const D3DXVECTOR3& vPos)
{
	TileMgr::GetInstance()->Initialize(L"../Data/Tile/Act1.dat");
	TileMgr::GetInstance()->ObstacleLoadData(L"../Data/Obstacle/Act1.dat");
	// Enemy Create
	EnemyMgr::GetInstance()->Initialize(L"../Data/Unit/Act1.dat", ObjMgr::GetInstance()->GetObj(OBJ_PLAYER));

	ScrollMgr::GetInstance()->Initialize(ObjMgr::GetInstance()->GetObj(OBJ_PLAYER));
	ScrollMgr::GetInstance()->PlayerInitPos(L"Act1", vPos);


	if (ObjMgr::GetInstance()->GetEffectObj(TOWNPROTAL) != nullptr)
	{
		ObjMgr::GetInstance()->DeleteSelectObj(ObjMgr::GetInstance()->GetEffectObj(TOWNPROTAL), OBJ_EFFECT);
	}

	if (TileMgr::GetInstance()->GetStageInit(STAGE::ACT1) == false)
	{
		gLoadingFrame = 5;
		m_hThread = (HANDLE)_beginthreadex(nullptr, 0, ThreadFunc, this, 0, nullptr);
	}

	SoundMgr::GetInstance()->StopAll();
	SoundMgr::GetInstance()->PlayBGM(L"BGM_Act1.mp3", CHANNAL::BGM);
	return S_OK;
}

void Act1::Update()
{
	if (g_bAct1)
	{
		TileMgr::GetInstance()->Update();
		ObjMgr::GetInstance()->Update();
	}
}
	

void Act1::Render()
{
	if (g_bAct1)
	{
		TileMgr::GetInstance()->Render();
		ObjMgr::GetInstance()->Render();
		ObjMgr::GetInstance()->Collision();
	}
	else
	{
		LoadingRender(gLoadingFrame);
	}

}

void Act1::Release()
{
	ObjMgr::GetInstance()->DeleteObj(OBJ_OBSTACLE);
	ObjMgr::GetInstance()->DeleteObj(OBJ_ENEMY);
	TileMgr::GetInstance()->Release();
	EnemyMgr::GetInstance()->SetEnemyInit(false);
	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);
}

unsigned int Act1::ThreadFunc(void * pArg)
{
	if (FAILED(TextureMgr::GetInstance()->ReadImagePath(L"../Data/ImgInfo/Council.txt")))
		return E_FAIL;
	++gLoadingFrame;

	if (FAILED(TextureMgr::GetInstance()->ReadImagePath(L"../Data/ImgInfo/Countess.txt")))
		return E_FAIL;
	++gLoadingFrame;

	if (FAILED(TextureMgr::GetInstance()->ReadImagePath(L"../Data/ImgInfo/FallenShaman.txt")))
		return E_FAIL;
	++gLoadingFrame;

	if (FAILED(TextureMgr::GetInstance()->ReadImagePath(L"../Data/ImgInfo/Fallen.txt")))
		return E_FAIL; 
	//++gLoadingFrame;

	TileMgr::GetInstance()->SetStageInit(STAGE::ACT1);
	g_bAct1 = true;
	return 0;
}
