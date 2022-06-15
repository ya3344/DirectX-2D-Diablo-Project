#include "stdafx.h"
#include "BuffSkill.h"
#include "Tile.h"
#include "Enemy.h"

BuffSkill::BuffSkill()
{
	m_vRandomPos = { 0.f, 0.f, 0.f };
}


BuffSkill::~BuffSkill()
{
}

HRESULT BuffSkill::Initialize(int type, int enemyType)
{
	mEnemyType = enemyType;

	switch (type)
	{
	case REVIVE:
		SoundMgr::GetInstance()->PlaySound(L"summon.wav", EFFECT_SOUND);
		SetInfo(type, L"Revive", FRAME(0, 25, 25));
		break;
	case TRANSFORM:
		SoundMgr::GetInstance()->PlaySound(L"morph.wav", PLAYER_SOUND);
		SetInfo(type, L"Transform", FRAME(0, 13, 13));
		break;
	case TOWNPROTAL:
		SoundMgr::GetInstance()->PlaySound(L"EFF_Portal.wav", PLAYER_SOUND);
		SetInfo(type, L"TownProtalOpen", FRAME(0, 15, 15));
		break;
	case REDPORTAL:
		SoundMgr::GetInstance()->PlaySound(L"EFF_Portal.wav", PLAYER_SOUND);
		SetInfo(type, L"RedPortalOpen", FRAME(0, 15, 15));
		break;
	case FIRE_OVERLAY1:
		SoundMgr::GetInstance()->PlaySound(L"firecastb.wav", PLAYER_SOUND);
		SetInfo(type, L"FireOverlay1", FRAME(0, 20 *2.f, 20));
		break;
	case FIRE_OVERLAY2:
		SoundMgr::GetInstance()->PlaySound(L"firecastb.wav", PLAYER_SOUND);
		SetInfo(type, L"FireOverlay2", FRAME(0, 20 * 1.5f, 20));
		break;
	case COLD_OVERLAY:
		SoundMgr::GetInstance()->PlaySound(L"firecasta.wav", PLAYER_SOUND);
		SetInfo(type, L"ColdOverlay", FRAME(0, 20 * 1.5f, 20));
		break;
	case TYREAL:
		SetInfo(type, L"Tyreal", FRAME(0, 15 * 1.f, 15));
		m_bForever = true;
		D3DXMatrixScaling(&mInfo.matScale, 3.0f, 3.0f, 3.0f);
		break;
	default:
		break;
	}

	return S_OK;
}

int BuffSkill::Update()
{
	// 스킬효과 발동
	Skill();
	
	// 스킬효과 발동이 안되면 이펙트를 발생시키지 않는다.
	if (m_bOperation == false)
	{
		return OBJ_DIE;
	}

	D3DXMatrixTranslation(&mInfo.matTrans, mInfo.vPos.x + ScrollMgr::GetInstance()->GetScrollX(), mInfo.vPos.y + ScrollMgr::GetInstance()->GetScrollY(), 0.f);
	mFrame.frame += mFrame.count * TimeMgr::GetInstance()->GetTime();

	if (m_bForever == false)
	{
		if (mFrame.frame > mFrame.max)
		{
			return OBJ_DIE;
		}
	}
	else
	{
		if (mFrame.frame > mFrame.max)
		{
			mFrame.frame = mFrame.frameInit;
		}
	}

	

	return OBJ_NORMAL;
}

void BuffSkill::Render(void)
{
	m_pTextureInfo = TextureMgr::GetInstance()->GetTexture(m_pObj->GetObjKey()
		, mStateKey, (int)mFrame.frame);

	mInfo.centerX = m_pTextureInfo->imgInfo.Width * 0.5f;
	mInfo.centerY = m_pTextureInfo->imgInfo.Height * 0.5f;

	m_pSprite->End();
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	mInfo.matWorld = mInfo.matScale * mInfo.matTrans;
	//cout << (int)mFrame.frame << endl;
	m_pSprite->SetTransform(&mInfo.matWorld);
	m_pSprite->Draw(m_pTextureInfo->pTexture, nullptr
		, &D3DXVECTOR3(mInfo.centerX, mInfo.centerY, 0.f)
		, nullptr, mColor);

	m_pSprite->End();
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);


	
	if (mStateKey == L"TonwPortalDoor")
	{
		PortalCollision();
		DebugMgr::GetInstance()->DrawRectange((float)mInfo.mCollisionInfo.collisionRect.left, (float)mInfo.mCollisionInfo.collisionRect.top,
			mInfo.mCollisionInfo.collisionWidth, mInfo.mCollisionInfo.collisionHeight);
	}
	else if (mStateKey == L"RedPortalDoor")
	{
		RedPortalCollision();
		DebugMgr::GetInstance()->DrawRectange((float)mInfo.mCollisionInfo.collisionRect.left, (float)mInfo.mCollisionInfo.collisionRect.top,
			mInfo.mCollisionInfo.collisionWidth, mInfo.mCollisionInfo.collisionHeight);
	}


}

