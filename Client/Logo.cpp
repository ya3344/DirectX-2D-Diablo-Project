#include "stdafx.h"
#include "Logo.h"
#include "Player.h"
#include "MouseUI.h"
#include "StatUI.h"

Logo::Logo()
{
}


Logo::~Logo()
{
	Release();
}

HRESULT Logo::Initialize(const D3DXVECTOR3& vPos)
{
	if (TileMgr::GetInstance()->GetStageInit(STAGE::LOGO) == false)
	{
		if (FAILED(TextureMgr::GetInstance()->InsertTexture(L"../Texture/Tile/Option/TileOption%d.png"
			, L"TILE_OPTION", TEXTURE_MULTI, L"tileOption", 7)))
		{
			MESSAGE_BOX(L"TILE_OPTION", L"BackGround::Initialize()");
			return E_FAIL;
		}

		if (FAILED(TextureMgr::GetInstance()->ReadImagePath(L"../Data/ImgInfo/Skill.txt")))
			return E_FAIL;

		if (FAILED(TextureMgr::GetInstance()->ReadImagePath(L"../Data/ImgInfo/Logo.txt")))
			return E_FAIL;

		if (FAILED(TextureMgr::GetInstance()->ReadImagePath(L"../Data/ImgInfo/Player.txt")))
			return E_FAIL;

		if (FAILED(TextureMgr::GetInstance()->ReadImagePath(L"../Data/ImgInfo/UI.txt")))
			return E_FAIL;

		ObjMgr::GetInstance()->AddObject(OBJ_PLAYER, ObjFactory<Player>::CreateObj());

		ObjMgr::GetInstance()->AddObject(OBJ_MOUSE,
			ObjFactory<MouseUI>::CreateUI(D3DXVECTOR3(400.f, 550.f, 0.f), NULL));

		TileMgr::GetInstance()->SetStageInit(STAGE::LOGO);
	}
	
	// Sound
	SoundMgr::GetInstance()->PlayBGM(L"BGM_Menu.mp3", CHANNAL::BGM);
	mFrame = FRAME(0.f, 10.f, 5);

	mCollisionRect = { 265, 297 , 265 + 270, 297 + 35 };
	

	return S_OK;
}

void Logo::Update()
{
	Obj* pObj = ObjMgr::GetInstance()->GetObj(OBJ_MOUSE);
	pObj->Update();

	mFrame.frame += mFrame.count * TimeMgr::GetInstance()->GetTime();
	if (mFrame.frame > mFrame.max)
		mFrame.frame = mFrame.frameInit;
}

void Logo::Render()
{
	D3DXMATRIX matTrans;
	D3DXMatrixIdentity(&matTrans);
	MapRender();

	const TEXTURE_INFO* pTextureInfo = TextureMgr::GetInstance()->GetTexture(L"Texture", L"Logo", (int)mFrame.frame);
	D3DXMatrixTranslation(&matTrans, 404.f, 103.f, 0.f);
	mInfo.matWorld = matTrans;
	m_pSprite->SetTransform(&mInfo.matWorld);
	m_pSprite->Draw(pTextureInfo->pTexture, NULL, &D3DXVECTOR3(pTextureInfo->imgInfo.Width * 0.5f, pTextureInfo->imgInfo.Height * 0.5f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


	pTextureInfo = TextureMgr::GetInstance()->GetTexture(L"Texture", L"Logo", 5);
	D3DXMatrixTranslation(&matTrans, 400.f, 315.f, 0.f);
	mInfo.matWorld = matTrans;
	m_pSprite->SetTransform(&mInfo.matWorld);
	m_pSprite->Draw(pTextureInfo->pTexture, NULL, &D3DXVECTOR3(pTextureInfo->imgInfo.Width * 0.5f, pTextureInfo->imgInfo.Height * 0.5f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


	pTextureInfo = TextureMgr::GetInstance()->GetTexture(L"Texture", L"Logo", 7);
	D3DXMatrixTranslation(&matTrans, 400.f, 400.f, 0.f);
	mInfo.matWorld = matTrans;
	m_pSprite->SetTransform(&mInfo.matWorld);
	m_pSprite->Draw(pTextureInfo->pTexture, NULL, &D3DXVECTOR3(pTextureInfo->imgInfo.Width * 0.5f, pTextureInfo->imgInfo.Height * 0.5f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));



	Obj* pObj = ObjMgr::GetInstance()->GetObj(OBJ_MOUSE);
	pObj->Render();

	KeyCheck();
}

void Logo::Release()
{

}

void Logo::KeyCheck()
{
	if (PtInRect(&mCollisionRect, MathMgr::GetInstance()->GetMouse()))
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			SceneMgr::GetInstance()->ChangeScene(STAGE::VILLAGE);
		}
	}

}

void Logo::MapRender()
{
	m_pTextureInfo = TextureMgr::GetInstance()->GetTexture(L"Texture", L"Logo", 8);

	D3DXMATRIX matTrans;
	D3DXMatrixIdentity(&matTrans);

	D3DXMatrixTranslation(&matTrans, WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f, 0.f);
	mMapMatrix = matTrans;

	m_pSprite->SetTransform(&mMapMatrix);

	m_pSprite->Draw(m_pTextureInfo->pTexture, nullptr
		, &D3DXVECTOR3(m_pTextureInfo->imgInfo.Width * 0.5f, m_pTextureInfo->imgInfo.Height * 0.5f, 0.f)
		, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}
