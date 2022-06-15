#include "stdafx.h"
#include "Act4.h"


Act4::Act4()
{
}


Act4::~Act4()
{
	Release();
}

HRESULT Act4::Initialize(const D3DXVECTOR3 & vPos)
{
	TileMgr::GetInstance()->Initialize(L"../Data/Tile/Act4.dat");
	TileMgr::GetInstance()->ObstacleLoadData(L"../Data/Obstacle/Act4.dat");

	// Enemy Create
	EnemyMgr::GetInstance()->Initialize(L"../Data/Unit/Act4.dat", ObjMgr::GetInstance()->GetObj(OBJ_PLAYER));

	ScrollMgr::GetInstance()->Initialize(ObjMgr::GetInstance()->GetObj(OBJ_PLAYER));
	ScrollMgr::GetInstance()->PlayerInitPos(L"Act4", vPos);

	if (ObjMgr::GetInstance()->GetEffectObj(TOWNPROTAL) != nullptr)
	{
		ObjMgr::GetInstance()->DeleteSelectObj(ObjMgr::GetInstance()->GetEffectObj(TOWNPROTAL), OBJ_EFFECT);
	}

	if (ObjMgr::GetInstance()->GetEffectObj(REDPORTAL) != nullptr)
	{
		ObjMgr::GetInstance()->DeleteSelectObj(ObjMgr::GetInstance()->GetEffectObj(REDPORTAL), OBJ_EFFECT);
	}

	if (TileMgr::GetInstance()->GetStageInit(STAGE::ACT4) == false)
	{
		gLoadingFrame = 5;
		m_hThread = (HANDLE)_beginthreadex(nullptr, 0, ThreadFunc, this, 0, nullptr);
	}

	SoundMgr::GetInstance()->StopAll();
	SoundMgr::GetInstance()->PlayBGM(L"BGM_Act4.mp3", CHANNAL::BGM);

	return S_OK;
}

void Act4::Update()
{
	if (g_bAct4)
	{
		TileMgr::GetInstance()->Update();
		ObjMgr::GetInstance()->Update();
	}

}

void Act4::Render()
{
	if (g_bAct4)
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

void Act4::Release()
{
	ObjMgr::GetInstance()->DeleteObj(OBJ_OBSTACLE);
	ObjMgr::GetInstance()->DeleteObj(OBJ_ENEMY);
	TileMgr::GetInstance()->Release();
	EnemyMgr::GetInstance()->SetEnemyInit(false);
	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);
}

unsigned int Act4::ThreadFunc(void * pArg)
{
	if (FAILED(TextureMgr::GetInstance()->ReadImagePath(L"../Data/ImgInfo/Wraith.txt")))
		return E_FAIL;
	++gLoadingFrame;

	if (FAILED(TextureMgr::GetInstance()->ReadImagePath(L"../Data/ImgInfo/Demon.txt")))
		return E_FAIL;
	++gLoadingFrame;
	++gLoadingFrame;

	if (FAILED(TextureMgr::GetInstance()->ReadImagePath(L"../Data/ImgInfo/Diablo.txt")))
		return E_FAIL;

	//++gLoadingFrame;

	TileMgr::GetInstance()->SetStageInit(STAGE::ACT4);


	g_bAct4 = true;
	return 0;
}
