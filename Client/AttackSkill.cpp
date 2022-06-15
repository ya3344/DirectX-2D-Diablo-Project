#include "stdafx.h"
#include "AttackSkill.h"
#include "Player.h"

AttackSkill::AttackSkill()
{
	m_vTargetPos = { 0.f, 0.f, 0.f };
	m_vTargetDir = { 0.f, 0.f, 0.f };
	m_vRandomPos = { 0.f, 0.f, 0.f };
}


AttackSkill::~AttackSkill()
{
	
}

HRESULT AttackSkill::Initialize(int type, int enemyType)
{
	if (ObjMgr::GetInstance()->GetObj(OBJ_PLAYER) != nullptr)
	{
		m_pPlayer = ObjMgr::GetInstance()->GetObj(OBJ_PLAYER);
	}

	mEnemyType = enemyType;

	int dir = 0;

	switch (type)
	{
	case BOULDER_ROLL:
		m_vTargetPos = mInfo.vPos;
		mInfo.vPos = m_pTargetObj->GetInfo().vPos;
		SetInfo(type, L"BoulderRoll", FRAME(0.f, 80 * 2.f, 80));
		SetAttribute(true, 0, m_pTargetObj->GetAttribute().attack * 0.2f, 6000);
		break;
	case BOULDER_EMERGE:
		m_vTargetPos = mInfo.vPos;
		mInfo.vPos = m_pTargetObj->GetInfo().vPos;
		SetInfo(type, L"BoulderEmerge", FRAME(0.f, 47 * 0.5f, 47));
		SetAttribute(true, 0, m_pTargetObj->GetAttribute().attack * 0.2f, 5000);
		SoundMgr::GetInstance()->PlaySound(L"explode1.wav", EFFECT_SOUND);
		break;
	case TWISTER:
		m_vTargetPos = mInfo.vPos;
		m_vTargetDir = MathMgr::GetInstance()->CalTargetDir(m_pTargetObj->GetInfo().vPos, m_vTargetPos);
		mInfo.vPos = m_pTargetObj->GetInfo().vPos + (m_vTargetDir * 40);
		SetInfo(type, L"Twister", FRAME(0.f, 40 * 2.0f, 40));
		SetAttribute(true, 0, m_pTargetObj->GetAttribute().attack * 0.2f, 8000);
		break;
	case GROUND_FIRE:
		SetInfo(type, L"GroundFire", FRAME(0.f, 37 * 2.f, 37));
		SetAttribute(false, 3, m_pTargetObj->GetAttribute().attack * 0.05f, 9000);
	
		break;
	case DIABLO_FIRE:
		m_vTargetPos = mInfo.vPos;
		mInfo.vPos = m_pTargetObj->GetInfo().vPos;
		m_vTargetDir = MathMgr::GetInstance()->CalTargetDir(mInfo.vPos, m_vTargetPos);
		SetInfo(type, L"GroundFire", FRAME(0.f, 37.f * 3.f, 37));
		SetAttribute(false, 2, m_pTargetObj->GetAttribute().attack * 0.1f, 6000);
		SoundMgr::GetInstance()->PlaySound(L"M_Diafire.wav", BOSS_SOUND);
		break;
	case FIRE_BALL:
		m_vTargetPos = mInfo.vPos;
		mInfo.vPos = m_pTargetObj->GetInfo().vPos;
		m_vTargetDir = MathMgr::GetInstance()->CalTargetDir(mInfo.vPos, m_vTargetPos);
	
		DirAttack(mInitFrame, FIRE_BALL_FRAME, mMaxFrame, 0.f, 16);
		mInfo.vPos.y += 20;
		D3DXMatrixScaling(&mInfo.matScale, 1.5f, 1.5f, 0.f);
		SetInfo(type, L"FireBall", FRAME(mInitFrame, FIRE_BALL_FRAME * 3.f, mMaxFrame));
		SetAttribute(false, 4, m_pTargetObj->GetAttribute().attack * 0.05f, 9000);
		SoundMgr::GetInstance()->PlaySound(L"explode3.wav", EFFECT_SOUND);
		break;

	case DIA_INFERNO:
		m_vTargetPos = mInfo.vPos;
		mInfo.vPos = m_pTargetObj->GetInfo().vPos;
		m_vTargetDir = MathMgr::GetInstance()->CalTargetDir(mInfo.vPos, m_vTargetPos);
		DirAttack(mInitFrame, DIA_INFERNO_FRAME, mMaxFrame, 0.f, 8);
		D3DXMatrixScaling(&mInfo.matScale, 1.5f, 1.5f, 0.f);
		SetInfo(type, L"DiaInferno", FRAME(mInitFrame, DIA_INFERNO_FRAME * 3.f, mMaxFrame));
		SetAttribute(false, 4, m_pTargetObj->GetAttribute().attack * 0.2f, 8000);
		SoundMgr::GetInstance()->PlaySound(L"M_Diared.wav", BOSS_SOUND);
	
		break;

	case ARMA_EXPLOSION:
		SetInfo(type, L"ArmaExplosion", FRAME(0.f, 16 * 2.f, 16));
		SetAttribute(false, 1, m_pTargetObj->GetAttribute().attack * 0.1f, 5000);
		SoundMgr::GetInstance()->PlaySound(L"explode2.wav", EFFECT_SOUND);
		break;
	case BOULDER_EXPOLDE:
		SetInfo(type, L"BoulderExplode", FRAME(0.f, 13 * 1.5f, 13));
		SetAttribute(false, 1, m_pTargetObj->GetAttribute().attack * 0.1f, 8000);
		SoundMgr::GetInstance()->PlaySound(L"F_Hit1.wav", EFFECT_SOUND);
		break;
	case VOL_BASE:
		SetInfo(type, L"VolBase", FRAME(0.f, 20.f, 10));
		SetAttribute(false, 5, m_pTargetObj->GetAttribute().attack * 0.0f, 9000);
		break;
	case VOL_FIRE:
		SetInfo(type, L"VolFire", FRAME(0.f ,10.f, 5));
		SetAttribute(false, 5, m_pTargetObj->GetAttribute().attack * 0.1f, 9000);
		mInfo.vPos.y -= 40;
		mInfo.vPos.x -= 3;
		break;
	case VOL_ROCK:
		SetInfo(type, L"VolRock", FRAME(0.f, 14.f * 3.f, 14));
		mRandDistance = (rand() % 13) - 5;
		SetAttribute(true, 0, m_pTargetObj->GetAttribute().attack * 0.1f, 8000);
		break;
	case VOL_LAVAEXPLOSION:
		SetInfo(type, L"VolLavaExplosion", FRAME(0.f, 18.f * 3.f, 18));
		SetAttribute(false, 1, m_pTargetObj->GetAttribute().attack * 0.1f, 8000);

		break;
	case VOL_LAVAPOOL:
		SetInfo(type, L"VolLavaPool", FRAME(0.f, 18.f * 3.f, 18));
		SetAttribute(false, 1, m_pTargetObj->GetAttribute().attack * 0.1f, 8000);
		break;
	case METEOR_READY:
		SetInfo(type, L"MeteorReady", FRAME(0.f, 16.f * 2.f, 16));
		SetAttribute(false, 3, m_pTargetObj->GetAttribute().attack * 0.f, 10000);
		
		break;
	case METEOR:
		m_vTargetPos = D3DXVECTOR3(mInfo.vPos.x - 350, mInfo.vPos.y + 800, 0.f);
		SetInfo(type, L"Meteor", FRAME(0.f, 15.f * 2.f, 15));
		SetAttribute(true, 0, m_pTargetObj->GetAttribute().attack * 0.f, 10000);
		break;
	case INFERNO:
		D3DXMatrixScaling(&mInfo.matScale, 3.f, 3.f, 0.f);
		SetInfo(type, L"Inferno", FRAME(0.f, 14 * 2.5f, 14));
		SetAttribute(false, 1, m_pTargetObj->GetAttribute().attack * 0.1f, 3000);
		SoundMgr::GetInstance()->PlaySound(L"F_Hit1.wav", EFFECT_SOUND);
		break;
	case STATIC_FIELD:
		m_vTargetPos = mInfo.vPos;
		mInfo.vPos = m_pTargetObj->GetInfo().vPos;
		SetInfo(type, L"StaticField", FRAME(0.f, 19 * 2.5f, 19));
		SetAttribute(true, 0, m_pTargetObj->GetAttribute().attack * 0.1f, 7000);
		SoundMgr::GetInstance()->PlaySound(L"L_Cast.wav", ENEMY_SOUND);
		break;
	default:
		m_bForever = false;
		mSkillCount = 0;
		break;
	}

	return S_OK;
}

