#include "stdafx.h"
#include "StatUI.h"
#include "PlayerObserver.h"

StatUI::StatUI()
{
	mStateKey = L"Stat";
	m_pStatFont = Device::GetInstance()->GetStatFont();
}


StatUI::~StatUI()
{
	Release();
}

HRESULT StatUI::Initialize()
{
	m_pObserver = new PlayerObserver;
	SubjectMgr::GetInstance()->Subscribe(m_pObserver);
	SubjectMgr::GetInstance()->Notify(PLAYER_DATA);
	return S_OK;
}

int StatUI::Update(void)
{
	KeyCheck();

	switch (mDrawID)
	{
	case ACTIVE_NORMAL_STAT:
		
		if (m_pPlayer->GetAttribute().statPoint <= 0)
		{
			if (mType != SKILL)
				mDrawID = DISABLE_STAT;
		}

		if (m_pPlayer->GetAttribute().skillPoint <= 0)
		{
			if(mType == SKILL)
				mDrawID = DISABLE_STAT;
		}
		break;
	case ACTIVE_PRESSED_STAT:
		break;
	case DISABLE_STAT:
		if (m_pPlayer->GetAttribute().statPoint > 0)
		{
			if(mType != SKILL)
				mDrawID = ACTIVE_NORMAL_STAT;
		}

		if (m_pPlayer->GetAttribute().skillPoint > 0)
		{
			if (mType == SKILL)
				mDrawID = ACTIVE_NORMAL_STAT;
		}
		break;
	case CLOSE_NORMAL_STAT:
		break;
	case CLOSE_PRESSED_STAT:
		break;
	default:
		break;
	}

	m_pTextureInfo = TextureMgr::GetInstance()->GetTexture(mObjKey, mStateKey, mDrawID);

	if (mDrawID != FRAME_STAT)
	{
		mCollisionRect = { (LONG)mInfo.vPos.x, (LONG)mInfo.vPos.y,
			(LONG)(mInfo.vPos.x + m_pTextureInfo->imgInfo.Width), (LONG)(mInfo.vPos.y + m_pTextureInfo->imgInfo.Height) };
	}
	

	Collision();
	return OBJ_NORMAL;
}

void StatUI::Render(void)
{
	if (mDrawID == FRAME_STAT || mDrawID == CLOSE_NORMAL_STAT || mDrawID == CLOSE_PRESSED_STAT)
	{
		if (m_bStatDialog == false)
		{
			return;
		}
	}

	if (mDrawID == ACTIVE_NORMAL_STAT || mDrawID == DISABLE_STAT)
	{
		if (mType != NORMAL && mType != SKILL)
		{
			if (m_bStatDialog == false)
			{
				return;
			}
		}
	}

	m_pTextureInfo = TextureMgr::GetInstance()->GetTexture(mObjKey, mStateKey, mDrawID);
	D3DXMatrixTranslation(&mInfo.matTrans, mInfo.vPos.x, mInfo.vPos.y, mInfo.vPos.z);

	mInfo.matWorld = mInfo.matTrans;

	m_pSprite->SetTransform(&mInfo.matWorld);
	m_pSprite->Draw(m_pTextureInfo->pTexture, NULL, &D3DXVECTOR3(0.f,0.f, 0.f), nullptr, D3DCOLOR_ARGB(mAlpha, 255, 255, 255));

	if (m_bStatDialog && mDrawID == FRAME_STAT)
	{
		DialogFont();
	}
}

