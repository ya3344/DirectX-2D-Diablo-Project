#include "stdafx.h"
#include "Village.h"
#include "Player.h"
#include "Bridge.h"
#include "BarUI.h"
#include "StatUI.h"
#include "SkillUI.h"
#include "QuestUI.h"

Village::Village()
{
}


Village::~Village()
{
	Release();
}

HRESULT Village::Initialize(const D3DXVECTOR3& vPos)
{
	TileMgr::GetInstance()->Initialize(L"../Data/Tile/Village.dat");
	TileMgr::GetInstance()->ObstacleLoadData(L"../Data/Obstacle/Village.dat");
	//Player Init
	ScrollMgr::GetInstance()->Initialize(ObjMgr::GetInstance()->GetObj(OBJ_PLAYER));
	ScrollMgr::GetInstance()->PlayerInitPos(L"Village", vPos);
	
;
	// TownPotal Init
	if (ObjMgr::GetInstance()->GetEffectObj(TOWNPROTAL) != nullptr)
	{
		ObjMgr::GetInstance()->GetEffectObj(TOWNPROTAL)->GetBidge()->SetPos(D3DXVECTOR3(1500.f, 1300.f, 0.f));
		TileMgr::GetInstance()->SetTileOption(D3DXVECTOR3(1500.f, 1300.f, 0.f), TILE_AVAILABLE);
	}
	mNPCFrame = FRAME(0, 13.f, 13);

	if (TileMgr::GetInstance()->GetStageInit(STAGE::VILLAGE) == false)
	{
		gLoadingFrame = 4;
		m_hThread = (HANDLE)_beginthreadex(nullptr, 0, ThreadFunc, this, 0, nullptr);
	}

	EnemyMgr::GetInstance()->SetEnemyInit(true);

	SoundMgr::GetInstance()->StopAll();
	SoundMgr::GetInstance()->PlayBGM(L"BGM_Town.mp3", CHANNAL::BGM);

	return S_OK;
}

void Village::Update()
{
	if (g_bVillage)
	{
		TileMgr::GetInstance()->Update();
		ObjMgr::GetInstance()->Update();

		mNPCFrame.frame += mNPCFrame.count * TimeMgr::GetInstance()->GetTime();
		if (mNPCFrame.frame > mNPCFrame.max)
			mNPCFrame.frame = mNPCFrame.frameInit;
	}

}

void Village::Render()
{
	if (g_bVillage)
	{
		TileMgr::GetInstance()->Render();
		NPCRender();
		ObjMgr::GetInstance()->Render();
		ObjMgr::GetInstance()->Collision();
	}
	else
	{
		Scene::LoadingRender(gLoadingFrame);
	}
}

void Village::Release()
{
	ObjMgr::GetInstance()->DeleteObj(OBJ_OBSTACLE);
	TileMgr::GetInstance()->Release();
	ObjMgr::GetInstance()->DeleteObj(OBJ_ENEMY);
	EnemyMgr::GetInstance()->SetEnemyInit(false);
	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);
}

