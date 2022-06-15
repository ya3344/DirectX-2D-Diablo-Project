#include "stdafx.h"
#include "TileMgr.h"
#include "Tile.h"
#include "Obstacle.h"
IMPLEMENT_SINGLETON(TileMgr);



TileMgr::TileMgr()
{
	m_vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_vPortalPos = D3DXVECTOR3(0.f, 0.f, 0.f);
}


TileMgr::~TileMgr()
{
	//Release();
}

void TileMgr::Initialize(const TCHAR* pFilePath)
{
	LoadData(pFilePath);
}

void TileMgr::Update()
{
	if (KeyMgr::GetInstance()->KeyDown(KEY_D))
	{
		m_bDraw = !m_bDraw;
	}
	if (KeyMgr::GetInstance()->KeyDown(KEY_F))
	{
		g_bFontDraw = !g_bFontDraw;
	}
	if (KeyMgr::GetInstance()->KeyDown(KEY_C))
	{
		g_bCollingDraw = !g_bCollingDraw;
	}
}

void TileMgr::Render()
{
	if (m_bTileInit == false)
		return;

	float scrollX = ScrollMgr::GetInstance()->GetScrollX();
	float scrollY = ScrollMgr::GetInstance()->GetScrollY();

	int culTileX = (int)(-scrollX / (TILE_WIDTH));
	int culTileY = (int)(-scrollY / (TILE_HEIGHT*0.5f));

	int endTileX = (int)(WINDOW_WIDTH / (TILE_WIDTH));
	int endTileY = (int)(WINDOW_HEIGHT / (TILE_HEIGHT*0.5f));

	size_t index = 0;

	for (int i = culTileY; i < culTileY + endTileY + 2; ++i)
	{
		for (int j = culTileX; j < culTileX + endTileX + 2; ++j)
		{
			index = j + (int)(i*gTileNumX);

			if (index < 0 || index >= mTileSpace.size())
				continue;

			mTileSpace[index]->Render();
		}
	}


}

void TileMgr::ObstacleLoadData(const TCHAR * pFilePath)
{
	HANDLE hFile = CreateFile(pFilePath, GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Obstacle load failed!!!", L"Error!!!", MB_OK);
		return;
	}

	DWORD byte = 0;
	int drawID = 0;
	D3DXVECTOR3 vPos = { 0.f, 0.f, 0.f };

	while (true)
	{
		ReadFile(hFile, &drawID, sizeof(int), &byte, nullptr);
		ReadFile(hFile, &vPos, sizeof(D3DXVECTOR3), &byte, nullptr);

		if (byte == 0)
		{
			m_bObstacleInit = true;
			break;
		}

		Obj* pObstacle = ObjFactory<Obstacle>::CreateObj(vPos);
		pObstacle->SetDrawID(drawID);
		ObjMgr::GetInstance()->AddObject(OBJ_OBSTACLE, pObstacle);
	}
	CloseHandle(hFile);
}

int TileMgr::Picking()
{
	POINT	pt;

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x -= (int)ScrollMgr::GetInstance()->GetScrollX();
	pt.y -= (int)ScrollMgr::GetInstance()->GetScrollY();

	for (Tile* pTile : mTileSpace)
	{
		if (pTile->GetTileInfo().gradiant[LEFT] * pt.x + pTile->GetTileInfo().intercept[LEFT] <= pt.y
			&& pTile->GetTileInfo().gradiant[UP] * pt.x + pTile->GetTileInfo().intercept[UP] <= pt.y
			&& pTile->GetTileInfo().gradiant[RIGHT] * pt.x + pTile->GetTileInfo().intercept[RIGHT] > pt.y
			&& pTile->GetTileInfo().gradiant[DOWN] * pt.x + pTile->GetTileInfo().intercept[DOWN] > pt.y)
		{
			if (pTile->GetOption() == TILE_BLOCK)
				return -1;
			else
				return pTile->GetIndex();
		}
	}

	return -1;
}

HRESULT TileMgr::Picking(const D3DXVECTOR3& vPos)
{
	for (Tile* pTile : mTileSpace)
	{
		if (pTile->GetTileInfo().gradiant[LEFT] * vPos.x + pTile->GetTileInfo().intercept[LEFT] <= vPos.y
			&& pTile->GetTileInfo().gradiant[UP] * vPos.x + pTile->GetTileInfo().intercept[UP] <= vPos.y
			&& pTile->GetTileInfo().gradiant[RIGHT] * vPos.x + pTile->GetTileInfo().intercept[RIGHT] > vPos.y
			&& pTile->GetTileInfo().gradiant[DOWN] * vPos.x + pTile->GetTileInfo().intercept[DOWN] > vPos.y)
		{
			if (pTile->GetOption() == TILE_BLOCK)
				return E_FAIL;
			else
				return pTile->GetIndex();
		}
	}

	return E_FAIL;
}

void TileMgr::LoadData(const TCHAR * pFilePath)
{
	HANDLE hFile = CreateFile(pFilePath, GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Tile load failed!!!", L"Error!!!", MB_OK);
		return;
	}

	DWORD byte = 0;
	TILE_INFO tileInfo;

	Tile* pTile = nullptr;
	int index = 0;

	ReadFile(hFile, &gTileNumX, sizeof(float), &byte, nullptr);
	ReadFile(hFile, &gTileNumY, sizeof(float), &byte, nullptr);

	mTileSpace.reserve((int)(gTileNumX*gTileNumY));

	while (true)
	{
		ReadFile(hFile, &tileInfo, sizeof(TILE_INFO), &byte, nullptr);

		if (0 == byte)
		{
			m_bTileInit = true;
			break;
		}
			

		pTile = new Tile;
		pTile->Initiallize(tileInfo, index);
		mTileSpace.emplace_back(pTile);
		++index;
	}

	CloseHandle(hFile);
}

bool TileMgr::SetTileOption(const D3DXVECTOR3& vPos, const int option)
{
	size_t tileIndex = Picking(vPos);

	if (tileIndex == -1 && tileIndex >= TileMgr::GetInstance()->GetTileSpace().size())
		return false;

	Tile* pTile = mTileSpace[tileIndex];

	if (pTile->GetOption() == TILE_AVAILABLE)
	{
		pTile->SetOption(option);
		return true;
	}

	return false;
}

Tile * TileMgr::GetTile(const size_t index)
{
	if (index == -1 || index >= mTileSpace.size())
		return nullptr;

	return mTileSpace[index];
}

void TileMgr::Release()
{
	for_each(mTileSpace.begin(), mTileSpace.end(), SafeDelete<Tile*>);
	mTileSpace.clear();
	vector<Tile*>().swap(mTileSpace);
	m_bObstacleInit = false;
	m_bTileInit = false;
}
