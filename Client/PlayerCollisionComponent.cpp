#include "stdafx.h"
#include "PlayerCollisionComponent.h"


PlayerCollisionComponent::PlayerCollisionComponent()
{
	PlayAttackFrame();
}


PlayerCollisionComponent::~PlayerCollisionComponent()
{

}

void PlayerCollisionComponent::Initialize(Obj* pSrc)
{
	m_pSrc = pSrc;
}

void PlayerCollisionComponent::ObstacleCollision(const list<Obj*>& objSpace)
{
	CollisionComponent::ObstacleCollision_Common(m_pSrc, objSpace);
}

void PlayerCollisionComponent::MoveCollision(const list<Obj*>& objSpace)
{
	float moveX = 0.f;
	float moveY = 0.f;

	for (Obj* pObj : objSpace)
	{
		if (m_pSrc->GetAttribute().bDie == true || pObj->GetAttribute().bDie == true)
			continue;

		if (CollisionMgr::CheckRect(m_pSrc->GetInfo().mCollisionInfo, pObj->GetInfo().mCollisionInfo))
		{
			m_pSrc->SetCollision(true);
			pObj->SetCollision(true);
			pObj->SetTarget(m_pSrc);
		}
		else
		{
			if (pObj->GetAttribute().bCollision && pObj->GetTarget() == m_pSrc)
			{
				m_pSrc->SetCollision(false);
				pObj->SetCollision(false);
				pObj->SetTarget(nullptr);
				//cout << "E: Collision: " << pObj->GetAttribute().bCollision << endl;
				//cout << "P: Collision: " << pObj->GetAttribute().bCollision << endl;
			}
		}

		//if (CollisionMgr::CheckRectEX(m_pSrc->GetInfo(), pObj->GetInfo(), moveX, moveY))
		//{
		//	if (moveX < moveY)
		//	{
		//		if (m_pSrc->GetInfo().vPos.x > pObj->GetInfo().vPos.x)
		//		{
		//			moveX *= -0.5f;
		//		}
		//		pObj->SetPos(D3DXVECTOR3(pObj->GetInfo().vPos.x + (moveX), pObj->GetInfo().vPos.y, 0.f));
		//	}
		//	else if (moveX > moveY)
		//	{
		//		if (m_pSrc->GetInfo().vPos.y > pObj->GetInfo().vPos.y)
		//		{
		//			moveY *= -0.5f;
		//		}
		//		pObj->SetPos(D3DXVECTOR3(pObj->GetInfo().vPos.x, pObj->GetInfo().vPos.y + (moveY), 0.f));
		//	}

	

		//	//cout << "E: Collision: " << pObj->GetAttribute().bCollision << endl;
		//	//cout << "P: Collision: " << pObj->GetAttribute().bCollision << endl;
		//}
		
	}
}

void PlayerCollisionComponent::AttackCollision(const list<Obj*>& objSpace)
{
	for (Obj* pObj : objSpace)
	{
		if (CollisionMgr::CheckRect(m_pSrc->GetInfo().mCollisionInfo, pObj->GetInfo().mCollisionInfo))
		{
			if (m_pSrc->GetAttribute().mode == MODE::ATTACK)
			{
				mAttackPercent = (rand() % 10000) + 1;

				if (mAttackPercent <= 7000)
					continue;

				mFrameNum = m_pSrc->GetFrame().max - (int)m_pSrc->GetFrame().frameInit;

				mFrame = (int)(m_pSrc->GetFrame().frame) % mFrameNum;


				if (mFrame >= mAttackFrame[m_pSrc->GetAttribute().type][START] &&
					mFrame <= mAttackFrame[m_pSrc->GetAttribute().type][END])
				{
					if(pObj->GetAttribute().currentHP > 0)
						pObj->SetEnemyDamage(m_pSrc->GetAttribute().attack);
				}
			}
		}
	}
}

void PlayerCollisionComponent::PlayAttackFrame()
{
	mAttackFrame[HUMAN][START] = 7;
	mAttackFrame[HUMAN][END] = 8;
	mAttackFrame[BEAR][START] = 7;
	mAttackFrame[BEAR][END] = 8;
	mAttackFrame[WOLF][START] = 7;
	mAttackFrame[WOLF][END] = 8;
}