int AttackSkill::Update()
{
	if (Skill() == false)
		return OBJ_DIE;
	
	mFrame.frame += mFrame.count * TimeMgr::GetInstance()->GetTime();

	if (m_bForever)
	{
		if (mFrame.frame > mFrame.max)
		{
			mFrame.frame = mFrame.frameInit;
		}
	}
	else
	{
		if (mFrame.frame > mFrame.max)
		{
			--mSkillCount;
			mFrame.frame = mFrame.frameInit;
			if (mSkillCount == 0)
				return OBJ_DIE;
		}
	}
	D3DXMatrixTranslation(&mInfo.matTrans, mInfo.vPos.x + ScrollMgr::GetInstance()->GetScrollX(), mInfo.vPos.y + ScrollMgr::GetInstance()->GetScrollY(), 0.f);

	return OBJ_NORMAL;
}

void AttackSkill::Render(void)
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
	
	m_pSprite->SetTransform(&mInfo.matWorld);
	m_pSprite->Draw(m_pTextureInfo->pTexture, nullptr
		, &D3DXVECTOR3(mInfo.centerX, mInfo.centerY, 0.f)
		, nullptr, mColor);

	m_pSprite->End();
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	

	Collision();
}

void AttackSkill::Collision(void)
{
	// Collision Rect Setting
	if (mType == BOULDER_EXPOLDE || mType == ARMA_EXPLOSION)
	{
		mInfo.mCollisionInfo = COLLISION_INFO(0.4f, 0.4f, 0.4f, 0.4f );
	}
	else if (mType == TWISTER)
	{
		if (mScale >= 2.5f)
		{
			mInfo.mCollisionInfo = COLLISION_INFO(1.2f, 1.2f, 1.2f, 1.2f);
		}
		else
		{
			mInfo.mCollisionInfo = COLLISION_INFO(0.8f, 0.8f, 0.8f, 0.8f);
		}
		
	}
	else if (mType == INFERNO)
	{
		mInfo.mCollisionInfo = COLLISION_INFO(2.0f, 1.5f, 1.5f, 1.5f);
	}
	else
	{
		mInfo.mCollisionInfo = COLLISION_INFO(0.7f, 0.7f, 0.7f, 0.7f);
	}
	
	CollisionMgr::SetCollisionRect(mInfo, m_pTextureInfo);

	DebugMgr::GetInstance()->DrawRectange((float)mInfo.mCollisionInfo.collisionRect.left, (float)mInfo.mCollisionInfo.collisionRect.top,
		mInfo.mCollisionInfo.collisionWidth, mInfo.mCollisionInfo.collisionHeight);



	if (mEnemyType >= ENEMY_KIND)
	{
		if (CollisionMgr::CheckRect(mInfo.mCollisionInfo, m_pPlayer->GetInfo().mCollisionInfo))
		{
			if (mType == FIRE_BALL)
			{
				m_bFireBall = true;
			}

			mAttackPercent = (rand() % 10000) + 1;

			if (mAttackPercent <= mAttackStaticPercent)
				return;

			if (m_pPlayer->GetAttribute().currentHP > 0)
				m_pPlayer->SetPlayerDamage(mAttack);
		}
	}
	else
	{
		for (Obj* pObj : ObjMgr::GetInstance()->GetObjSpace(OBJ_ENEMY))
		{
			if (CollisionMgr::CheckRect(mInfo.mCollisionInfo, pObj->GetInfo().mCollisionInfo))
			{

				mAttackPercent = (rand() % 10000) + 1;

				if (mAttackPercent <= mAttackStaticPercent)
					break;

				if (pObj->GetAttribute().currentHP > 0)
					pObj->SetEnemyDamage(mAttack);
			}
		}
	}
	
}

