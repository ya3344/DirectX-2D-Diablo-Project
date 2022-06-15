#include "stdafx.h"
#include "Player.h"
#include "AStar.h"
#include "Tile.h"
#include "PlayerGraphicsComponent.h"
#include "PlayerMoveComponent.h"
#include "PlayerCollisionComponent.h"
#include "PlayerAnimState.h"
#include "BuffSkill.h"
#include "AttackSkill.h"

Player::Player()
{
}


Player::~Player()
{
	Release();
}

HRESULT Player::Initialize()
{
	mInfo.vPos = D3DXVECTOR3(1500.f, 1500.f, 0.f);
	mInfo.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);

	mObjKey = L"Human";
	mStateKey = L"Neutral";

	mFrame = FRAME(0, (size_t)HUMAN_FRAME::NEUTRAL, (size_t)HUMAN_FRAME::NEUTRAL);

	if (m_pAStar == nullptr)
	{
		m_pAStar = new AStar();
	}

	m_pGraphicsComponent = new PlayerGraphicsComponent;
	m_pMoveComponent = new PlayerMoveComponent;
	m_pCollisionComponent = new PlayerCollisionComponent;
	m_pCollisionComponent->Initialize(this);

	m_pAnimationState = new PlayerAnimState();
	m_pAnimationState->Initialize(HUMAN, mObjKey);

	// 모든 초기화가 이루어진 이후에 실행.
	SetInfo(HUMAN, MODE::NEUTRAL, 10, 20, 25, 25);
	mAttribute.currentHP = mAttribute.maxHP;
	mAttribute.currentMP = mAttribute.maxMP;
	mAttribute.currentSP = mAttribute.maxSP;
	
	mAttribute.nextEXP = 500;

	mAttribute.FallenShamanCount = 5;
	mAttribute.DiabloCount = 1;

	SubjectMgr::GetInstance()->AddData(PLAYER_DATA, &mAttribute);

	return S_OK;
}

int Player::Update(void)
{
	KeyCheck();

	if ( (mAttribute.mode == MODE::WALK || mAttribute.mode == MODE::RUN ) )
	{
		if (m_pMoveComponent->Update(m_pAStar, mAttribute, mInfo) == false)
		{
			mAttribute.mode = MODE::NEUTRAL;
		}
	}
	else if (mAttribute.mode == MODE::NEUTRAL)
	{
		SetSP(+5);
	}

	// Animation Frame Update
	ChangeMode();
	m_pMoveComponent->FrameCal(mAttribute, mFrame);

	// Stage Change Update
	if (StageChange() == OBJ_SCENECHANGE)
		return OBJ_SCENECHANGE;

	return OBJ_NORMAL;
}

void Player::Render(void)
{
	m_pGraphicsComponent->Update(mFrame, mInfo);
	m_pGraphicsComponent->Render(mObjKey, mStateKey, m_pSprite, mFrame, mInfo);
}

void Player::Collision(void)
{
	m_pCollisionComponent->ObstacleCollision(ObjMgr::GetInstance()->GetObjSpace(OBJ_OBSTACLE));
	m_pCollisionComponent->MoveCollision(ObjMgr::GetInstance()->GetObjSpace(OBJ_ENEMY));
	m_pCollisionComponent->AttackCollision(ObjMgr::GetInstance()->GetObjSpace(OBJ_ENEMY));
}

void Player::AddSkillSlot(const TCHAR * pKeyName, D3DXVECTOR3 vPos, int drawID)
{
	if (mSkillSlotSpace.empty() == false)
	{
		auto iterBegin = mSkillSlotSpace.begin();
		auto iterEnd = mSkillSlotSpace.end();

		for (; iterBegin != iterEnd;)
		{
			if (!lstrcmp((*iterBegin)->keyBuf, pKeyName))
			{
				SafeDelete<SKILL_SLOT*>(*iterBegin);
				iterBegin = mSkillSlotSpace.erase(iterBegin);
				iterEnd = mSkillSlotSpace.end();
			}
			else if (vPos == (*iterBegin)->vPos)
			{
				SafeDelete<SKILL_SLOT*>(*iterBegin);
				iterBegin = mSkillSlotSpace.erase(iterBegin);
				iterEnd = mSkillSlotSpace.end();
			}
			else
				++iterBegin;
		}
	}

	SKILL_SLOT* pSkillSlot = new SKILL_SLOT(pKeyName, vPos, drawID);
	mSkillSlotSpace.emplace_back(pSkillSlot);
	//cout << mSkillSlotSpace.size() << endl;
}

