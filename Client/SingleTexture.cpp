#include "stdafx.h"
#include "SingleTexture.h"


SingleTexture::SingleTexture()
{
}


SingleTexture::~SingleTexture()
{
	Release();
}

HRESULT SingleTexture::InsertTexture(const wstring & filePath, const wstring & stateKey, const int & count)
{
	m_pTextureInfo = new TEXTURE_INFO;
	ZeroMemory(m_pTextureInfo, sizeof(TEXTURE_INFO));

	if (FAILED(D3DXGetImageInfoFromFile(filePath.c_str(), &m_pTextureInfo->imgInfo)))
	{
		MessageBox(NULL, stateKey.c_str(), L"System Message", MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFileEx(Device::GetInstance()->GetDevice()
		, filePath.c_str()
		, m_pTextureInfo->imgInfo.Width
		, m_pTextureInfo->imgInfo.Height
		, m_pTextureInfo->imgInfo.MipLevels
		, 0
		, m_pTextureInfo->imgInfo.Format
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, NULL
		, &m_pTextureInfo->imgInfo
		, nullptr
		, &m_pTextureInfo->pTexture)))
	{
		MessageBox(NULL, filePath.c_str(), L"System Message", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

void SingleTexture::Release()
{
	SafeRelease<LPDIRECT3DTEXTURE9>(m_pTextureInfo->pTexture);
	SafeDelete<TEXTURE_INFO*>(m_pTextureInfo);
}
