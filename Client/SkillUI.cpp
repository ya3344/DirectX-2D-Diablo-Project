#include "stdafx.h"
#include "SkillUI.h"
#include "Player.h"

int SkillUI::gFrameIndex = FIRST_FRAME;
int SkillUI::gSkillPoint = 0;
int SkillUI::gFirstSkillCount = 0;
int SkillUI::gSecondSkillCount = 0;
int SkillUI::gThirdSkillCount = 0;


SkillUI::SkillUI()
{
	mStateKey = L"Skill";
}

SkillUI::~SkillUI()
{
	Release();
}

HRESULT SkillUI::Initialize()
{
	if (mDrawID == FIRST_FRAME || mDrawID == SECOND_FRAME || mDrawID == THIRD_FRAME)
	{
		mCloseRect = { 614, 480, 614 + 48, 480 + 48 };
		mSkillOpenRect = { 636, 554, 636 + 48, 554 + 48 };
		mFrameRect[0] = { 688, 141, 688 + 110, 141 + 115 };
		mFrameRect[1] = { 688, 273, 688 + 110, 273 + 115 };
		mFrameRect[2] = { 688, 411, 688 + 110, 411 + 115 };

		g_bSkillIcon[FIRST_FRAME] = true;
		g_bSkillIcon[SECOND_FRAME] = true;
		g_bSkillIcon[THIRD_FRAME] = true;

	}
	return S_OK;
}

int SkillUI::Update(void)
{
	InitIcon();
	static bool init = false;

	if (PtInRect(&mSkillOpenRect, MathMgr::GetInstance()->GetMouse()))
	{
		if (GetAsyncKeyState(VK_LBUTTON) && 0x8000)
		{
			if (init == false)
			{
				m_bSkillIcon = !m_bSkillIcon;
				init = true;
			}
		}

		if (KeyMgr::GetInstance()->KeyPressed(KEY_LBUTTON))
		{
			init = false;
		}

		dynamic_cast<LifeObj*>(m_pPlayer)->SetMoveCheck(false);
	}

	return OBJ_NORMAL;
}

void SkillUI::Render(void)
{
	KeyCheck();

	if (m_bSkillDialog == false && mType <= 10)
		return;

	if (mType > 10)
	{
		if (mType < 100)
		{
			if (m_bSkillIcon == false)
				return;
		}


		D3DXMatrixScaling(&mInfo.matScale, 0.8f, 0.8f, 0.0f);
	}
	else
	{
		D3DXMatrixScaling(&mInfo.matScale, 1.f, 1.f, 0.0f);
	}

	m_pTextureInfo = TextureMgr::GetInstance()->GetTexture(mObjKey, mStateKey, mDrawID);
	D3DXMatrixTranslation(&mInfo.matTrans, mInfo.vPos.x, mInfo.vPos.y, mInfo.vPos.z);

	mInfo.matWorld = mInfo.matScale * mInfo.matTrans;
	m_pSprite->SetTransform(&mInfo.matWorld);

	if (g_bSkillIcon[mDrawID])
	{
		m_pSprite->Draw(m_pTextureInfo->pTexture, NULL, &D3DXVECTOR3(0.f, 0.f, 0.f), nullptr, D3DCOLOR_ARGB(mAlpha, 255, 255, 255));

		if(m_bSkillIcon)
			SkillSlotFont();
	}
		

	// CollisionRectSetting
	if (mDrawID < 62)
	{
		if (mType <= 10)
		{
			mCollisionRect = { (LONG)mInfo.vPos.x, (LONG)mInfo.vPos.y,
				(LONG)(mInfo.vPos.x + m_pTextureInfo->imgInfo.Width), (LONG)(mInfo.vPos.y + m_pTextureInfo->imgInfo.Height) };
		}
		else
		{
			mCollisionRect = { (LONG)mInfo.vPos.x, (LONG)mInfo.vPos.y,
				(LONG)(mInfo.vPos.x + 48), (LONG)(mInfo.vPos.y + 48) };
		}
	}

	DebugMgr::GetInstance()->DrawRectange((float)mCollisionRect.left, (float)mCollisionRect.top,
		(float)m_pTextureInfo->imgInfo.Width * mInfo.matScale._11, (float)m_pTextureInfo->imgInfo.Height * mInfo.matScale._22);


	FontDraw();

	// Collision Check
	Collision();
	
}

