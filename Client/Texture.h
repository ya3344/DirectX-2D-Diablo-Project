#pragma once

class Texture abstract
{
public:
	Texture();
	virtual ~Texture();

public:
	virtual TEXTURE_INFO* GetTexture(const wstring& stateKey = L"" , int count = 0) const PURE;

public:
	virtual HRESULT InsertTexture(const wstring& filePath, const wstring& stateKey = L"", const int& count = 0) PURE;
	virtual void Release() PURE;
};

