#pragma once
#include "Texture.h"

class MultiTexture : public Texture
{
public:
	MultiTexture();
	virtual ~MultiTexture();

public:
	// Texture��(��) ���� ��ӵ�
	virtual TEXTURE_INFO * GetTexture(const wstring & stateKey = L"", int count = 0) const override;
public:
	virtual HRESULT InsertTexture(const wstring & filePath, const wstring & stateKey = L"", const int & count = 0) override;
	virtual void Release() override;

private:
	unordered_map<wstring, vector<TEXTURE_INFO*>> mMultiTextureSpace;
};