void SkillUI::Collision(void)
{
	if (PtInRect(&mCloseRect, MathMgr::GetInstance()->GetMouse()))
	{
		if (GetAsyncKeyState(VK_LBUTTON) && 0x8000)
		{
			m_bSkillDialog = false;
		}
	}

	if (PtInRect(&mFrameRect[0], MathMgr::GetInstance()->GetMouse()))
	{
		if (GetAsyncKeyState(VK_LBUTTON) && 0x8000)
		{
			mDrawID = FIRST_FRAME;
			gFrameIndex = FIRST_FRAME;
		}
	}

	if (PtInRect(&mFrameRect[1], MathMgr::GetInstance()->GetMouse()))
	{
		if (GetAsyncKeyState(VK_LBUTTON) && 0x8000)
		{
			mDrawID = SECOND_FRAME;
			gFrameIndex = SECOND_FRAME;
		}
	}

	if (PtInRect(&mFrameRect[2], MathMgr::GetInstance()->GetMouse()))
	{
		if (GetAsyncKeyState(VK_LBUTTON) && 0x8000)
		{
			mDrawID = THIRD_FRAME;
			gFrameIndex = THIRD_FRAME;
		}
	}

	if (PtInRect(&mCollisionRect, MathMgr::GetInstance()->GetMouse()))
	{
		if (GetAsyncKeyState(VK_LBUTTON) && 0x8000)
		{
			if (g_bSkillIcon[mDrawID] == false)
			{
				if(mType <= 10 && m_pPlayer->GetAttribute().skillPoint > 0)
					SkillSelect();
			}
			else
			{
				if (mType > 10 && mType < 100)
				{
					if (ObjMgr::GetInstance()->GetUIObj(100) != nullptr)
					{
						ObjMgr::GetInstance()->GetUIObj(100)->SetDrawID(mDrawID);
						dynamic_cast<Player*>(m_pPlayer)->SetSkillChoice(mDrawID);
						m_bSkillIcon = false;
					}
				
				}
				
			}
		}

		if (mType > 10 && mType < 100)
		{
			if (KeyMgr::GetInstance()->KeyDown(KEY_F1))
			{
				dynamic_cast<Player*>(m_pPlayer)->AddSkillSlot(L"F1", mInfo.vPos, mDrawID);
			}

			if (KeyMgr::GetInstance()->KeyDown(KEY_F2))
			{
				dynamic_cast<Player*>(m_pPlayer)->AddSkillSlot(L"F2", mInfo.vPos, mDrawID);
			}

			if (KeyMgr::GetInstance()->KeyDown(KEY_F3))
			{
				dynamic_cast<Player*>(m_pPlayer)->AddSkillSlot(L"F3", mInfo.vPos, mDrawID);
			}

			if (KeyMgr::GetInstance()->KeyDown(KEY_F4))
			{
				dynamic_cast<Player*>(m_pPlayer)->AddSkillSlot(L"F4", mInfo.vPos, mDrawID);
			}

			if (KeyMgr::GetInstance()->KeyDown(KEY_F5))
			{
				dynamic_cast<Player*>(m_pPlayer)->AddSkillSlot(L"F5", mInfo.vPos, mDrawID);
			}

			if (KeyMgr::GetInstance()->KeyDown(KEY_F6))
			{
				dynamic_cast<Player*>(m_pPlayer)->AddSkillSlot(L"F6", mInfo.vPos, mDrawID);
			}

			if (KeyMgr::GetInstance()->KeyDown(KEY_F7))
			{
				dynamic_cast<Player*>(m_pPlayer)->AddSkillSlot(L"F7", mInfo.vPos, mDrawID);
			}

			if (KeyMgr::GetInstance()->KeyDown(KEY_F8))
			{
				dynamic_cast<Player*>(m_pPlayer)->AddSkillSlot(L"F8", mInfo.vPos, mDrawID);
			}
		}


		//dynamic_cast<LifeObj*>(m_pPlayer)->SetMoveCheck(false);
	}

	if(m_bSkillDialog || m_bSkillIcon)
		dynamic_cast<LifeObj*>(m_pPlayer)->SetMoveCheck(false);



}

