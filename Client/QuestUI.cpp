#include "stdafx.h"
#include "QuestUI.h"
#include "BuffSkill.h"

QuestUI::QuestUI()
{
	mStateKey = L"Quest";

}


QuestUI::~QuestUI()
{
	Release();
}

HRESULT QuestUI::Initialize()
{
	mCloseRect = { 744, 504, 744 + 48, 504 + 48 };

	return S_OK;
}

int QuestUI::Update(void)
{
	KeyCheck();

	// 21 70
	mNpcRect = { 1583 + (LONG)ScrollMgr::GetInstance()->GetScrollX() , 1960 + (LONG)ScrollMgr::GetInstance()->GetScrollY(),
		1583 + 21 + (LONG)ScrollMgr::GetInstance()->GetScrollX(), 1960 + 90 + (LONG)ScrollMgr::GetInstance()->GetScrollY() };

	if (m_bQuestDialog == false)
		return OBJ_NORMAL;

	if (m_pPlayer->GetAttribute().FallenShamanCount <= 0 && mEnemyDrawID != 25)
	{
		mEnemyDrawID += 5 * TimeMgr::GetInstance()->GetTime();
		if (mEnemyDrawID >= 25)
			mEnemyDrawID = 25;
	}

	if (m_pPlayer->GetAttribute().DiabloCount <= 0 && mDiaDrawID != 25)
	{
		mDiaDrawID += 5 * TimeMgr::GetInstance()->GetTime();
		if (mDiaDrawID >= 25)
			mDiaDrawID = 25;
	}

	
	return OBJ_NORMAL;
}

void QuestUI::Render(void)
{
	if (m_bQuestDialog == false)
		return;

	FrameRender();
	QuestIconEnemy_Render();
	QuestIconDia_Render();
	DrawFont();

	Collision();
}

void QuestUI::Collision(void)
{
	static bool bInit = false;
	static bool bInit2 = false;
	if (m_bQuestDialog)
		dynamic_cast<LifeObj*>(m_pPlayer)->SetMoveCheck(false);

	if (PtInRect(&mCloseRect, MathMgr::GetInstance()->GetMouse()))
	{
		if (GetAsyncKeyState(VK_LBUTTON) && 0x8000)
		{
			m_bQuestDialog = false;
		}
	}

	if (PtInRect(&mNpcRect, MathMgr::GetInstance()->GetMouse()))
	{
		if (GetAsyncKeyState(VK_LBUTTON) && 0x8000)
		{
			if (m_pPlayer->GetAttribute().FallenShamanCount <= 0)
			{
				if (bInit == false)
				{
					mDiaDrawID = 1;

					if (gSceneName != L"Village")
						return;

					if (ObjMgr::GetInstance()->GetEffectObj(REDPORTAL) != nullptr)
					{
						ObjMgr::GetInstance()->DeleteSelectObj(ObjMgr::GetInstance()->GetEffectObj(REDPORTAL), OBJ_EFFECT);
					}

					ObjMgr::GetInstance()->AddObject(OBJ_EFFECT, ObjFactory<BuffSkill>::CreateEffect(REDPORTAL,
						D3DXVECTOR3(1590.f, 2110.f, 0.f), m_pPlayer));

					SoundMgr::GetInstance()->PlaySound(L"Aka_act1_q6_successful.wav", UI_SOUND);
					bInit = true;
				}
			
			}
			else
			{
				if (bInit2 == false)
				{
					SoundMgr::GetInstance()->PlaySound(L"Aka_act1_q1_init.wav", UI_SOUND);
					bInit2 = true;
				}
				
				mEnemyDrawID = 1;


			}
		}
	}
}

void QuestUI::KeyCheck(void)
{
	if (KeyMgr::GetInstance()->KeyDown(KEY_Q))
	{
		m_bQuestDialog = !m_bQuestDialog;
	}
}

void QuestUI::Release(void)
{

}

void QuestUI::FrameRender()
{
	m_pTextureInfo = TextureMgr::GetInstance()->GetTexture(mObjKey, mStateKey, mDrawID);
	D3DXMatrixTranslation(&mInfo.matTrans, mInfo.vPos.x, mInfo.vPos.y, mInfo.vPos.z);

	mInfo.matWorld = mInfo.matTrans;

	m_pSprite->SetTransform(&mInfo.matWorld);
	m_pSprite->Draw(m_pTextureInfo->pTexture, NULL, &D3DXVECTOR3(0.f, 0.f, 0.f), nullptr, D3DCOLOR_ARGB(mAlpha, 255, 255, 255));

	DebugMgr::GetInstance()->DrawRectange((float)mNpcRect.left, (float)mNpcRect.top,
		(float)21, (float)90);
}

void QuestUI::QuestIconEnemy_Render()
{
	const TEXTURE_INFO* pTextureInfo = TextureMgr::GetInstance()->GetTexture(mObjKey, L"QuestIconEnemy", (int)mEnemyDrawID);

	D3DXMATRIX matTrans;
	D3DXMatrixIdentity(&matTrans);

	D3DXMatrixTranslation(&matTrans, 488.f, 122.f, 0.f);

	m_pSprite->SetTransform(&matTrans);

	m_pSprite->Draw(pTextureInfo->pTexture, nullptr
		, &D3DXVECTOR3(0.f, 0.f, 0.f)
		, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void QuestUI::QuestIconDia_Render()
{
	const TEXTURE_INFO* pTextureInfo = TextureMgr::GetInstance()->GetTexture(mObjKey, L"QuestIconDia", (int)mDiaDrawID);

	D3DXMATRIX matTrans;
	D3DXMatrixIdentity(&matTrans);

	D3DXMatrixTranslation(&matTrans, 636.f, 122.f, 0.f);

	m_pSprite->SetTransform(&matTrans);

	m_pSprite->Draw(pTextureInfo->pTexture, nullptr
		, &D3DXVECTOR3(0.f, 0.f, 0.f)
		, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void QuestUI::DrawFont()
{
	TCHAR QuestBuf[40] = L"";

	D3DXMatrixIdentity(&mMatFont);

	if (mDiaDrawID == 1 || mDiaDrawID == 25)
	{
		D3DXMatrixTranslation(&mMatFont, 488, 391, 0.f);

		if (m_pPlayer->GetAttribute().DiabloCount > 0)
		{
			wsprintf(QuestBuf, L"디아블로를 처치하세요");
		}
		else
		{
			wsprintf(QuestBuf, L"디아블로 처치 성공!");
		}

		m_pSprite->SetTransform(&mMatFont);
		m_pFont->DrawTextW(m_pSprite
			, QuestBuf, lstrlen(QuestBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else if ( (mEnemyDrawID == 1 || mEnemyDrawID == 25) && m_pPlayer->GetAttribute().DiabloCount > 0)
	{
		D3DXMatrixTranslation(&mMatFont, 488, 391, 0.f);
		if (m_pPlayer->GetAttribute().FallenShamanCount > 0)
		{
			wsprintf(QuestBuf, L"소환사 %d마리를 처치하세요", m_pPlayer->GetAttribute().FallenShamanCount);
		}
		else
		{
			wsprintf(QuestBuf, L"소환사 처치 성공!", m_pPlayer->GetAttribute().FallenShamanCount);
		}
		

		m_pSprite->SetTransform(&mMatFont);
		m_pFont->DrawTextW(m_pSprite
			, QuestBuf, lstrlen(QuestBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	
}