bool AttackSkill::Skill()
{
	switch (mType)
	{
	case BOULDER_ROLL:
	case BOULDER_EMERGE:
		Roll();
		break;
	case TWISTER:
		Twister(FRAME(10.f, 23.f, 32), FRAME(33.f, 8.f, 40));
		break;
	case VOL_BASE:
		Volcano(FRAME(11.f, 16.f, 18), FRAME(19.f, 22.f, 29));
		break;
	case VOL_FIRE:
		Volcano(FRAME(5.f, 24.f, 12), FRAME(13.f, 34.f, 29));
		break;
	case VOL_ROCK:
		Rock();
		break;
	case METEOR:
		Meteor();
		break;
	case METEOR_READY:
		MeteorReady();
		break;
	case GROUND_FIRE:
		GroundFire(FRAME(9.f, 54.f, 36), FRAME(9.f, 54.f, 36));
		break;
	case DIABLO_FIRE:
		DiabloFire(FRAME(9.f, 54.f, 36));
		break;
	case STATIC_FIELD:
		StaticField();
		break;
	case DIA_INFERNO:
		//m_bOperation = true;
		DiaInferno();
		break;
	case FIRE_BALL:
		mInfo.vPos += m_vTargetDir * 600 * TimeMgr::GetInstance()->GetTime();

		if (m_bFireBall)
		{
			ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, ObjFactory<AttackSkill>::CreateEffect(INFERNO, mInfo.vPos, m_pTargetObj, ENEMY_KIND));
			ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, ObjFactory<AttackSkill>::CreateEffect(ARMA_EXPLOSION, mInfo.vPos, m_pTargetObj, ENEMY_KIND));
			m_bOperation = false;
		}
		else
		{
			m_bOperation = true;
		}
	
		
		break;
	default:
		m_bOperation = true;
		break;
	}

	if (m_bOperation == false)
		return false;

	return true;
}

