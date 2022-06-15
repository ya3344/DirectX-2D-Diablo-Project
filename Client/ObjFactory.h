#pragma once

#include "Obj.h"
#include "ObjBridge.h"
#include "Enemy.h"

template <typename T>
class ObjFactory
{
public:
	static Obj* CreateObj()
	{
		Obj* pObj = new T;
		if (FAILED(pObj->Initialize()))
		{
			SafeDelete<Obj*>(pObj);
		}

		return pObj;
	}

	static Obj* CreateObj(const D3DXVECTOR3& vPos)
	{
		Obj* pObj = new T;
		pObj->SetPos(vPos);
		if (FAILED(pObj->Initialize()))
		{
			SafeDelete<Obj*>(pObj);
		}

		return pObj;
	}

	static Obj* CreateEnemy(const D3DXVECTOR3& vPos, Obj* pPlayer, const int type)
	{
		Obj* pObj = new T;
		pObj->SetPos(vPos);
		dynamic_cast<Enemy*>(pObj)->SetType(type);
		EnemyMgr::GetInstance()->SetInfo(type, pObj->GetAttribute());
		if (pPlayer != nullptr)
		{
			pObj->SetObj(pPlayer);
		}
	
		if (FAILED(pObj->Initialize()))
		{
			SafeDelete<Obj*>(pObj);
		}

		return pObj;
	}

	static Obj* CreateUI(const D3DXVECTOR3& vPos, const int drawID, const int type =0)
	{
		Obj* pObj = new T;
		pObj->SetPos(vPos);
		pObj->SetDrawID(drawID);
		dynamic_cast<UI*>(pObj)->SetType(type);

		if (FAILED(pObj->Initialize()))
		{
			SafeDelete<Obj*>(pObj);
		}

		return pObj;
	}

	static Obj* CreateEffect(int type, const D3DXVECTOR3& vPos, Obj* pTargetObj, int enemyType = 0, D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255))
	{
		Obj* pObj = new ObjBridge;
		Bridge*	pBridge = new T;

		pObj->SetBridge(pBridge);
		pObj->SetObjKey(L"Skill");
		pBridge->SetPos(vPos);
		pBridge->SetColor(color);
		pBridge->SetTargetObj(pTargetObj);

		if (FAILED(pObj->Initialize()))
			return nullptr;

		if (FAILED(pBridge->Initialize(type, enemyType)))
			return nullptr;

		return pObj;
	}
};