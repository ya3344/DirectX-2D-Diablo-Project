#pragma once
class DebugMgr
{
	DECLARE_SINGLETON(DebugMgr);
private:
	DebugMgr();
	~DebugMgr();

public:
	void DebugText(const TCHAR* pFontBuf, D3DXVECTOR3 vPos);
	void DrawRectange(float x, float y, float widht, float height);

public:
	D3DXMATRIX mFontMatrix;
	LPD3DXSPRITE m_pSprite = nullptr;
	LPD3DXFONT m_pFont = nullptr;

};

