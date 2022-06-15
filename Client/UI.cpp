#include "stdafx.h"
#include "UI.h"

bool UI::m_bStatDialog = false;
bool UI::m_bSkillDialog = false;
bool UI::m_bSkillIcon = false;
bool UI::m_bQuestDialog = false;

UI::UI()
{
	mObjKey = L"UI";

	D3DXMatrixIdentity(&mMatFont);
	m_pFont = Device::GetInstance()->GetFont();

	m_pPlayer = ObjMgr::GetInstance()->GetObj(OBJ_PLAYER);

	mUIRect = { 0 ,0, 800, 490 };
}


UI::~UI()
{
	
}

