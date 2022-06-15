#include "stdafx.h"
#include "Obstacle.h"


Obstacle::Obstacle()
{

}


Obstacle::~Obstacle()
{
}

HRESULT Obstacle::Initialize()
{
	return S_OK;
}

int Obstacle::Update(void)
{
	return OBJ_NORMAL;
}

void Obstacle::Render(void)
{
	D3DXMatrixTranslation(&mInfo.matTrans, mInfo.vPos.x + ScrollMgr::GetInstance()->GetScrollX(),
		mInfo.vPos.y + ScrollMgr::GetInstance()->GetScrollY(), mInfo.vPos.z);

	mInfo.matWorld = mInfo.matTrans;

	m_pTextureInfo = TextureMgr::GetInstance()->GetTexture(gSceneName, L"Obstacle", mDrawID);
	mInfo.centerX = m_pTextureInfo->imgInfo.Width * 0.5f;
	mInfo.centerY = 0.f;
	
	m_pSprite->SetTransform(&mInfo.matWorld);
	m_pSprite->Draw(m_pTextureInfo->pTexture, nullptr, &D3DXVECTOR3(mInfo.centerX, mInfo.centerY, 0.f), nullptr, D3DCOLOR_ARGB(mAlpha, 255, 255, 255));

	if (m_pTextureInfo->imgInfo.Width >= 900)
	{
		mInfo.mCollisionInfo = COLLISION_INFO(0.2f, 0.0f, 0.7f, 0.4f, 230, +430);
	}
	else if (gSceneName == L"Act4")
	{
		if (mDrawID == 5 || mDrawID == 6 || (mDrawID <= 20 && mDrawID >= 15))
		{
			mInfo.mCollisionInfo = COLLISION_INFO(0.0f, 0.0f, 0.0f, 0.0f);
		}
		else
		{
			mInfo.mCollisionInfo = COLLISION_INFO(0.8f, 0.0f, 0.8f, 0.7f, 0, +30);
		}
	}
	else
	{
		mInfo.mCollisionInfo = COLLISION_INFO(0.8f, 0.0f, 0.8f, 0.7f, 0, +30);
	}
	
	
	CollisionMgr::SetCollisionRect(mInfo, m_pTextureInfo);

	DebugMgr::GetInstance()->DrawRectange((float)mInfo.mCollisionInfo.collisionRect.left, (float)mInfo.mCollisionInfo.collisionRect.top,
		mInfo.mCollisionInfo.collisionWidth, mInfo.mCollisionInfo.collisionHeight);

}


void Obstacle::Release(void)
{

}

