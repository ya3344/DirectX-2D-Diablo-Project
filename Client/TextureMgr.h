#pragma once

class Texture;

class TextureMgr
{
	DECLARE_SINGLETON(TextureMgr);

/*public:										
	static TextureMgr* GetInstance()
	{										
		static TextureMgr*	m_pInstance = new TextureMgr;					
		return m_pInstance;						
	}											
												
	void DestroyInstance()						
	{											
		if (m_pInstance)						
		{										
			delete m_pInstance;					
			m_pInstance = nullptr;				
		}										
	}					*/						
												
/*private:										
	static ClassName* m_pInstance;	*/			

private:
	TextureMgr();
	~TextureMgr();

public:
	TEXTURE_INFO* GetTexture(const wstring& objKey, const  wstring& stateKey = L"", int count = 0);

public:
	HRESULT InsertTexture(const wstring& filePath, const wstring& objKey, TEXTURE_TYPE textureType, const wstring& stateKey = L"", const int& count = 0);
	HRESULT ReadImagePath(const wstring& path);

public:
	void Release();

private:
	unordered_map<wstring, Texture*> mTextureSpace;
};

