#include "stdafx.h"
#include "EnemyMgr.h"
#include "Enemy.h"
#include "LifeObj.h"

IMPLEMENT_SINGLETON(EnemyMgr);

EnemyMgr::EnemyMgr()
{

}


EnemyMgr::~EnemyMgr()
{

}

void EnemyMgr::Initialize(const TCHAR * pFilePath, Obj* pPlayer)
{
	m_pPlayer = pPlayer;
	LoadData(pFilePath);
}

void EnemyMgr::LoadData(const TCHAR * pFilePath)
{
	HANDLE hFile = CreateFile(pFilePath, GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Enemy load failed!!!", L"Error!!!", MB_OK);
		return;
	}

	DWORD byte = 0;
	int type = 0;
	D3DXVECTOR3 vPos = { 0.f, 0.f, 0.f };
	int count = 0;
	while (true)
	{
		ReadFile(hFile, &type, sizeof(int), &byte, nullptr);
		ReadFile(hFile, &vPos, sizeof(D3DXVECTOR3), &byte, nullptr);

		if (byte == 0)
		{
			m_bEnemeyInit = true;
			break;
		}
		
		Obj* pEnemy = ObjFactory<Enemy>::CreateEnemy(vPos, m_pPlayer, type);
		ObjMgr::GetInstance()->AddObject(OBJ_ENEMY, pEnemy);	
	}
	CloseHandle(hFile);
}



void EnemyMgr::SetInfo(int type, ATTRIBUTE & attribute)
{
	switch (type)
	{
	case FALLEN:
		attribute.attack = 10;
		attribute.maxHP = 250;
		attribute.speed = 130;
		break;
	case FALLEN_SHAMON:
		attribute.attack = 10;
		attribute.maxHP = 350;
		attribute.speed = 120;
		break;
	case COUNCIL:
		attribute.attack = 25;
		attribute.maxHP = 400;
		attribute.speed = 130;
		break;
	case COUNTESS:
		attribute.attack = 30;
		attribute.maxHP = 450;
		attribute.speed = 130;
		break;
	case ANIMAL:
		attribute.attack = 30;
		attribute.maxHP = 400;
		attribute.speed = 130;
		break;
	case WRAITH:
		attribute.attack = 30;
		attribute.maxHP = 550;
		attribute.speed = 200;
		break;
	case DEMON:
		attribute.attack = 20;
		attribute.maxHP = 750;
		attribute.speed = 120;
		break;
	case DIABLO:
		attribute.attack = 100;
		attribute.maxHP = 15000;
		attribute.speed = 150;
		break;
	}
	attribute.currentHP = attribute.maxHP;
}

void EnemyMgr::Release()
{
}
