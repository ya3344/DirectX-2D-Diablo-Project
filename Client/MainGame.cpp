#include "stdafx.h"
#include "MainGame.h"

int gTileXNum = 0;
int gTileYNum = 0;

bool g_bFontDraw = false;
bool g_bCollingDraw = false;

MainGame::MainGame()
{
	srand((unsigned int)time(nullptr));
}


MainGame::~MainGame()
{
	Release();
}

HRESULT MainGame::Initialize(void)
{
	if (FAILED(Device::GetInstance()->InitDevice()))
	{
		MESSAGE_BOX(L"Init Fail", L"MainGame::Initialize()");
		return E_FAIL;
	}
	

	m_pDevice = Device::GetInstance()->GetDevice();
	if (m_pDevice == nullptr)
	{
		MESSAGE_BOX(L"GetDivice Fail", L"MainGame::Initialize()");
		return E_FAIL;
	}

	m_pSprite = Device::GetInstance()->GetSprite();

	m_pSceneMgr = SceneMgr::GetInstance();
	if (FAILED(m_pSceneMgr->ChangeScene(STAGE::LOGO)))
		return E_FAIL;
		
	TimeMgr::GetInstance()->InitTime();
	return S_OK;
}

void MainGame::Update(void)
{
	KeyMgr::GetInstance()->KeyCheck();
	TimeMgr::GetInstance()->SetTime();
	m_pSceneMgr->Update();
	ScrollMgr::GetInstance()->Update();
	SoundMgr::GetInstance()->Update();
}

void MainGame::Render(void)
{
	mTime += TimeMgr::GetInstance()->GetTime();
	++mTimeCount;

	if (mTime > 1.f)
	{
		mTime = 0.f;
		wsprintf(mFPSBuf, L"FPS : %d", mTimeCount);
		mTimeCount = 0;
	}

	m_pDevice->Clear(0, nullptr
		, D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET
		, D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);
	m_pDevice->BeginScene();
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	m_pSceneMgr->Render();

	DebugMgr::GetInstance()->DebugText(mFPSBuf, D3DXVECTOR3(0.f, 0.f, 0.f));

	m_pSprite->End();
	m_pDevice->EndScene();
	m_pDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

void MainGame::Release(void)
{
	Device::GetInstance()->DestroyInstance();
	ScrollMgr::GetInstance()->DestroyInstance();
	TextureMgr::GetInstance()->DestroyInstance();
	SceneMgr::GetInstance()->DestroyInstance();
	TimeMgr::GetInstance()->DestroyInstance();
	ObjMgr::GetInstance()->DestroyInstance();
	KeyMgr::GetInstance()->DestroyInstance();
	DebugMgr::GetInstance()->DestroyInstance();
	TileMgr::GetInstance()->DestroyInstance();
	EnemyMgr::GetInstance()->DestroyInstance();
	MathMgr::GetInstance()->DestroyInstance();
	SubjectMgr::GetInstance()->DestroyInstance();
	SoundMgr::GetInstance()->DestroyInstance();
	//_CrtDumpMemoryLeaks();
}