void AttackSkill::SetInfo(const int type, const TCHAR * pStateKey, FRAME frame, float durationTime, float attack)
{
	SkillBridge::SetInfo(type, pStateKey, frame, durationTime, attack);
}

void AttackSkill::SetAttribute(bool bForever, int skillCount, float attack, int attackPercent)
{
	m_bForever = bForever;
	mMaxSkillCount = skillCount;
	mSkillCount = mMaxSkillCount;
	mAttack = attack;
	mAttackStaticPercent = attackPercent;
}

void AttackSkill::Roll()
{
	m_vTargetDir = MathMgr::GetInstance()->CalTargetDir( mInfo.vPos, m_vTargetPos);

	mInfo.vPos += m_vTargetDir * 250 * TimeMgr::GetInstance()->GetTime();
	mTargetDistance = MathMgr::GetInstance()->CalDistance(mInfo.vPos, m_vTargetPos);
	
	if((int)(mTargetDistance) % 5 == 3 )
		ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, ObjFactory<AttackSkill>::CreateEffect(GROUND_FIRE, mInfo.vPos, m_pTargetObj));
	
	if (mTargetDistance <= 3.f)
	{
		ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, ObjFactory<AttackSkill>::CreateEffect(BOULDER_EXPOLDE, mInfo.vPos, m_pTargetObj));
		ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, ObjFactory<AttackSkill>::CreateEffect(ARMA_EXPLOSION, mInfo.vPos, m_pTargetObj));
		m_bOperation = false;
	}
	else
	{
		m_bOperation = true;
	}
}
void AttackSkill::Meteor()
{
	m_vTargetDir = MathMgr::GetInstance()->CalTargetDir(mInfo.vPos, m_vTargetPos);

	mInfo.vPos += m_vTargetDir * 1000 * TimeMgr::GetInstance()->GetTime();
	mTargetDistance = MathMgr::GetInstance()->CalDistance(mInfo.vPos, m_vTargetPos);

	if (mTargetDistance <= 7.f)
	{
		ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, ObjFactory<AttackSkill>::CreateEffect(INFERNO, mInfo.vPos, m_pTargetObj));
		ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, ObjFactory<AttackSkill>::CreateEffect(ARMA_EXPLOSION, mInfo.vPos, m_pTargetObj));

		ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, ObjFactory<AttackSkill>::CreateEffect(GROUND_FIRE,
			D3DXVECTOR3(mInfo.vPos.x, mInfo.vPos.y, 0.f), m_pTargetObj));
		ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, ObjFactory<AttackSkill>::CreateEffect(GROUND_FIRE, 
			D3DXVECTOR3( mInfo.vPos.x+25, mInfo.vPos.y, 0.f), m_pTargetObj));
		ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, ObjFactory<AttackSkill>::CreateEffect(GROUND_FIRE,
			D3DXVECTOR3(mInfo.vPos.x, mInfo.vPos.y + 15, 0.f), m_pTargetObj));

		ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, ObjFactory<AttackSkill>::CreateEffect(GROUND_FIRE,
			D3DXVECTOR3(mInfo.vPos.x +25, mInfo.vPos.y +15, 0.f), m_pTargetObj));
		m_bOperation = false;
	}
	else
	{
		m_bOperation = true;
	}

}

