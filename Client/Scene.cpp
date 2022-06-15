#include "stdafx.h"
#include "Scene.h"

bool Scene::g_bLogo = false;
bool Scene::g_bVillage = false;
bool Scene::g_bAct1 = false;
bool Scene::g_bAct4 = false;
int Scene::gLoadingFrame = 0;
//FRAME Scene::gLoadingFrame = FRAME(0.f, 10.f, 10);

Scene::Scene()
{
	m_pSprite = Device::GetInstance()->GetSprite();
	D3DXMatrixIdentity(&mMapMatrix);
}


Scene::~Scene()
{
}

void Scene::PlayerInit(const TCHAR* pSceneNamem, const D3DXVECTOR3 & vPos)
{

}

void Scene::LoadingRender(int frame)
{
	D3DXMATRIX matTrans;
	D3DXMatrixIdentity(&matTrans);

	const TEXTURE_INFO* pTextureInfo = TextureMgr::GetInstance()->GetTexture(L"UI", L"Loading", frame);
	D3DXMatrixTranslation(&matTrans, WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f, 0.f);
	m_pSprite->SetTransform(&matTrans);
	m_pSprite->Draw(pTextureInfo->pTexture, NULL, &D3DXVECTOR3(pTextureInfo->imgInfo.Width * 0.5f, pTextureInfo->imgInfo.Height * 0.5f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}
