#pragma once

class Tile
{
public:
	Tile();
	~Tile();

public:
	void Initiallize(const TILE_INFO& tileInfo, const int index);
	int Update();
	void Render();

public:
	void SetDrawID(const int drawID) { mTileInfo.drawID = drawID; };
	void SetOption(const int option) { mTileInfo.option = option; }
	void SetSize(const D3DXVECTOR3 size) { mTileInfo.vSize = size; }


public:
	int GetDrawID() const { return mTileInfo.drawID; }
	int GetOption() const { return mTileInfo.option;  }
	int GetIndex() const { return mIndex; }
	const TILE_INFO& GetTileInfo() const { return mTileInfo; }
private:
	void Release();

private:
	LPD3DXSPRITE m_pSprite = nullptr;
	LPD3DXFONT m_pFont = nullptr;

	D3DXIMAGE_INFO mImgInfo = {};
	TILE_INFO mTileInfo;

	const TEXTURE_INFO* m_pTextureInfo = nullptr;

private:
	float mCenterX = 0.f;
	float mCenterY = 0.f;

	int mIndex = 0;
};