void AttackSkill::MeteorReady()
{
	if (mSkillCount == 1)
	{
		if (mFrame.frame > mFrame.max - 1)
		{
			ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, ObjFactory<AttackSkill>::CreateEffect(METEOR, 
				D3DXVECTOR3(mInfo.vPos.x + 350, mInfo.vPos.y - 800.f, 0.f), m_pTargetObj));
		}
	}
	m_bOperation = true;
}


void AttackSkill::Twister(FRAME midFrame, FRAME endFrame)
{
	m_vTargetDir = MathMgr::GetInstance()->CalTargetDir(mInfo.vPos, m_vTargetPos);

	mTime = TimeMgr::GetInstance()->GetTime();

	mRandDistance = rand() % 1000;

	if (mScale <= 2.5f)
	{
		mScale += mTime * 1.0f;
	}
	else
	{
		mScale = 2.5f;
	}
	
	D3DXMatrixScaling(&mInfo.matScale, mScale, mScale, 0.f);
	

	if (mScale >= 2.5f)
	{
		mInfo.vPos.x += m_vTargetDir.x * 200 * mTime;
		mInfo.vPos.y += m_vTargetDir.y * 200 * mTime;

		if (mTwisterTime >= 0)
		{
			mTwisterTime += mTime * 10;

			if (roundf(m_vTargetDir.x) == 0.f)
			{
				mInfo.vPos.x -= m_vTargetDir.x * 250 * mTime;
			}
			else
			{
				mInfo.vPos.y -= m_vTargetDir.y * 250 * mTime;
			}
			

		//	cout << mTwisterTime << endl;
			if (mTwisterTime >= 5.f)
			{
				mTwisterTime = -5.f;
			}
		}
		else
		{
			mTwisterTime -= mTime * 10;

			if (roundf(m_vTargetDir.x) == 0.f)
			{
				mInfo.vPos.x += m_vTargetDir.y * 250 * mTime;
			}
			else
			{
				mInfo.vPos.y += m_vTargetDir.y * 250 * mTime;
			}
		
			if (mTwisterTime <= -10.f)
			{
				mTwisterTime = 0.f;
			}
		}
	}
	else
	{
		mInfo.vPos += m_vTargetDir * 5.f * mTime;
		
	}

	mTargetDistance = MathMgr::GetInstance()->CalDistance(mInfo.vPos, m_vTargetPos);

	if (mFrame.frame > midFrame.frameInit)
	{
		if (mPreFrameInit != mFrame.frameInit)
		{
			mFrame = midFrame;
			mPreFrameInit = mFrame.frameInit;
		}
	}
	else if (mTargetDistance <= 2.5f)
	{
		if (mPreFrameInit != mFrame.frameInit)
		{
			mFrame = endFrame;
			mPreFrameInit = mFrame.frameInit;
		}
	}
	else
	{
		if (mTargetDistance <= 3.0f)
		{
			mPreFrameInit = -1.f;
		}
	}


	if (mTargetDistance <= 2.f)
	{
		m_bOperation = false;
	}
	else
	{
		m_bOperation = true;
	}

}

void AttackSkill::Rock()
{
	m_vTargetDir = MathMgr::GetInstance()->CalTargetDir(mInfo.vPos, m_vTargetPos);
	
	mTime += 3.0f * TimeMgr::GetInstance()->GetTime();
	
	// -7  ~ 7 

	mInfo.vPos.x += mRandDistance * cosf(90) * mTime;
	mInfo.vPos.y -= 10.f * sinf(90) *mTime - (0.5f * 9.8f * mTime * mTime);

	m_bOperation = true;

	int randDie = ((mRandDistance + 7) % 3) + 1;

	if (mTime >= randDie)
	{
		ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, ObjFactory<AttackSkill>::CreateEffect(VOL_LAVAEXPLOSION, mInfo.vPos, m_pTargetObj));
		ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, ObjFactory<AttackSkill>::CreateEffect(VOL_LAVAPOOL, mInfo.vPos, m_pTargetObj));
		m_bOperation = false;

	}
}

