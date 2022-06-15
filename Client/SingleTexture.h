#pragma once
#include "Texture.h"

class SingleTexture : public Texture
{
public:
	SingleTexture();
	virtual ~SingleTexture();

public:
	// Texture��(��) ���� ��ӵ�
	virtual TEXTURE_INFO * GetTexture(const wstring & stateKey = L"", int count = 0) const override
	{
		return m_pTextureInfo;
	};

public:
	virtual HRESULT InsertTexture(const wstring & filePath, const wstring & stateKey = L"", const int & count = 0) override;
	virtual void Release() override;

private:
	TEXTURE_INFO* m_pTextureInfo = nullptr;
};