void Player::KeyCheck()
{
	Obj* pObj = nullptr;
	if (KeyMgr::GetInstance()->KeyDown(KEY_2))
	{
		SoundMgr::GetInstance()->PlaySound(L"P_Potion.wav", PLAYER_SOUND);
		SetHP(1500);
		SetMP(1500);
		SetSP(1500);
		SubjectMgr::GetInstance()->Notify(PLAYER_DATA, &mAttribute);
	}

	if (KeyMgr::GetInstance()->KeyDown(KEY_3))
	{
		mAttribute.mode = MODE::SKILL_ATTACK;
		pObj = ObjFactory<BuffSkill>::CreateEffect(REVIVE, MathMgr::GetInstance()->CalPoint(), this, ANIMAL);
		ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pObj);

		
	}

	//cout << m_bMoveCheck << endl;
	if(KeyMgr::GetInstance()->KeyDown(KEY_LBUTTON) && m_bMoveCheck)
	{
		if (m_pAStar->AStarStartPos(mInfo.vPos, MathMgr::GetInstance()->CalPoint(), BEAR))
		{
			if (mAttribute.currentSP > 10)
				mAttribute.mode = MODE::RUN;
			else
				mAttribute.mode = MODE::WALK;
		}
	}

	if (KeyMgr::GetInstance()->KeyDown(KEY_RBUTTON))
	{
		mAttribute.degree = MathMgr::GetInstance()->CalDirDegree(mInfo.vPos, MathMgr::GetInstance()->CalPoint());
		SkillOperation();
		
	}

	
	if (mAttribute.mode == MODE::GETHIT || mAttribute.mode == MODE::SPECIAL_CAST || mAttribute.mode == MODE::SKILL_ATTACK)
	{

	}
	else if (GetAsyncKeyState('A') & 0x8000)
	{
		mAttribute.mode = MODE::ATTACK;
	}
	else if (KeyMgr::GetInstance()->KeyDown(KEY_H))
	{
		if (mAttribute.type == WOLF || mAttribute.type == BEAR)
		{
			TransInfo(HUMAN, MODE::NEUTRAL);
		}
	}
	else if (KeyMgr::GetInstance()->KeyDown(KEY_W))
	{
		if (mAttribute.type == HUMAN)
		{
			TransInfo(WOLF, MODE::TRANSFORM);
			Obj* pObj = ObjFactory<BuffSkill>::CreateEffect(TRANSFORM, mInfo.vPos, this);
			ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pObj);
		}
		
	}
	else if (KeyMgr::GetInstance()->KeyDown(KEY_B))
	{
		if (mAttribute.type == HUMAN)
		{
			TransInfo(BEAR, MODE::TRANSFORM);

			Obj* pObj = ObjFactory<BuffSkill>::CreateEffect(TRANSFORM, mInfo.vPos, this);
			ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pObj);
		}
	}
	else
	{
		if (mAttribute.mode != MODE::TRANSFORM)
		{
			if (m_pAStar->GetBesRoadSpace().size() == 0)
				mAttribute.mode = MODE::NEUTRAL;
			else
			{
				if (mAttribute.currentSP > 0)
				{
					mAttribute.mode = MODE::RUN;
					SetSP(-1);
				}
				else
				{
					mAttribute.mode = MODE::WALK;
				}
			}
		}
	}

}

