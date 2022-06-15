#include "stdafx.h"
#include "EnemyGraphicsComponent.h"


EnemyGraphicsComponent::EnemyGraphicsComponent()
{
}


EnemyGraphicsComponent::~EnemyGraphicsComponent()
{
}

void EnemyGraphicsComponent::Update(FRAME & frame, INFO & info)
{
	frame.frame += frame.count * TimeMgr::GetInstance()->GetTime();
	if (frame.frame > frame.max)
		frame.frame = frame.frameInit;


	D3DXMatrixTranslation(&info.matTrans, info.vPos.x + ScrollMgr::GetInstance()->GetScrollX()
		, info.vPos.y + ScrollMgr::GetInstance()->GetScrollY() + 30.f
		, 0.f);

}

void EnemyGraphicsComponent::Render(const wstring & objKey, const wstring & stateKey, const LPD3DXSPRITE pSprite, const FRAME & frame, INFO & info)
{
	const TEXTURE_INFO*	pTextureInfo = TextureMgr::GetInstance()->GetTexture(objKey, stateKey, (int)frame.frame);

	if (pTextureInfo == nullptr)
	{
		return;
	}
	info.matWorld = info.matTrans;

	info.centerX = pTextureInfo->imgInfo.Width * 0.5f;
	info.centerY = pTextureInfo->imgInfo.Height * 0.5f;

	pSprite->SetTransform(&info.matWorld);
	pSprite->Draw(pTextureInfo->pTexture, nullptr
		, &D3DXVECTOR3(info.centerX, info.centerY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	// Collision Rect Setting
	info.mCollisionInfo = COLLISION_INFO(0.7f, 0.7f, 0.7f, 0.7f);
	CollisionMgr::SetCollisionRect(info, pTextureInfo);

	DebugMgr::GetInstance()->DrawRectange((float)info.mCollisionInfo.collisionRect.left, (float)info.mCollisionInfo.collisionRect.top,
		info.mCollisionInfo.collisionWidth, info.mCollisionInfo.collisionHeight);
}
