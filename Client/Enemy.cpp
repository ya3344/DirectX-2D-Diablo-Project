#include "stdafx.h"
#include "Enemy.h"
#include "EnemyGraphicsComponent.h"
#include "EnemyMoveComponent.h"
#include "EnemyCollisionComponent.h"
#include "EnemyAnimState.h"
#include "ChaseMoveBehavior.h"
#include "EscapeMoveBehavior.h"
#include "AStar.h"
#include "AttackSkill.h"
#include "BuffSkill.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
	Release();
}

HRESULT Enemy::Initialize()
{
	mFrame = FRAME(0, (size_t)HUMAN_FRAME::NEUTRAL, (size_t)HUMAN_FRAME::NEUTRAL);
	mStateKey = L"Neutral";

	mAttribute.mode = MODE::NEUTRAL;

	if (mAttribute.type == ANIMAL)
	{
		mAttribute.mode = MODE::SPECIAL_CAST;
	}

	if (m_pAStar == nullptr)
	{
		m_pAStar = new AStar();
	}

	// Component
	m_pGraphicsComponent = new EnemyGraphicsComponent;
	m_pMoveComponent = new EnemyMoveComponent;
	m_pCollisionComponent = new EnemyCollisionComponent;
	m_pCollisionComponent->Initialize(this);

	// State
	m_pAnimationState = new EnemyAnimState();
	m_pAnimationState->Initialize(mAttribute.type, mObjKey);

	// Strategy

	switch (mAttribute.type)
	{
	case ENEMY_TYPE::FALLEN_SHAMON:
	case ENEMY_TYPE::COUNCIL:
	case ENEMY_TYPE::COUNTESS:
		m_pMoveBehaivor = new EscapeMoveBehavior();
		m_pMoveBehaivor->Initialize(m_pAStar, mAttribute.type);
		break;
	default:
		m_pMoveBehaivor = new ChaseMoveBehavior();
		m_pMoveBehaivor->Initialize(m_pAStar, mAttribute.type);
		break;
	}
	
	return S_OK;
}

int Enemy::Update(void)
{
	int state = m_pMoveBehaivor->Move(this, m_pObj);

	if (mAttribute.mode == MODE::GETHIT || mAttribute.mode == MODE::DEATH || mAttribute.mode == MODE::SPECIAL_CAST
		|| mAttribute.mode == MODE::SPECIAL || mAttribute.mode == MODE::FIRE_CAST || mAttribute.mode == MODE::ATTACK)
	{
		if (mAttribute.mode == MODE::SPECIAL_CAST || mAttribute.mode == MODE::SPECIAL || mAttribute.mode == MODE::FIRE_CAST)
		{
			SkillOperation(mAttribute.type);
		}
	}
	else if (state == OBJ_SPECIAL)
	{
		mAttribute.mode = MODE::SPECIAL_CAST;
	}
	else if (state == OBJ_BOSS_SUMMON_CAST)
	{
		mAttribute.mode = MODE::SPECIAL;
	}
	else if (state == OBJ_FIRE_CAST)
	{
		mAttribute.mode = MODE::FIRE_CAST;
	}
	else if (state == OBJ_MOVE)
	{
		mAttribute.mode = MODE::RUN;
		mAttribute.bEXCollision = false;
		mAttribute.bCollision = false;
	}
	else if (state == OBJ_ATTACK)
	{
		mAttribute.mode = MODE::ATTACK;
		mAttribute.degree = MathMgr::GetInstance()->CalDirDegree(mInfo.vPos, D3DXVECTOR3(m_pObj->GetInfo().vPos.x, m_pObj->GetInfo().vPos.y, 0.f));
	}

	if ((mAttribute.mode == MODE::WALK || mAttribute.mode == MODE::RUN))
	{
		if (m_pMoveComponent->Update(m_pAStar, mAttribute, mInfo) == false)
		{
			mAttribute.mode = MODE::NEUTRAL;
		}
	}

	// Animation Frame Update
	ChangeMode();
	m_pMoveComponent->FrameCal(mAttribute, mFrame);

	if (mAttribute.bDie)
	{
		mAttribute.bCollision = false;
		mAttribute.bEXCollision = false;
		return OBJ_DIE;
	}


	return OBJ_NORMAL;
}

