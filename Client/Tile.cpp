#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
}


Tile::~Tile()
{
	Release();
}

void Tile::Initiallize(const TILE_INFO& tileInfo, const int index)
{
	m_pSprite = Device::GetInstance()->GetSprite();
	m_pFont = Device::GetInstance()->GetFont();
	mIndex = index;

	mTileInfo.vPos = tileInfo.vPos;

	mTileInfo.vSize = tileInfo.vSize;
	mTileInfo.drawID = tileInfo.drawID;
	mTileInfo.option = tileInfo.option;

	mCenterX = mTileInfo.vSize.x * 0.5f;
	mCenterY = mTileInfo.vSize.y * 0.5f;

	// Left Vertex
	mTileInfo.vVertex[LEFT].x = mTileInfo.vPos.x - (mTileInfo.vSize.x * 0.5f);
	mTileInfo.vVertex[LEFT].y = mTileInfo.vPos.y;

	// Up Vertex
	mTileInfo.vVertex[UP].x = mTileInfo.vPos.x;
	mTileInfo.vVertex[UP].y = mTileInfo.vPos.y - (mTileInfo.vSize.y * 0.5f);

	// Right Vertex
	mTileInfo.vVertex[RIGHT].x = mTileInfo.vPos.x + (mTileInfo.vSize.x * 0.5f);
	mTileInfo.vVertex[RIGHT].y = mTileInfo.vPos.y;

	// Down Vertex
	mTileInfo.vVertex[DOWN].x = mTileInfo.vPos.x;
	mTileInfo.vVertex[DOWN].y = mTileInfo.vPos.y + (mTileInfo.vSize.y * 0.5f);

	// Gradiant = Height / Width
	mTileInfo.gradiant[LEFT] = ((mTileInfo.vVertex[LEFT].y - mTileInfo.vVertex[UP].y) / (mTileInfo.vVertex[LEFT].x - mTileInfo.vVertex[UP].x));
	mTileInfo.gradiant[UP] = ((mTileInfo.vVertex[UP].y - mTileInfo.vVertex[RIGHT].y) / (mTileInfo.vVertex[UP].x - mTileInfo.vVertex[RIGHT].x));
	mTileInfo.gradiant[RIGHT] = ((mTileInfo.vVertex[RIGHT].y - mTileInfo.vVertex[DOWN].y) / (mTileInfo.vVertex[RIGHT].x - mTileInfo.vVertex[DOWN].x));
	mTileInfo.gradiant[DOWN] = ((mTileInfo.vVertex[DOWN].y - mTileInfo.vVertex[LEFT].y) / (mTileInfo.vVertex[DOWN].x - mTileInfo.vVertex[LEFT].x));

	// b = y - ax == y = ax+ b
	mTileInfo.intercept[LEFT] = mTileInfo.vVertex[LEFT].y - (mTileInfo.gradiant[LEFT] * (mTileInfo.vVertex[LEFT].x));
	mTileInfo.intercept[UP] = mTileInfo.vVertex[UP].y - (mTileInfo.gradiant[UP] * (mTileInfo.vVertex[UP].x));
	mTileInfo.intercept[RIGHT] = mTileInfo.vVertex[RIGHT].y - (mTileInfo.gradiant[RIGHT] * (mTileInfo.vVertex[RIGHT].x));
	mTileInfo.intercept[DOWN] = mTileInfo.vVertex[DOWN].y - (mTileInfo.gradiant[DOWN] * (mTileInfo.vVertex[DOWN].x));

	
}

int Tile::Update()
{

	return 0;
}

void Tile::Render()
{
	TCHAR fontBuf[16] = L"";

	D3DXMATRIX matTrans, matFont;
	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixIdentity(&matFont);

	D3DXMatrixTranslation(&matTrans, mTileInfo.vPos.x + ScrollMgr::GetInstance()->GetScrollX(),
		mTileInfo.vPos.y + ScrollMgr::GetInstance()->GetScrollY(), mTileInfo.vPos.z);
	mTileInfo.matWorld = matTrans;

	m_pTextureInfo = TextureMgr::GetInstance()->GetTexture(gSceneName, L"Tile", mTileInfo.drawID);

	m_pSprite->SetTransform(&mTileInfo.matWorld);
	m_pSprite->Draw(m_pTextureInfo->pTexture, nullptr, &D3DXVECTOR3(mCenterX, mCenterY, 0), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


	if (g_bCollingDraw)
	{
		m_pTextureInfo = TextureMgr::GetInstance()->GetTexture(L"TILE_OPTION", L"tileOption", mTileInfo.option);
		m_pSprite->Draw(m_pTextureInfo->pTexture, nullptr, &D3DXVECTOR3(mCenterX, mCenterY, 0), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		if (g_bFontDraw)
		{
			wsprintf(fontBuf, L"%d", mIndex);
			D3DXMatrixTranslation(&matFont, matTrans._41 - 10.f, matTrans._42 - 10.f, 0.f);
			m_pSprite->SetTransform(&matFont);
			m_pFont->DrawTextW(m_pSprite, fontBuf, lstrlen(fontBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}









}



void Tile::Release()
{
	
}