void StatUI::DialogFont()
{
	TCHAR levleBuf[3] = L"";
	TCHAR expBuf[30] = L"";
	TCHAR nextExpBuf[30] = L"";

	TCHAR strBuf[5] = L"";
	TCHAR dexBuf[5] = L"";
	TCHAR lifeBuf[5] = L"";
	TCHAR energyBuf[5] = L"";
	TCHAR statBuf[10] = L"";

	TCHAR attackBuf[7] = L"";
	TCHAR attackGradeBuf[7] = L"";
	TCHAR ShieldBuf[7] = L"";

	TCHAR currentSpBuf[10] = L"";
	TCHAR maxSpBuf[10] = L"";
	TCHAR currentHpBuf[10] = L"";
	TCHAR maxHpBuf[10] = L"";
	TCHAR currentMpBuf[10] = L"";
	TCHAR maxMpBuf[10] = L"";

	TCHAR fireBuf[4] = L"";
	TCHAR coldBuf[4] = L"";
	TCHAR lightBuf[4] = L"";
	TCHAR poisonBuf[4] = L"";

	int fire = 0;
	int cold = 0;
	int light = 0;
	int poison = 0;


	fire = (int)(m_pObserver->GetAttribute()->str * 1.23f);
	cold = (int)(m_pObserver->GetAttribute()->str * 1.11f);
	light = (int)(m_pObserver->GetAttribute()->dex * 1.34f);
	poison = (int)(m_pObserver->GetAttribute()->dex * 1.24f);

	
	D3DXMatrixIdentity(&mMatFont);

	// level
	D3DXMatrixTranslation(&mMatFont, 108, 109, 0.f);
	wsprintf(levleBuf, L"%d", (int)m_pObserver->GetAttribute()->Level);

	m_pSprite->SetTransform(&mMatFont);
	m_pStatFont->DrawTextW(m_pSprite
		, levleBuf, lstrlen(levleBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// exp
	D3DXMatrixTranslation(&mMatFont, 178, 109, 0.f);
	wsprintf(expBuf, L"%d", (int)m_pObserver->GetAttribute()->currentEXP);


	m_pSprite->SetTransform(&mMatFont);
	m_pStatFont->DrawTextW(m_pSprite
		, expBuf, lstrlen(expBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// Next exp
	D3DXMatrixTranslation(&mMatFont, 308, 109, 0.f);
	wsprintf(nextExpBuf, L"%d", (int)m_pObserver->GetAttribute()->nextEXP);


	m_pSprite->SetTransform(&mMatFont);
	m_pStatFont->DrawTextW(m_pSprite
		, nextExpBuf, lstrlen(nextExpBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// Str
	D3DXMatrixTranslation(&mMatFont, 166, 147, 0.f);
	wsprintf(strBuf, L"%d", (int)m_pObserver->GetAttribute()->str);

	m_pSprite->SetTransform(&mMatFont);
	m_pStatFont->DrawTextW(m_pSprite
		, strBuf, lstrlen(strBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// Dex
	D3DXMatrixTranslation(&mMatFont, 166, 210, 0.f);
	wsprintf(dexBuf, L"%d", (int)m_pObserver->GetAttribute()->dex);

	m_pSprite->SetTransform(&mMatFont);
	m_pStatFont->DrawTextW(m_pSprite
		, dexBuf, lstrlen(dexBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// life
	D3DXMatrixTranslation(&mMatFont, 166, 295, 0.f);
	wsprintf(lifeBuf, L"%d", (int)m_pObserver->GetAttribute()->life);

	m_pSprite->SetTransform(&mMatFont);
	m_pStatFont->DrawTextW(m_pSprite
		, lifeBuf, lstrlen(lifeBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// enenrgy
	D3DXMatrixTranslation(&mMatFont, 166, 358, 0.f);
	wsprintf(energyBuf, L"%d", (int)m_pObserver->GetAttribute()->energy);

	m_pSprite->SetTransform(&mMatFont);
	m_pStatFont->DrawTextW(m_pSprite
		, energyBuf, lstrlen(energyBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// statPoint
	D3DXMatrixTranslation(&mMatFont, 167, 428, 0.f);
	wsprintf(statBuf, L"%d", (int)m_pObserver->GetAttribute()->statPoint);

	m_pSprite->SetTransform(&mMatFont);
	m_pStatFont->DrawTextW(m_pSprite
		, statBuf, lstrlen(statBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));


	// attack
	D3DXMatrixTranslation(&mMatFont, 353, 147, 0.f);
	wsprintf(attackBuf, L"%d", (int)(m_pObserver->GetAttribute()->str *23.f));

	m_pSprite->SetTransform(&mMatFont);
	m_pStatFont->DrawTextW(m_pSprite
		, attackBuf, lstrlen(attackBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// attack grade
	D3DXMatrixTranslation(&mMatFont, 356, 209, 0.f);
	wsprintf(attackGradeBuf, L"%d", (int)(m_pObserver->GetAttribute()->str *43.f));

	m_pSprite->SetTransform(&mMatFont);
	m_pStatFont->DrawTextW(m_pSprite
		, attackGradeBuf, lstrlen(attackGradeBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));


	// Shield grade
	D3DXMatrixTranslation(&mMatFont, 356, 257, 0.f);
	wsprintf(ShieldBuf, L"%d", (int)(m_pObserver->GetAttribute()->dex *33.f));

	m_pSprite->SetTransform(&mMatFont);
	m_pStatFont->DrawTextW(m_pSprite
		, ShieldBuf, lstrlen(ShieldBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// current stamina
	D3DXMatrixTranslation(&mMatFont, 314, 296, 0.f);
	wsprintf(currentSpBuf, L"%d", (int)(m_pObserver->GetAttribute()->currentSP));

	m_pSprite->SetTransform(&mMatFont);
	m_pStatFont->DrawTextW(m_pSprite
		, currentSpBuf, lstrlen(currentSpBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// max stamina
	D3DXMatrixTranslation(&mMatFont, 357, 296, 0.f);
	wsprintf(maxSpBuf, L"%d", (int)(m_pObserver->GetAttribute()->maxSP));

	m_pSprite->SetTransform(&mMatFont);
	m_pStatFont->DrawTextW(m_pSprite
		, maxSpBuf, lstrlen(maxSpBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));


	// current Hp
	D3DXMatrixTranslation(&mMatFont, 314, 318, 0.f);
	wsprintf(currentHpBuf, L"%d", (int)(m_pObserver->GetAttribute()->currentHP));

	m_pSprite->SetTransform(&mMatFont);
	m_pStatFont->DrawTextW(m_pSprite
		, currentHpBuf, lstrlen(currentHpBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// max Hp
	D3DXMatrixTranslation(&mMatFont, 357, 318, 0.f);
	wsprintf(maxHpBuf, L"%d", (int)(m_pObserver->GetAttribute()->maxHP));

	m_pSprite->SetTransform(&mMatFont);
	m_pStatFont->DrawTextW(m_pSprite
		, maxHpBuf, lstrlen(maxHpBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));


	// current Mp
	D3DXMatrixTranslation(&mMatFont, 314, 357, 0.f);
	wsprintf(currentMpBuf, L"%d", (int)(m_pObserver->GetAttribute()->currentMP));

	m_pSprite->SetTransform(&mMatFont);
	m_pStatFont->DrawTextW(m_pSprite
		, currentMpBuf, lstrlen(currentMpBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// max Mp
	D3DXMatrixTranslation(&mMatFont, 357, 357, 0.f);
	wsprintf(maxMpBuf, L"%d", (int)(m_pObserver->GetAttribute()->maxMP));

	m_pSprite->SetTransform(&mMatFont);
	m_pStatFont->DrawTextW(m_pSprite
		, maxMpBuf, lstrlen(maxMpBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// fire
	D3DXMatrixTranslation(&mMatFont, 363, 397, 0.f);
	wsprintf(fireBuf, L"%d", fire);

	m_pSprite->SetTransform(&mMatFont);
	m_pStatFont->DrawTextW(m_pSprite
		, fireBuf, lstrlen(fireBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// light
	D3DXMatrixTranslation(&mMatFont, 363, 420, 0.f);
	wsprintf(lifeBuf, L"%d", light);

	m_pSprite->SetTransform(&mMatFont);
	m_pStatFont->DrawTextW(m_pSprite
		, lifeBuf, lstrlen(lifeBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// cold
	D3DXMatrixTranslation(&mMatFont, 363, 445, 0.f);
	wsprintf(coldBuf, L"%d", cold);

	m_pSprite->SetTransform(&mMatFont);
	m_pStatFont->DrawTextW(m_pSprite
		, coldBuf, lstrlen(coldBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// poison
	D3DXMatrixTranslation(&mMatFont, 363, 468, 0.f);
	wsprintf(poisonBuf, L"%d", poison);

	m_pSprite->SetTransform(&mMatFont);
	m_pStatFont->DrawTextW(m_pSprite
		, poisonBuf, lstrlen(poisonBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
}



void StatUI::Collision(void)
{
	if (PtInRect(&mCollisionRect, MathMgr::GetInstance()->GetMouse()))
	{
		if (GetAsyncKeyState(VK_LBUTTON) && 0x8000)
		{
			if (mType == NORMAL || mType == SKILL)
			{
				dynamic_cast<LifeObj*>(m_pPlayer)->SetMoveCheck(false);
			}
			if (mDrawID == ACTIVE_NORMAL_STAT)
			{
				if (mType == NORMAL)
				{
					
					mDrawID = ACTIVE_PRESSED_STAT;
					m_bStatDialog = true;
				}
				else if (mType == SKILL)
				{
					mDrawID = ACTIVE_PRESSED_STAT;
					m_bSkillDialog = true;
				}
				else
				{
					if (m_bStatDialog && m_pObserver->GetAttribute()->type == HUMAN)
					{
						mDrawID = ACTIVE_PRESSED_STAT;
						switch (mType)
						{
						case STR:
							m_pPlayer->SetStr(3);
							m_pPlayer->SetStatPoint(-3);
							break;
						case DEX:
							m_pPlayer->SetDex(3);
							m_pPlayer->SetStatPoint(-3);
							break;
						case LIFE:
							m_pPlayer->SetLife(3);
							m_pPlayer->SetStatPoint(-3);
							break;
						case ENERGY:
							m_pPlayer->SetEnergy(3);
							m_pPlayer->SetStatPoint(-3);
						/*	cout << m_pPlayer->GetAttribute().energy << endl;
							cout << m_pPlayer->GetAttribute().statPoint << endl;*/
							break;
						default:
							break;
						}
					}
					
				}
				
			}
			else if (mDrawID == CLOSE_NORMAL_STAT)
			{
				mDrawID = CLOSE_PRESSED_STAT;
				m_bStatDialog = false;
			}
		}
		else
		{
			if (mDrawID == ACTIVE_PRESSED_STAT)
			{
				mDrawID = ACTIVE_NORMAL_STAT;
			}
			else if (mDrawID == CLOSE_PRESSED_STAT)
			{
				mDrawID = CLOSE_NORMAL_STAT;
			}
		}


		
	}

	if (m_bStatDialog == true)
	{
		dynamic_cast<LifeObj*>(m_pPlayer)->SetMoveCheck(false);
	}
	
}


void StatUI::KeyCheck(void)
{
	if( KeyMgr::GetInstance()->KeyDown(KEY_7) )
	{
		m_pPlayer->SetEXP(+m_pPlayer->GetAttribute().nextEXP);
	}

	if (KeyMgr::GetInstance()->KeyDown(KEY_S))
	{
		m_bStatDialog = !m_bStatDialog;
	}
}


void StatUI::Release(void)
{
	SafeDelete<Observer*>(m_pObserver);
}

