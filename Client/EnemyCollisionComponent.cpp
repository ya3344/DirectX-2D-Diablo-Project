#include "stdafx.h"
#include "EnemyCollisionComponent.h"


EnemyCollisionComponent::EnemyCollisionComponent()
{
	EnemyAttackFrame();
}


EnemyCollisionComponent::~EnemyCollisionComponent()
{
}

void EnemyCollisionComponent::Initialize(Obj * pSrc)
{
	m_pSrc = pSrc;
}

void EnemyCollisionComponent::ObstacleCollision(const list<Obj*>& objSpace)
{
	CollisionComponent::ObstacleCollision_Common(m_pSrc, objSpace);

}

void EnemyCollisionComponent::MoveCollision(const list<Obj*>& objSpace)
{
	float moveX = 0.f;
	float moveY = 0.f;

	for (Obj* pObj : objSpace)
	{
		// 같은 개체끼리는 검사하지 않는다.
		if (m_pSrc == pObj)
			continue;

		if (m_pSrc->GetAttribute().bDie == true || pObj->GetAttribute().bDie == true)
			continue;

		if (CollisionMgr::CheckRectEX(m_pSrc->GetInfo(), pObj->GetInfo(), moveX, moveY))
		{
			if (moveX < moveY)
			{
				if (m_pSrc->GetInfo().vPos.x > pObj->GetInfo().vPos.x)
				{
					moveX *= -1.f;
				}
				pObj->SetPos(D3DXVECTOR3(pObj->GetInfo().vPos.x + (moveX), pObj->GetInfo().vPos.y, 0.f));
			}
			else if(moveX > moveY)
			{
				if (m_pSrc->GetInfo().vPos.y > pObj->GetInfo().vPos.y)
				{
					moveY *= -1.f;
				}
				pObj->SetPos(D3DXVECTOR3(pObj->GetInfo().vPos.x, pObj->GetInfo().vPos.y + (moveY), 0.f));
			}

			//if (m_pSrc->GetAttribute().bCollision || pObj->GetAttribute().bCollision)
			//{
				m_pSrc->SetEXCollision(true);
				pObj->SetEXCollision(true);
			//}

		/*	cout << "SrcCol: " << m_pSrc->GetAttribute().bEXCollision << endl;
			cout << "destCol: " << pObj->GetAttribute().bEXCollision << endl;*/
		}
		else
		{

		}
	}

}

void EnemyCollisionComponent::AttackCollision(const list<Obj*>& objSpace)
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
					//cout << frame << endl;
					pObj->SetPlayerDamage(m_pSrc->GetAttribute().attack);
				
				}
			}
		}
	}
}


void EnemyCollisionComponent::EnemyAttackFrame()
{
	mAttackFrame[FALLEN][START] = 7;
	mAttackFrame[FALLEN][END] = 8;
	mAttackFrame[COUNCIL][START] = 3;
	mAttackFrame[COUNCIL][END] = 4;
	mAttackFrame[COUNTESS][START] = 10;
	mAttackFrame[COUNTESS][END] = 11;
}