bool BuffSkill::Skill()
{
	switch (mType)
	{
	case REVIVE:
		m_bOperation = Summon(mEnemyType);
		break;
	case TOWNPROTAL:
		m_bOperation = Portal();
		break;
	case REDPORTAL:
		m_bOperation = RedPortal();
		break;
	default:
		m_bOperation = true;
		break;
	}

	if (m_bOperation == false)
		return false;

	return true;
}

void BuffSkill::SetInfo(const int type, const TCHAR * pStateKey, FRAME frame, float durationTime, float attack)
{
	SkillBridge::SetInfo(type, pStateKey, frame, durationTime, attack);
}

bool BuffSkill::Summon(int objType)
{
	size_t tileIndex = 0;
	int count = 0;

	if (m_bSummonInit == false)
	{
		while (count <= 3)
		{
			m_vRandomPos = MathMgr::GetInstance()->RandomPos(mInfo.vPos);
			tileIndex = TileMgr::GetInstance()->Picking(m_vRandomPos);

			if (tileIndex != -1 && tileIndex < TileMgr::GetInstance()->GetTileSpace().size())
			{
				m_pTile = TileMgr::GetInstance()->GetTile(tileIndex);
				if (m_pTile->GetOption() == TILE_AVAILABLE)
				{
					Obj* pEnemy = ObjFactory<Enemy>::CreateEnemy(m_vRandomPos, ObjMgr::GetInstance()->GetObj(OBJ_PLAYER), objType);
					ObjMgr::GetInstance()->AddObject(OBJ_ENEMY, pEnemy);
					mInfo.vPos = m_vRandomPos;
					m_bSummonInit = true;
					return true;	
				}
			}
			++count;
		}
	}
	else
	{
		return true;
	}
	

	return false;
}

bool BuffSkill::Portal()
{
	if (m_bPortalInit == false)
	{
		if (mFrame.frame > mFrame.max - 6)
		{
			m_bForever = true;
			mStateKey = L"TonwPortalDoor";
			TileMgr::GetInstance()->SetPortalPos(mInfo.vPos);
			TileMgr::GetInstance()->SetSceneName(gSceneName);

			m_bPortalInit = true;

			return true;
		}
	}

	return true;
}

bool BuffSkill::RedPortal()
{
	if (mFrame.frame > mFrame.max - 6)
	{
		m_bForever = true;
		mStateKey = L"RedPortalDoor";

		return true;
	}
	
	return true;
}

void BuffSkill::PortalCollision()
{
	if (m_bPortalVillage)
	{
		mInfo.mCollisionInfo = COLLISION_INFO(0.f, 0.f, 0.f, 0.f);
	}
	else
	{
		mInfo.mCollisionInfo = COLLISION_INFO(0.5f, 0.5f, 0.5f, 0.5f);
		CollisionMgr::SetCollisionRect(mInfo, m_pTextureInfo);
	}

	if (SkillOperation(2.5f))
	{
		m_bPortalVillage = false;
	}

	
}

void BuffSkill::RedPortalCollision()
{
	mInfo.mCollisionInfo = COLLISION_INFO(0.5f, 0.5f, 0.5f, 0.5f);
	CollisionMgr::SetCollisionRect(mInfo, m_pTextureInfo);
}

bool BuffSkill::SkillOperation(const float time)
{
	if (m_bPortalVillage == false)
	{
		mSkillTime = 0.f;
		return false;
	}
		
	if (mSkillTime < time)
	{
		mSkillTime += TimeMgr::GetInstance()->GetTime();
		//cout << mSkillTime << endl;
	}
	else
	{
		mSkillTime = 0.f;
		return true;
	}
	return false;
}

void BuffSkill::Release(void)
{
}