void Player::ChangeMode()
{
	if (mAttribute.mode == MODE::TRANSFORM || mAttribute.mode == MODE::GETHIT || mAttribute.mode == MODE::SPECIAL_CAST || mAttribute.mode == MODE::SKILL_ATTACK)
	{
		if ((int)mFrame.frame == (int)(mFrame.max - 1))
		{
			if(mAttribute.mode == MODE::GETHIT)
				SoundMgr::GetInstance()->PlaySound(L"P_Hit.wav", PLAYER_SOUND);
			mAttribute.mode = MODE::NEUTRAL;
		}
	}

	if (mAttribute.mode != mPreMode || mAttribute.frameDir != mPreFrameDir)
	{
		switch (mAttribute.mode)
		{
		case MODE::NEUTRAL:
			m_bMoveCheck = true;
			m_pAStar->Release();
			m_pAnimationState->FrameUpdate(mAttribute, mFrame, mStateKey);
			m_pMoveComponent->FrameCal(mAttribute, mFrame);
			break;
		case MODE::WALK:
			mAttribute.speed = 130.f;
			break;
		case MODE::RUN:
			mAttribute.speed = 200.f;
			break;
		case MODE::ATTACK:
			m_pAStar->Release();
			break;
		case MODE::TRANSFORM:
			m_bMoveCheck = false;
			break;
		}

		m_pAnimationState->FrameUpdate(mAttribute, mFrame, mStateKey);
		mPreMode = mAttribute.mode;
		mPreFrameDir = mAttribute.frameDir;
	}


}

int Player::StageChange()
{
	if (TileMgr::GetInstance()->GetTile(mAttribute.tileIndex) == nullptr)
	{
		return OBJ_NORMAL;
	}

	if (TileMgr::GetInstance()->GetTile(mAttribute.tileIndex)->GetOption() == TILE_WARP_ENTRANCE)
	{
		if (mAttribute.bSceneInit == false)
		{
			if (gSceneName == L"Village")
			{
				SceneMgr::GetInstance()->ChangeScene(STAGE::ACT1);
			}
			else if (gSceneName == L"Act1")
			{
				SceneMgr::GetInstance()->ChangeScene(STAGE::ACT4);
			}
			mAttribute.bSceneInit = true;
			mAttribute.mode = MODE::NEUTRAL;
			m_pAStar->Release();
			return OBJ_SCENECHANGE;
		}
	}
	else if (PortalCollision())
	{
		if (mAttribute.bSceneInit == false)
		{
			ObjMgr::GetInstance()->GetEffectObj(TOWNPROTAL)->GetBidge()->SetPortalVillage(true);

			if (gSceneName == L"Act1" || gSceneName == L"Act4")
			{
				SceneMgr::GetInstance()->ChangeScene(STAGE::VILLAGE);
			}
			else if (gSceneName == L"Village")
			{
				if (TileMgr::GetInstance()->GetSceneName() == L"Act1")
				{
					SceneMgr::GetInstance()->ChangeScene(STAGE::ACT1, TileMgr::GetInstance()->GetPortalPos());
				}
				else if (TileMgr::GetInstance()->GetSceneName() == L"Act4")
				{
					SceneMgr::GetInstance()->ChangeScene(STAGE::ACT4, TileMgr::GetInstance()->GetPortalPos());
				}
			}
			SoundMgr::GetInstance()->PlaySound(L"P_Portal.wav", PLAYER_SOUND);
			mAttribute.bSceneInit = true;
			mAttribute.mode = MODE::NEUTRAL;
			m_pAStar->Release();
			
			return OBJ_SCENECHANGE;
		}
	}
	else if (RedPortalCollision())
	{
		if (gSceneName == L"Village")
		{
			SceneMgr::GetInstance()->ChangeScene(STAGE::ACT4, (D3DXVECTOR3(653.f, 1779.f, 0.f)) );
		}
		SoundMgr::GetInstance()->PlaySound(L"P_Portal.wav", PLAYER_SOUND);
		mAttribute.bSceneInit = true;
		mAttribute.mode = MODE::NEUTRAL;
		m_pAStar->Release();
		return OBJ_SCENECHANGE;
	}

	return OBJ_NORMAL;
}

void Player::SetInfo(int type, MODE mode, int str, int dex, int life, int energy)
{
	m_pAnimationState->Initialize(type, mObjKey);
	mAttribute.mode = mode;
	mAttribute.type = type;
	mFrame = FRAME(0.f, 0.f, 0);

	mAttribute.str = str;
	mAttribute.dex = dex;
	mAttribute.life = life;
	mAttribute.energy = energy;

	mAttribute.attack = (float)mAttribute.str;
	mAttribute.maxHP = mAttribute.life * 53.f;
	mAttribute.maxMP = mAttribute.energy * 54.f;
	mAttribute.maxSP = mAttribute.str * 62.f;

	SetHP(0);
	SetMP(0);
	SetSP(0);
}