void Village::NPCRender()
{
	const TEXTURE_INFO* pTextureInfo = TextureMgr::GetInstance()->GetTexture(L"NPC", L"Charsi", (int)mNPCFrame.frame);

	D3DXMATRIX matTrans;
	D3DXMatrixIdentity(&matTrans);

	D3DXMatrixTranslation(&matTrans, 1917.f + ScrollMgr::GetInstance()->GetScrollX(), 641.f + ScrollMgr::GetInstance()->GetScrollY(), 0.f);
	mMapMatrix = matTrans;

	m_pSprite->SetTransform(&mMapMatrix);

	m_pSprite->Draw(pTextureInfo->pTexture, nullptr
		, &D3DXVECTOR3(pTextureInfo->imgInfo.Width * 0.5f, pTextureInfo->imgInfo.Height * 0.5f, 0.f)
		, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	D3DXMatrixIdentity(&matTrans);

	D3DXMatrixTranslation(&matTrans, 2556.f + ScrollMgr::GetInstance()->GetScrollX(), 1438.f + ScrollMgr::GetInstance()->GetScrollY(), 0.f);
	mMapMatrix = matTrans;

	m_pSprite->SetTransform(&mMapMatrix);

	m_pSprite->Draw(pTextureInfo->pTexture, nullptr
		, &D3DXVECTOR3(pTextureInfo->imgInfo.Width * 0.5f, pTextureInfo->imgInfo.Height * 0.5f, 0.f)
		, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	pTextureInfo = TextureMgr::GetInstance()->GetTexture(L"NPC", L"Akara", (int)mNPCFrame.frame);

	D3DXMatrixIdentity(&matTrans);

	D3DXMatrixTranslation(&matTrans, 1595.f + ScrollMgr::GetInstance()->GetScrollX(), 2002.f + ScrollMgr::GetInstance()->GetScrollY(), 0.f);
	mMapMatrix = matTrans;

	m_pSprite->SetTransform(&mMapMatrix);

	m_pSprite->Draw(pTextureInfo->pTexture, nullptr
		, &D3DXVECTOR3(pTextureInfo->imgInfo.Width * 0.5f, pTextureInfo->imgInfo.Height * 0.5f, 0.f)
		, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

}

unsigned int Village::ThreadFunc(void * pArg)
{
	Village* pVillage = (Village*)pArg;

	//pVillage->LoadingRender(0);
	if (FAILED(TextureMgr::GetInstance()->ReadImagePath(L"../Data/ImgInfo/Village.txt")))
		return E_FAIL;
	++gLoadingFrame;

	if (FAILED(TextureMgr::GetInstance()->ReadImagePath(L"../Data/ImgInfo/Act1.txt")))
		return E_FAIL;
	++gLoadingFrame;
	if (FAILED(TextureMgr::GetInstance()->ReadImagePath(L"../Data/ImgInfo/Act4.txt")))
		return E_FAIL;
	++gLoadingFrame;

	if (FAILED(TextureMgr::GetInstance()->ReadImagePath(L"../Data/ImgInfo/NPC.txt")))
		return E_FAIL;
	if (FAILED(TextureMgr::GetInstance()->ReadImagePath(L"../Data/ImgInfo/Animal.txt")))
		return E_FAIL;
	++gLoadingFrame;

	TileMgr::GetInstance()->SetStageInit(STAGE::VILLAGE);

	// UI Init
	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<BarUI>::CreateUI(D3DXVECTOR3(400.f, 550.f, 0.f), FRAME_BAR));
	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<BarUI>::CreateUI(D3DXVECTOR3(70.f, 670.f, 0.f), HP_BAR));
	
	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<BarUI>::CreateUI(D3DXVECTOR3(730.f, 670.f, 0.f), MP_BAR));
	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<BarUI>::CreateUI(D3DXVECTOR3(275.f, 583.f, 0.f), SP_BAR));
	//++gLoadingFrame;

	// StatUI Init
	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<StatUI>::CreateUI(D3DXVECTOR3(0.f, 0.f, 0.f), FRAME_STAT));
	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<StatUI>::CreateUI(D3DXVECTOR3(188.f, 547.f, 0.f), DISABLE_STAT, NORMAL));
	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<StatUI>::CreateUI(D3DXVECTOR3(193.f, 434.f, 0.f), CLOSE_NORMAL_STAT));
	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<StatUI>::CreateUI(D3DXVECTOR3(547.f, 547.f, 0.f), DISABLE_STAT, SKILL));
	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<StatUI>::CreateUI(D3DXVECTOR3(192.f, 122.f, 0.f), DISABLE_STAT, STR));
	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<StatUI>::CreateUI(D3DXVECTOR3(192.f, 185.f, 0.f), DISABLE_STAT, DEX));
	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<StatUI>::CreateUI(D3DXVECTOR3(192.f, 270.f, 0.f), DISABLE_STAT, LIFE));
	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<StatUI>::CreateUI(D3DXVECTOR3(192.f, 333.f, 0.f), DISABLE_STAT, ENERGY));

	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<QuestUI>::CreateUI(D3DXVECTOR3(400.f, 0.f, 0.f), 0));
	// SkillUI Init
	pVillage->SkillUI_Init();

	g_bVillage = true;

	return 0;
}

void Village::SkillUI_Init()
{
	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<SkillUI>::CreateUI(D3DXVECTOR3(400.f, 0.f, 0.f), 62));

	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<SkillUI>::CreateUI(D3DXVECTOR3(420, 14.f, 0.f), 0, 1));

	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<SkillUI>::CreateUI(D3DXVECTOR3(420, 100.f, 0.f), 2, 2));

	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<SkillUI>::CreateUI(D3DXVECTOR3(420, 185.f, 0.f), 6, 3));

	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<SkillUI>::CreateUI(D3DXVECTOR3(420, 357.f, 0.f), 12, 4));

	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<SkillUI>::CreateUI(D3DXVECTOR3(420, 442.f, 0.f), 16, 5));

	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<SkillUI>::CreateUI(D3DXVECTOR3(593.f, 100.f, 0.f), 4, 6));

	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<SkillUI>::CreateUI(D3DXVECTOR3(593.f, 185.f, 0.f), 8, 7));

	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<SkillUI>::CreateUI(D3DXVECTOR3(505.f, 270.f, 0.f), 10, 8));

	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<SkillUI>::CreateUI(D3DXVECTOR3(505.f, 355.f, 0.f), 14, 9));

	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<SkillUI>::CreateUI(D3DXVECTOR3(505.f, 440.f, 0.f), 18, 10));


	// SkillChoice
	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<SkillUI>::CreateUI(D3DXVECTOR3(633.f, 500.f, 0.f), 60, 60 + 11));
	g_bSkillIcon[60] = true;

	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<SkillUI>::CreateUI(D3DXVECTOR3(585.f, 500.f, 0.f), 61, 61 + 11));
	g_bSkillIcon[61] = true;


	// SkillChoice
	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<SkillUI>::CreateUI(D3DXVECTOR3(635.f, 555.f, 0.f), 61, 100));

	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<SkillUI>::CreateUI(D3DXVECTOR3(117.f, 555.f, 0.f), 60, 60 + 100));
}
