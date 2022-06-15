#pragma once
class Device
{
	DECLARE_SINGLETON(Device);

private:
	Device();
	~Device();

public:
	HRESULT InitDevice();

public:
	const LPDIRECT3DDEVICE9 GetDevice() const { return m_pDevice; }
	const LPD3DXSPRITE GetSprite() const { return m_pSprite; }
	const LPD3DXLINE GetLine() const { return m_pLine; }
	const LPD3DXFONT GetFont() const { return m_pFont; }
	const LPD3DXFONT GetStatFont() const { return m_pStatFont; }
	const LPD3DXFONT GetDebugFont() const { return m_pDebugFont; }

private:
	void SetParameters(D3DPRESENT_PARAMETERS& d3dpp);
	void Release();

private:
	LPDIRECT3D9 m_p3D = nullptr;
	LPDIRECT3DDEVICE9 m_pDevice = nullptr;
	LPD3DXSPRITE m_pSprite = nullptr;
	LPD3DXLINE m_pLine = nullptr;
private:
	LPD3DXFONT m_pFont = nullptr;
	LPD3DXFONT m_pStatFont = nullptr;
	LPD3DXFONT m_pDebugFont = nullptr;
};