void Enemy::Render(void)
{
	m_pGraphicsComponent->Update(mFrame, mInfo);
	m_pGraphicsComponent->Render(mObjKey, mStateKey, m_pSprite, mFrame, mInfo);
}

void Enemy::Collision(void)
{
	m_pCollisionComponent->ObstacleCollision(ObjMgr::GetInstance()->GetObjSpace(OBJ_OBSTACLE));
	m_pCollisionComponent->MoveCollision(ObjMgr::GetInstance()->GetObjSpace(OBJ_ENEMY));
	m_pCollisionComponent->AttackCollision(ObjMgr::GetInstance()->GetObjSpace(OBJ_PLAYER));
}

void Enemy::ChangeMode()
{
	float speed = 0.f;

	if (mAttribute.mode == MODE::GETHIT || mAttribute.mode == MODE::SPECIAL_CAST 
		|| mAttribute.mode == MODE::SPECIAL || mAttribute.mode == MODE::FIRE_CAST || mAttribute.mode == MODE::ATTACK)
	{
		if ((int)mFrame.frame == (int)(mFrame.max - 1))
		{
			mAttribute.mode = MODE::NEUTRAL;
		}

		if (mAttribute.currentHP <= 0)
		{
			mAttribute.mode = MODE::DEATH;
		}
	}

	if (mAttribute.mode == MODE::DEATH)
	{
		if ((int)mFrame.frame == (int)(mFrame.max - 1))
		{
			if (mAttribute.type == DIABLO)
			{
				ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, ObjFactory<BuffSkill>::CreateEffect(TYREAL, mInfo.vPos, this));
			}
			mAttribute.bDie = true;
		}

		if (mAttribute.type == DIABLO)
		{
			if ((int)mFrame.frame == (int)(mFrame.max - 130))
			{
				SoundMgr::GetInstance()->StopAll();
				SoundMgr::GetInstance()->PlaySound(L"M_Diadeath.wav", BUTTON_SOUND);
			}
		}
		else if ((int)mFrame.frame == (int)(mFrame.max - 4))
		{
			if (mAttribute.type == DEMON || mAttribute.type == ANIMAL)
			{
				SoundMgr::GetInstance()->PlaySound(L"BearGethit.wav", ENEMY_SOUND);
			}
			else if (mAttribute.type == WRAITH)
			{
				SoundMgr::GetInstance()->PlaySound(L"M_CMdeath.wav", ENEMY_SOUND);
			}
			else if (mAttribute.type == COUNTESS)
			{
				SoundMgr::GetInstance()->PlaySound(L"M_Cdeath.wav", ENEMY_SOUND);
			}
			else
			{
				SoundMgr::GetInstance()->PlaySound(L"WolfGethit.wav", ENEMY_SOUND);
			}
		}
	}


	if (mAttribute.mode != mPreMode || mAttribute.frameDir != mPreFrameDir)
	{
		switch (mAttribute.mode)
		{
		case MODE::NEUTRAL:
			m_bMoveCheck = true;
			m_pAnimationState->FrameUpdate(mAttribute, mFrame, mStateKey);
			m_pMoveComponent->FrameCal(mAttribute, mFrame);
			mAttribute.bEXCollision = false;
			mAttribute.bCollision = false;
			break;
		case MODE::ATTACK:
		case MODE::SPECIAL:
		case MODE::SPECIAL_CAST:
		case MODE::FIRE_CAST:
			m_bMoveCheck = false;
			m_pAnimationState->FrameUpdate(mAttribute, mFrame, mStateKey);
			m_pMoveComponent->FrameCal(mAttribute, mFrame);
			break;
		case MODE::GETHIT:
			break;
		case MODE::TRANSFORM:
			m_bMoveCheck = false;
			break;
		case MODE::DEATH:
			m_bMoveCheck = false;
			m_pAnimationState->FrameUpdate(mAttribute, mFrame, mStateKey);
			m_pMoveComponent->FrameCal(mAttribute, mFrame);
			mAttribute.bEXCollision = false;
			mAttribute.bCollision = false;
			break;
		}

		m_pAnimationState->FrameUpdate(mAttribute, mFrame, mStateKey);

		mPreMode = mAttribute.mode;
		mPreFrameDir = mAttribute.frameDir;
	}
}