void SkillUI::KeyCheck(void)
{
	if (KeyMgr::GetInstance()->KeyDown(KEY_K))
	{
		m_bSkillDialog = !m_bSkillDialog;
	}
	if (KeyMgr::GetInstance()->KeyDown(KEY_L))
	{
		m_bSkillIcon = !m_bSkillIcon;
	}

	if (GetAsyncKeyState(VK_F1) & 0x8000)
	{
		SkillSlotSelect(L"F1");
	}
	else if (GetAsyncKeyState(VK_F2) & 0x8000)
	{
		SkillSlotSelect(L"F2");
	}
	else if (GetAsyncKeyState(VK_F3) & 0x8000)
	{
		SkillSlotSelect(L"F3");
	}
	else if (GetAsyncKeyState(VK_F4) & 0x8000)
	{
		SkillSlotSelect(L"F4");
	}
	else if (GetAsyncKeyState(VK_F5) & 0x8000)
	{
		SkillSlotSelect(L"F5");
	}
	else if (GetAsyncKeyState(VK_F6) & 0x8000)
	{
		SkillSlotSelect(L"F6");
	}
	else if (GetAsyncKeyState(VK_F7) & 0x8000)
	{
		SkillSlotSelect(L"F7");
	}
	else if (GetAsyncKeyState(VK_F8) & 0x8000)
	{
		SkillSlotSelect(L"F8");
	}

}

void SkillUI::InitIcon()
{
	if (gFrameIndex == FIRST_FRAME)
	{
		switch (mType)
		{
		case 1:
			mInfo.vPos = D3DXVECTOR3(420.f, 14.f, 0.f);
			mDrawID = 0;
			break;
		case 2:
			mInfo.vPos = D3DXVECTOR3(420.f, 100.f, 0.f);
			mDrawID = 2;
			break;
		case 3:
			mInfo.vPos = D3DXVECTOR3(420.f, 185.f, 0.f);
			mDrawID = 6;
			break;
		case 4:
			mInfo.vPos = D3DXVECTOR3(420.f, 357.f, 0.f);
			mDrawID = 12;
			break;
		case 5:
			mInfo.vPos = D3DXVECTOR3(420.f, 442.f, 0.f);
			mDrawID = 16;
			break;
		case 6:
			mInfo.vPos = D3DXVECTOR3(593.f, 100.f, 0.f);
			mDrawID = 4;
			break;
		case 7:
			mInfo.vPos = D3DXVECTOR3(593.f, 185.f, 0.f);
			mDrawID = 8;
			break;
		case 8:
			mInfo.vPos = D3DXVECTOR3(505.f, 270.f, 0.f);
			mDrawID = 10;
			break;
		case 9:
			mInfo.vPos = D3DXVECTOR3(505.f, 355.f, 0.f);
			mDrawID = 14;
			break;
		case 10:
			mInfo.vPos = D3DXVECTOR3(505.f, 440.f, 0.f);
			mDrawID = 18;
			break;
		default:
			break;
		}
	}
	else if (gFrameIndex == SECOND_FRAME)
	{
		switch (mType)
		{
		case 1:
			mInfo.vPos = D3DXVECTOR3(420.f, 14.f, 0.f);
			mDrawID = 20;
			break;
		case 2:
			mInfo.vPos = D3DXVECTOR3(420.f, 185.f, 0.f);
			mDrawID = 26;
			break;
		case 3:
			mInfo.vPos = D3DXVECTOR3(420.f, 270.f, 0.f);
			mDrawID = 30;
			break;
		case 4:
			mInfo.vPos = D3DXVECTOR3(420.f, 442.f, 0.f);
			mDrawID = 38;
			break;
		case 5:
			mInfo.vPos = D3DXVECTOR3(505.f, 14.f, 0.f);
			mDrawID = 22;
			break;
		case 6:
			mInfo.vPos = D3DXVECTOR3(505.f, 270.f, 0.f);
			mDrawID = 32;
			break;
		case 7:
			mInfo.vPos = D3DXVECTOR3(505.f, 355.f, 0.f);
			mDrawID = 34;
			break;
		case 8:
			mInfo.vPos = D3DXVECTOR3(593,  100.f, 0.f);
			mDrawID = 24;
			break;
		case 9:
			mInfo.vPos = D3DXVECTOR3(593.f, 185.f, 0.f);
			mDrawID = 28;
			break;
		case 10:
			mInfo.vPos = D3DXVECTOR3(593.f, 355.f, 0.f);
			mDrawID = 36;
			break;
		default:
			break;
		}
	}
	else if (gFrameIndex == THIRD_FRAME)
	{
		switch (mType)
		{
		case 1:
			mInfo.vPos = D3DXVECTOR3(420.f, 100.f, 0.f);
			mDrawID = 44;
			break;
		case 2:
			mInfo.vPos = D3DXVECTOR3(420.f, 274.f, 0.f);
			mDrawID = 50;
			break;
		case 3:
			mInfo.vPos = D3DXVECTOR3(420.f, 442.f, 0.f);
			mDrawID = 56;
			break;
		case 4:
			mInfo.vPos = D3DXVECTOR3(505.f, 14.f, 0.f);
			mDrawID = 40;
			break;
		case 5:
			mInfo.vPos = D3DXVECTOR3(505.f, 100.f, 0.f);
			mDrawID = 46;
			break;
		case 6:
			mInfo.vPos = D3DXVECTOR3(505.f, 274.f, 0.f);
			mDrawID = 52;
			break;
		case 7:
			mInfo.vPos = D3DXVECTOR3(505.f, 442.f, 0.f);
			mDrawID = 58;
			break;
		case 8:
			mInfo.vPos = D3DXVECTOR3(593, 14.f, 0.f);
			mDrawID = 42;
			break;
		case 9:
			mInfo.vPos = D3DXVECTOR3(593.f, 185.f, 0.f);
			mDrawID = 48;
			break;
		case 10:
			mInfo.vPos = D3DXVECTOR3(593.f, 355.f, 0.f);
			mDrawID = 54;
			break;
		default:
			break;
		}
	}
}