void Player::TransInfo(int type, MODE mode)
{
	if (mAttribute.type == HUMAN)
	{
		if (type == WOLF)
		{
			mAttribute.attack = mAttribute.attack * 3.f;
			mAttribute.maxHP = mAttribute.maxHP * 2.f;
			mAttribute.maxMP = mAttribute.maxMP * 1.5f;
			mAttribute.maxSP = mAttribute.maxSP * 2.f;

			//cout << "Wolf Attack: " << mAttribute.attack << endl;
		}
		else if (type == BEAR)
		{
			mAttribute.attack = mAttribute.attack * 2.f;
			mAttribute.maxHP = mAttribute.maxHP * 3.f;
			mAttribute.maxMP = mAttribute.maxMP * 1.5f;
			mAttribute.maxSP = mAttribute.maxSP * 3.f;

			//cout << "Bear Attack: " << mAttribute.attack << endl;
		}

		
	}
	else if (mAttribute.type == WOLF)
	{
		if (type == HUMAN)
		{
			mAttribute.attack = mAttribute.attack / 3.f;
			mAttribute.maxHP = mAttribute.maxHP / 2.f;
			mAttribute.maxMP = mAttribute.maxMP / 1.5f;
			mAttribute.maxSP = mAttribute.maxSP / 2.f;


			//cout << "Human Attack: " << mAttribute.attack << endl;
		}
	}
	else if (mAttribute.type == BEAR)
	{
		if (type == HUMAN)
		{
			mAttribute.attack = mAttribute.attack / 2.f;
			mAttribute.maxHP = mAttribute.maxHP / 3.f;
			mAttribute.maxMP = mAttribute.maxMP / 1.5f;
			mAttribute.maxSP = mAttribute.maxSP / 3.f;


			//cout << "Human Attack: " << mAttribute.attack << endl;
		}
	}


	m_pAnimationState->Initialize(type, mObjKey);
	mAttribute.mode = mode;
	mAttribute.type = type;
	mFrame = FRAME(0.f, 0.f, 0);


	SetHP(0);
	SetMP(0);
	SetSP(0);
}

