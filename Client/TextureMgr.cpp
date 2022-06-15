#include "stdafx.h"
#include "TextureMgr.h"
#include "Texture.h"
#include "SingleTexture.h"
#include "MultiTexture.h"
#include "Scene.h"

IMPLEMENT_SINGLETON(TextureMgr);

TextureMgr::TextureMgr()
{
	cout << "TxturMgr »ý¼º" << endl;
}


TextureMgr::~TextureMgr()
{
	Release();
	//cout << "TxturMgr ¼Ò¸ê" << endl;
}



TEXTURE_INFO * TextureMgr::GetTexture(const wstring & objKey, const wstring & stateKey, int count)
{
	auto iterFind = mTextureSpace.find(objKey);

	if (iterFind == mTextureSpace.end())
	{
		MESSAGE_BOX(L"Texture Find Error!!", L"TEXTURE_INFO * TextureMgr::GetTexture");
		return nullptr;
	}

	return iterFind->second->GetTexture(stateKey, count);
}

HRESULT TextureMgr::InsertTexture(const wstring & filePath, const wstring & objKey, TEXTURE_TYPE textureType, const wstring & stateKey, const int & count)
{
	auto iterFind = mTextureSpace.find(objKey);

	if (iterFind == mTextureSpace.end())
	{
		Texture* pTexture = nullptr;

		switch (textureType)
		{
		case TEXTURE_SINGLE:
			pTexture = new SingleTexture;
			break;
		case TEXTURE_MULTI:
			pTexture = new MultiTexture;
			break;
		}

		if (FAILED(pTexture->InsertTexture(filePath, stateKey, count)))
		{
			MESSAGE_BOX(objKey.c_str(), L"InsertTexture(IF)");
			return E_FAIL;
		}
		mTextureSpace.emplace(objKey, pTexture);
	}
	else
	{
		if (textureType == TEXTURE_MULTI)
		{
			if (FAILED(iterFind->second->InsertTexture(filePath, stateKey, count)))
			{
				MESSAGE_BOX(objKey.c_str(), L"InertTexture(Else)");
				return E_FAIL;
			}
		}
	}

	return S_OK;
}

HRESULT TextureMgr::ReadImagePath(const wstring & path)
{
	wifstream loadFile;
	loadFile.open(path.c_str(), ios::in);

	TCHAR objKey[KEY_SIZE] = L"";
	TCHAR stateKey[KEY_SIZE] = L"";
	TCHAR countBuf[KEY_SIZE] = L"";
	TCHAR imgPath[MAX_PATH] = L"";

	while (!loadFile.eof())
	{
		loadFile.getline(objKey, KEY_SIZE, '|');
		loadFile.getline(stateKey, KEY_SIZE, '|');
		loadFile.getline(countBuf, KEY_SIZE, '|');
		loadFile.getline(imgPath, MAX_PATH);

		int count = _ttoi(countBuf);

		if (FAILED(InsertTexture(imgPath, objKey, TEXTURE_MULTI, stateKey, count)))
		{
			MESSAGE_BOX(objKey, L"TextureMgr::ReadImagePath");
			return E_FAIL;
		}
	}
	
	loadFile.close();
	return S_OK;
}

void TextureMgr::Release()
{
	for_each(mTextureSpace.begin(), mTextureSpace.end(), 
		[](pair<wstring, Texture*> texturePair)
	{
		if (texturePair.second)
		{	
			SafeDelete<Texture*>(texturePair.second);
		}
	});
	mTextureSpace.clear();
}
