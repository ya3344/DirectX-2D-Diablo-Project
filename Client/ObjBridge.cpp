#include "stdafx.h"
#include "ObjBridge.h"
#include "Bridge.h"

ObjBridge::ObjBridge()
{
}


ObjBridge::~ObjBridge()
{
	Release();
}

HRESULT ObjBridge::Initialize()
{
	if (m_pBridge)
		m_pBridge->SetObj(this);

	return S_OK;
}

int ObjBridge::Update(void)
{
	int result = 0;

	if (m_pBridge)
		result = m_pBridge->Update();

	if (result == OBJ_DIE)
	{
		return OBJ_DIE;
	}

	return OBJ_NORMAL;
}

void ObjBridge::Render(void)
{
	if (m_pBridge)
		m_pBridge->Render();
}

void ObjBridge::Release(void)
{
	SafeDelete<Bridge*>(m_pBridge);
}