void AttackSkill::Volcano(FRAME midFrame, FRAME endFrame)
{
	if (mSkillCount == mMaxSkillCount - 1)
	{
		if (mPreFrameInit != mFrame.frameInit)
		{
			
			mFrame = midFrame;
			mPreFrameInit = mFrame.frameInit;
		}

		if ((int)(mFrame.frame) % 8 == 1)
		{
			ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, ObjFactory<AttackSkill>::CreateEffect(VOL_ROCK, mInfo.vPos, m_pTargetObj));
		}
	}
	else if (mSkillCount == 1)
	{
		if (mPreFrameInit != mFrame.frameInit)
		{
			mFrame = endFrame;
			mPreFrameInit = mFrame.frameInit;
		}
	}
	else
	{
		mPreFrameInit = -1;

		if ((int)(mFrame.frame) % 8 == 1)
		{
			ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, ObjFactory<AttackSkill>::CreateEffect(VOL_ROCK, mInfo.vPos, m_pTargetObj));
		}
	}
	
	
	

	m_bOperation = true;
}

void AttackSkill::GroundFire(FRAME midFrame, FRAME endFrame)
{
	if (mSkillCount == mMaxSkillCount - 1)
	{
		if (mPreFrameInit != mFrame.frameInit)
		{

			mFrame = midFrame;
			mPreFrameInit = mFrame.frameInit;
		}
	}
	else if (mSkillCount == 1)
	{
		if (mPreFrameInit != mFrame.frameInit)
		{
			mFrame = endFrame;
			mPreFrameInit = mFrame.frameInit;
		}
	}
	else
	{
		mPreFrameInit = -1;
	}


	m_bOperation = true;
}

void AttackSkill::StaticField()
{
	m_vTargetDir = MathMgr::GetInstance()->CalTargetDir(mInfo.vPos, m_vTargetPos);

	mInfo.vPos += m_vTargetDir * 300 * TimeMgr::GetInstance()->GetTime();
	mTargetDistance = MathMgr::GetInstance()->CalDistance(mInfo.vPos, m_vTargetPos);

	if (mTargetDistance <= 7.f)
	{
		m_bOperation = false;
	}
	else
	{
		m_bOperation = true;
	}

}

void AttackSkill::DiabloFire(FRAME midFrame)
{
	if (mSkillCount == mMaxSkillCount - 1)
	{
		if (mPreFrameInit != mFrame.frameInit)
		{
			
			mFrame = midFrame;
			mPreFrameInit = mFrame.frameInit;
		}
	}


	mInfo.vPos += m_vTargetDir * 400 * TimeMgr::GetInstance()->GetTime();
	mTargetDistance = MathMgr::GetInstance()->CalDistance(mInfo.vPos, m_vTargetPos);


	m_bOperation = true;
	
}

void AttackSkill::DirAttack(float& initFrame, int count, int& maxFrame, float distance, int dirNum)
{
	float degree = 0.f;
	int dir = 0;
	float calDegree = 0.f;

	degree = MathMgr::GetInstance()->CalDirDegree(mInfo.vPos, m_vTargetPos);
	dir = MathMgr::GetInstance()->CalFrame(dirNum, degree);
	calDegree = (degree / (360.f / dirNum)) * (360.f / dirNum);

	initFrame = (float)(dir * count);
	maxFrame = dir *count + count;

	//m_vTargetDir = MathMgr::GetInstance()->CalTargetDir(m_pTargetObj->GetInfo().vPos, mInfo.vPos);
	mInfo.vPos.x = m_pTargetObj->GetInfo().vPos.x + cosf(D3DXToRadian(calDegree)) *distance;
	mInfo.vPos.y = m_pTargetObj->GetInfo().vPos.y -sinf(D3DXToRadian(calDegree)) *distance;
}

void AttackSkill::DiaInferno()
{
	mInfo.vPos += m_vTargetDir * 600 * TimeMgr::GetInstance()->GetTime();
	m_bOperation = true;
}

void AttackSkill::Release(void)
{

}
