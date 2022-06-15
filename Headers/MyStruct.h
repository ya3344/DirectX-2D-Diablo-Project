#pragma once
#include "Enum.h"


typedef struct tagFrame
{
	tagFrame()
	{
		ZeroMemory(this, sizeof(tagFrame));
	}
	explicit tagFrame(float frameInit, float count, int max)
	{
		this->frameInit = frameInit;
		this->frame = frameInit;
		this->count = count;
		this->max = max;
	}

	float frameInit = 0.f;
	float frame = 0.f;
	float count = 0.f;
	int max = 0;

	int dirNum[(size_t)MODE::END] = {};

}FRAME;

typedef struct tagCollisionInfo
{
	tagCollisionInfo()
	{
		ZeroMemory(this, sizeof(tagCollisionInfo));
	}
	explicit tagCollisionInfo(float leftScale, float topScale, float rightScale, float bottomScale, LONG moveX = 0, LONG moveY = 0)
	{
		this->leftScale = leftScale;
		this->topScale = topScale;
		this->rightScale = rightScale;
		this->bottomScale = bottomScale;
		
		this->moveX = moveX;
		this->moveY = moveY;
	}

	RECT collisionRect;

	float leftScale = 0.f;
	float topScale = 0.f;
	float rightScale = 0.f;
	float bottomScale = 0.f;

	float collisionWidth = 0.f;
	float collisionHeight = 0.f;

	LONG moveX = 0;
	LONG moveY = 0;


}COLLISION_INFO;

typedef struct tagInfo
{
	tagInfo()
	{
		ZeroMemory(this, sizeof(tagInfo));
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixIdentity(&matScale);
		D3DXMatrixIdentity(&matTrans);
		//D3DXMatrixIdentity(&matRot);
	}

	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vLook;

	D3DXMATRIX matScale;
	D3DXMATRIX matTrans;
	//D3DXMATRIX matRot;
	D3DXMATRIX matWorld;

	float centerX = 0.f;
	float centerY = 0.f;

	COLLISION_INFO mCollisionInfo;
}INFO;



typedef struct tagAttribute
{
	tagAttribute()
	{
		ZeroMemory(this, sizeof(tagAttribute));
	};

	float maxHP = 0.f;
	float currentHP = 0.f;
	float maxMP = 0.f;
	float currentMP = 0.f;
	float maxSP = 0.f;
	float currentSP = 0.f;

	// LEVEL
	float nextEXP = 0;
	float currentEXP = 0;
	int Level = 1;

	// Stat
	int str = 0;
	int dex = 0;
	int life = 0;
	int energy = 0;

	float degree = 0.f;
	float speed = 0.f;

	float attack = 0.f;

	bool bDie = false;
	bool bCollision = false;
	bool bEXCollision = false;
	bool bSceneInit = true;

	MODE mode = MODE::END;
	int frameDir = 0;

	int type = HUMAN;
	int tileIndex = 0;

	D3DXVECTOR3 vDistance = { 0.f, 0.f, 0.f };

	int statPoint = 0;
	int skillPoint = 0;

	int FallenShamanCount = 0;
	int DiabloCount = 0;

}ATTRIBUTE;


typedef struct tagTileInfo
{
	tagTileInfo()
	{
		ZeroMemory(this, sizeof(tagTileInfo));
		D3DXMatrixIdentity(&matWorld);
	};
	explicit tagTileInfo(D3DXVECTOR3 vPos, D3DXVECTOR3 vSize, BYTE option, int drawID)
	{
		this->vPos = vPos;
		this->vSize = vSize;
		this->option = option;
		this->drawID = drawID;
	}

	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize;
	D3DXVECTOR3 vVertex[4];
	float gradiant[4];
	float intercept[4];

	D3DXMATRIX matWorld;

	BYTE option;
	int drawID;
	int preDrawID;

}TILE_INFO;

typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9 pTexture;
	D3DXIMAGE_INFO imgInfo;
}TEXTURE_INFO;


typedef struct tagUnitData
{
	tagUnitData()
	{
		ZeroMemory(this, sizeof(tagUnitData));
	};
	explicit tagUnitData(const TCHAR* pName, float HP, float attack, float speed)
	{
		lstrcpy(name, pName);
		this->HP = HP;
		this->attack = attack;
		this->speed = speed;
	}

	TCHAR name[32] = L"";
	float HP = 0.f;
	float attack = 0.f;
	float speed = 0.f;

}UNITDATA;

typedef struct tagAStarNode
{
	tagAStarNode() {};
	explicit tagAStarNode(float cost, int index, tagAStarNode* pParent, DIRECTION dir = DIRECTION::DOWN)
	{
		this->cost = cost;
		this->index = index;
		this->pParent = pParent;
		this->dir = dir;
	}

	float cost = 0.f;
	int index = 0;
	tagAStarNode* pParent = nullptr;
	DIRECTION dir = DIRECTION::DOWN;

}ASTAR_NODE;


typedef struct tagImgInfo
{
	wstring objKey = L"";
	wstring stateKey = L"";
	wstring path = L"";
	int count = 0;

}IMG_INFO;

typedef struct tagRectangle {
	float x, y, z, w; //D3DFVF_XYZRHW 위치정보
	D3DCOLOR color; //D3DFVF_DIFFUSE 색깔
} RECTANGLE;