void Enemy::AttackDir(const D3DXVECTOR3 vSrcPos, const D3DXVECTOR3 vDestPos)
{
	mAttribute.degree = MathMgr::GetInstance()->CalDirDegree(vSrcPos, vDestPos);
}




void Enemy::SkillOperation(const int type)
{
	
	int frameNum  = mFrame.max - (int)mFrame.frameInit;

	int frame = (int)(mFrame.frame) % frameNum;
	float degree = 0.f;
	Obj* pObj = nullptr;

	int summonRand = rand() % 2;

	switch (type)
	{
	case COUNCIL:
		if (frame == 4)
		{
			for (int i = 0; i < 10; ++i)
			{
				pObj = ObjFactory<AttackSkill>::CreateEffect(STATIC_FIELD,
					MathMgr::GetInstance()->DegreePos(mInfo.vPos, m_pObj->GetInfo().vPos, 4.0f), this, ENEMY_KIND);
				ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pObj);
			}

			
		}

		break;
	case DEMON:
		if (frame == 7)
		{
			pObj = ObjFactory<AttackSkill>::CreateEffect(FIRE_BALL, m_pObj->GetInfo().vPos, this, ENEMY_KIND);
			ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pObj);
		}
		break;
	case FALLEN_SHAMON:
		if (frame == 14)
		{
			if (summonRand == 0)
			{
				Obj* pObj = ObjFactory<BuffSkill>::CreateEffect(REVIVE, m_pObj->GetInfo().vPos, nullptr, FALLEN);
				ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pObj);
			}

		}
		break;
	case DIABLO:
		if (mAttribute.mode == MODE::SPECIAL_CAST)
		{
			if (frame == 12)
			{
				if (summonRand == 0)
				{

					Obj* pObj = ObjFactory<BuffSkill>::CreateEffect(REVIVE, MathMgr::GetInstance()->CalPoint(), nullptr, WRAITH);
					ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pObj);
				}
			}
		}
		else if (mAttribute.mode == MODE::SPECIAL)
		{
			if (frame == 7)
			{
				pObj = ObjFactory<AttackSkill>::CreateEffect(DIA_INFERNO, m_pObj->GetInfo().vPos, this, ENEMY_KIND);
				ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, pObj);
			}
		}
		else if (mAttribute.mode == MODE::FIRE_CAST)
		{
			if (frame == 11)
			{
				for (int i = 0; i < 36; ++i)
				{
					pObj = ObjFactory<AttackSkill>::CreateEffect(DIABLO_FIRE, m_pMathMgr->Degree360(mInfo.vPos, degree), this, ENEMY_KIND);
					m_pObjMgr->AddObject(OBJ_EFFECT, pObj);


					degree += 10;
				}
			}
		}
		break;
	default:
		break;
	}

}

void Enemy::Release(void)
{
	SafeDelete<AStar*>(m_pAStar);
	SafeDelete<GraphicsComponent*>(m_pGraphicsComponent);
	SafeDelete<MoveComponent*>(m_pMoveComponent);
	SafeDelete<CollisionComponent*>(m_pCollisionComponent);
	SafeDelete<AnimState*>(m_pAnimationState);
	SafeDelete<MoveBehavior*>(m_pMoveBehaivor);
}