void Player::SkillOperation()
{

	Obj* pObj = nullptr;
	float degree = 0;
	switch (mSkillChoice)
	{
	case BOULDER_ROLL_TYPE:
		mAttribute.mode = MODE::SPECIAL_CAST;
		pObj = ObjFactory<AttackSkill>::CreateEffect(BOULDER_ROLL, MathMgr::GetInstance()->CalPoint(), this);
		ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pObj);

		pObj = ObjFactory<BuffSkill>::CreateEffect(FIRE_OVERLAY1, mInfo.vPos, this);
		ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pObj);
		SetMP(-100);
		break;
	case REVIVE_TYPE:
		mAttribute.mode = MODE::SKILL_ATTACK;
		pObj = ObjFactory<BuffSkill>::CreateEffect(REVIVE, MathMgr::GetInstance()->CalPoint(), this, COUNTESS);
		ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pObj);
		SetMP(-100);
		break;
	case TOWNPORTAL_TYPE:
		if (gSceneName == L"Village")
			break;
		if (ObjMgr::GetInstance()->GetEffectObj(TOWNPROTAL) != nullptr)
		{
			ObjMgr::GetInstance()->DeleteSelectObj(ObjMgr::GetInstance()->GetEffectObj(TOWNPROTAL), OBJ_EFFECT);
		}

		pObj = ObjFactory<BuffSkill>::CreateEffect(TOWNPROTAL, MathMgr::GetInstance()->CalPoint(), this);
		ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pObj);
		SetMP(-100);
		break;
	case VOLCAINO_TYPE:
		mAttribute.mode = MODE::SPECIAL_CAST;
		pObj = ObjFactory<AttackSkill>::CreateEffect(VOL_FIRE, MathMgr::GetInstance()->CalPoint(), this);
		ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pObj);

		pObj = ObjFactory<AttackSkill>::CreateEffect(VOL_BASE, MathMgr::GetInstance()->CalPoint(), this);
		ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pObj);

		pObj = ObjFactory<BuffSkill>::CreateEffect(FIRE_OVERLAY2, D3DXVECTOR3(mInfo.vPos.x, mInfo.vPos.y + 20, 0.f), this );
		ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pObj);
		SetMP(-100);

		break;
	case TWISTER_TYPE:
		mAttribute.mode = MODE::SPECIAL_CAST;
		pObj = ObjFactory<AttackSkill>::CreateEffect(TWISTER, MathMgr::GetInstance()->CalPoint(), this);
		ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pObj);
		pObj = ObjFactory<BuffSkill>::CreateEffect(COLD_OVERLAY, mInfo.vPos, this);
		ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pObj);
		SetMP(-100);
		break;
	case METEOR_TYPE:
		mAttribute.mode = MODE::SPECIAL_CAST;
		pObj = ObjFactory<AttackSkill>::CreateEffect(METEOR_READY, MathMgr::GetInstance()->CalPoint(), this);
		ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pObj);
		pObj = ObjFactory<BuffSkill>::CreateEffect(FIRE_OVERLAY1, mInfo.vPos, this);
		ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pObj);
		SetMP(-100);

		SoundMgr::GetInstance()->PlaySound(L"F_Meteor.wav", EFFECT_SOUND);
		break;
	case LIGHTING_TYPE:
		mAttribute.mode = MODE::SKILL_ATTACK;
		for (int i = 0; i < 10; ++i)
		{
			pObj = ObjFactory<AttackSkill>::CreateEffect(STATIC_FIELD, MathMgr::GetInstance()->DegreePos(mInfo.vPos, MathMgr::GetInstance()->CalPoint(), 3.0f), this);
			ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pObj);
		}
		SetMP(-100);
		
		break;
	case DIABLOFIRE_TYPE:
		mAttribute.mode = MODE::SPECIAL_CAST;
		pObj = ObjFactory<BuffSkill>::CreateEffect(FIRE_OVERLAY2, D3DXVECTOR3(mInfo.vPos.x, mInfo.vPos.y + 20, 0.f), this);
		ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pObj);

		for (int i = 0; i < 36; ++i)
		{
			pObj = ObjFactory<AttackSkill>::CreateEffect(DIABLO_FIRE, MathMgr::GetInstance()->Degree360(mInfo.vPos, degree), this);
			ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pObj);
			degree += 10;
		}
		SetMP(-100);
		break;
	default:
		break;
	}
}

bool Player::PortalCollision()
{
	if (mAttribute.bSceneInit == false)
	{
		if (ObjMgr::GetInstance()->GetEffectObj(TOWNPROTAL) != nullptr)
		{
			COLLISION_INFO protalCollision = ObjMgr::GetInstance()->GetEffectObj(TOWNPROTAL)->GetBidge()->GetInfo().mCollisionInfo;

			if (CollisionMgr::CheckRect(mInfo.mCollisionInfo, protalCollision))
			{
				return true;
			}
		}
	}

	return false;
}

bool Player::RedPortalCollision()
{
	if (mAttribute.bSceneInit == false)
	{
		if (ObjMgr::GetInstance()->GetEffectObj(REDPORTAL) != nullptr)
		{
			COLLISION_INFO protalCollision = ObjMgr::GetInstance()->GetEffectObj(REDPORTAL)->GetBidge()->GetInfo().mCollisionInfo;

			if (CollisionMgr::CheckRect(mInfo.mCollisionInfo, protalCollision))
			{
				return true;
			}
		}
	}

	return false;
}

void Player::Release(void)
{
	SafeDelete<AStar*>(m_pAStar);
	SafeDelete<GraphicsComponent*>(m_pGraphicsComponent);
	SafeDelete<MoveComponent*>(m_pMoveComponent);
	SafeDelete<CollisionComponent*>(m_pCollisionComponent);
	SafeDelete<AnimState*>(m_pAnimationState);

	for_each(mSkillSlotSpace.begin(), mSkillSlotSpace.end(), SafeDelete<SKILL_SLOT*>);
}
