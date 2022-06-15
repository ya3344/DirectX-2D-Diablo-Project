#include "stdafx.h"
#include "MultiTexture.h"


MultiTexture::MultiTexture()
{
}


MultiTexture::~MultiTexture()
{
	Release();
}

TEXTURE_INFO * MultiTexture::GetTexture(const wstring & stateKey, int count) const
{
	auto iterFind = mMultiTextureSpace.find(stateKey);

	if (iterFind == mMultiTextureSpace.end())
	{
		cout << "MultiTexture NULLptr Error!!!" << endl;
		//MESSAGE_BOX(L"MultiTexture NULLptr Error!!!!!", L"TEXTURE_INFO * TextureMgr::GetTexture");
		return nullptr;
	}

	if ((size_t)count >= iterFind->second.size())
	{
		count = iterFind->second.size() - 1;
		cout << "Vector Exceed Error!!!" << endl;
		//MESSAGE_BOX(L"Vector Exceed Error!!!!", L"TEXTURE_INFO * TextureMgr::GetTexture");
		return nullptr;
	}

	if (count <= 0)
	{
		count = 0;
	}


	return iterFind->second[count];
}

HRESULT MultiTexture::InsertTexture(const wstring & filePath, const wstring & stateKey, const int & count)
{
	TCHAR szPath[MAX_PATH] = L"";

	vector<TEXTURE_INFO*> textureSpace;
	TEXTURE_INFO* pTextureInfo = nullptr;

	for (int i = 0; i < count; ++i)
	{
		wsprintf(szPath, filePath.c_str(), i);

		pTextureInfo = new TEXTURE_INFO;
		ZeroMemory(pTextureInfo, sizeof(TEXTURE_INFO));

		if (FAILED(D3DXGetImageInfoFromFile(szPath, &pTextureInfo->imgInfo)))
		{
			MESSAGE_BOX(stateKey.c_str(), L"MultiTexture::InsertTexture");
			return E_FAIL;
		}

		if (FAILED(D3DXCreateTextureFromFileEx(Device::GetInstance()->GetDevice()
			, szPath
			, pTextureInfo->imgInfo.Width
			, pTextureInfo->imgInfo.Height
			, pTextureInfo->imgInfo.MipLevels
			, 0
			, pTextureInfo->imgInfo.Format
			, D3DPOOL_MANAGED
			, D3DX_DEFAULT
			, D3DX_DEFAULT
			, NULL
			, &pTextureInfo->imgInfo
			, nullptr
			, &pTextureInfo->pTexture)))
		{
			MESSAGE_BOX(filePath.c_str(), L"MultiTexture::InsertTexture");
			return E_FAIL;
		}
		textureSpace.emplace_back(pTextureInfo);
	}

	mMultiTextureSpace.emplace(stateKey, textureSpace);
	return S_OK;
}

void MultiTexture::Release()
{
	for (pair<wstring, vector<TEXTURE_INFO*>> multiTexturePair : mMultiTextureSpace)
	{
		for (TEXTURE_INFO* pTextureInfo : multiTexturePair.second)
		{
			SafeRelease<LPDIRECT3DTEXTURE9>(pTextureInfo->pTexture);
			SafeDelete<TEXTURE_INFO*>(pTextureInfo);
		}
		multiTexturePair.second.clear();
		vector<TEXTURE_INFO*>().swap(multiTexturePair.second);
	}
	mMultiTextureSpace.clear();
}