void SkillUI::FontDraw()
{
	if (m_bSkillDialog == false)
		return;

	D3DXMatrixTranslation(&mMatFont, 705, 188, 0.f);
	m_pSprite->SetTransform(&mMatFont);
	m_pFont->DrawTextW(m_pSprite
		, L"Human\n  Skill", lstrlen(L"Human\n   Skill"), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));


	D3DXMatrixTranslation(&mMatFont, 705, 325, 0.f);
	m_pSprite->SetTransform(&mMatFont);
	m_pFont->DrawTextW(m_pSprite
		, L"  Wolf\n  Skill", lstrlen(L"  Wolf\n  Skill"), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));


	D3DXMatrixTranslation(&mMatFont, 705, 451, 0.f);
	m_pSprite->SetTransform(&mMatFont);
	m_pFont->DrawTextW(m_pSprite
		, L"  Bear\n  Skill", lstrlen(L"  Bear\n  Skill"), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));


	D3DXMatrixTranslation(&mMatFont, 729, 82, 0.f);
	wsprintf(mSkillPointBuf, L"%d", m_pPlayer->GetAttribute().skillPoint);

	m_pSprite->SetTransform(&mMatFont);
	m_pFont->DrawTextW(m_pSprite
		, mSkillPointBuf, lstrlen(mSkillPointBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void SkillUI::SkillSelect()
{
	if (gFrameIndex == FIRST_FRAME)
	{
		if (mDrawID == 0 || mDrawID == 4)
		{
			g_bSkillIcon[mDrawID] = true;
			m_pPlayer->SetSkillPoint(-1);
			SkillAdd(mDrawID);
		}
		else 
		{
			switch (mDrawID)
			{
			case 2:
				SkillCheck(0, mDrawID);
				break;
			case 6:
				SkillCheck(2, mDrawID);
				break;
			case 12:
				SkillCheck(6, mDrawID);
				break;
			case 16:
				SkillCheck(18, mDrawID);
				SkillCheck(12, mDrawID);
				break;
			case 8:
				SkillCheck(4, mDrawID);
				break;
			case 10:
				SkillCheck(8, mDrawID);
				break;
			case 14:
				SkillCheck(10, mDrawID);
				break;
			case 18:
				SkillCheck(14, mDrawID);
				break;
			default:
				break;
			}
		}
	}
	if (gFrameIndex == SECOND_FRAME)
	{
		if (mDrawID == 20 || mDrawID == 24)
		{
			g_bSkillIcon[mDrawID] = true;
			m_pPlayer->SetSkillPoint(-1);
			SkillAdd(mDrawID);
		}
		else
		{
			switch (mDrawID)
			{
			case 26:
				SkillCheck(20, mDrawID);
				break;
			case 30:
				SkillCheck(26, mDrawID);
				break;
			case 38:
				SkillCheck(30, mDrawID);
				break;
			case 22:
				SkillCheck(20, mDrawID);
				break;
			case 28:
				SkillCheck(24, mDrawID);
				break;
			case 36:
				SkillCheck(28, mDrawID);
				break;
			case 32:
				SkillCheck(26, mDrawID);
				SkillCheck(28, mDrawID);
				break;
			case 34:
				SkillCheck(32, mDrawID);
				break;


			default:
				break;

			}
		}
	}
	if (gFrameIndex == THIRD_FRAME)
	{
		if (mDrawID == 40 || mDrawID == 42 || mDrawID == 44 )
		{
			g_bSkillIcon[mDrawID] = true;
			m_pPlayer->SetSkillPoint(-1);
			SkillAdd(mDrawID);
		}
		else
		{
			switch (mDrawID)
			{
			case 46:
				SkillCheck(40, mDrawID);
				break;
			case 52:
				SkillCheck(46, mDrawID);
				SkillCheck(44, mDrawID);
				break;
			case 58:
				SkillCheck(52, mDrawID);
				break;
			case 50:
				SkillCheck(44, mDrawID);
				break;
			case 56:
				SkillCheck(50, mDrawID);
				break;
			case 48:
				SkillCheck(42, mDrawID);
				break;
			case 54:
				SkillCheck(48, mDrawID);
				break;
			default:
				break;

			}
		}
	}
	
}

void SkillUI::SkillSlotFont()
{
	for (SKILL_SLOT* pSlot : dynamic_cast<Player*>(m_pPlayer)->GetSkillSlotSpace())
	{
		D3DXMatrixTranslation(&mMatFont, pSlot->vPos.x, pSlot->vPos.y, 0.f);
	
		m_pSprite->SetTransform(&mMatFont);
		m_pFont->DrawTextW(m_pSprite
			, pSlot->keyBuf, lstrlen(pSlot->keyBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void SkillUI::SkillSlotSelect(const TCHAR* pKeyBuf)
{
	
	for (SKILL_SLOT* pSlot : dynamic_cast<Player*>(m_pPlayer)->GetSkillSlotSpace())
	{
		if (!lstrcmp(pSlot->keyBuf, pKeyBuf))
		{
			if (ObjMgr::GetInstance()->GetUIObj(100) != nullptr)
			{
				ObjMgr::GetInstance()->GetUIObj(100)->SetDrawID(pSlot->drawID);
				dynamic_cast<Player*>(m_pPlayer)->SetSkillChoice(pSlot->drawID);
			}
		}
	}
	
}


inline void SkillUI::SkillCheck(int checkDrawID, int drawID)
{
	if (g_bSkillIcon[drawID] == false)
	{
		if (g_bSkillIcon[checkDrawID] == true)
		{
			g_bSkillIcon[drawID] = true;
			m_pPlayer->SetSkillPoint(-1);
			SkillAdd(mDrawID);
		}
	}
	
}

inline void SkillUI::SkillAdd(int drawID)
{
	float Y = 0.f;
	float X = 0.f;

	if (gFrameIndex == FIRST_FRAME)
	{
		X = 633 - (48.f * gFirstSkillCount);
		Y = 452.f;
		++gFirstSkillCount;
	//	cout << gFirstSkillCount << endl;
		
	}
	else if (gFrameIndex == SECOND_FRAME)
	{
		X = 633 - (48.f * gSecondSkillCount);
		Y = 404.f;
		++gSecondSkillCount;
	//	cout << gSecondSkillCount << endl;
	}
	else if (gFrameIndex == THIRD_FRAME)
	{
		X = 633 - (48.f * gThirdSkillCount);
		Y = 356.f;
		++gThirdSkillCount;
	//	cout << gThirdSkillCount << endl;
	}

	ObjMgr::GetInstance()->AddObject(OBJ_UI,
		ObjFactory<SkillUI>::CreateUI(D3DXVECTOR3(X, Y, 0.f), drawID, mDrawID + 11));

	//m_bSkillCountInit = true;


}

void SkillUI::Release(void)
{
	
}


